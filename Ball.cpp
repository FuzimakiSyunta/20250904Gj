#include "Ball.h"
#include <cmath>
#include"input/Input.h"

Ball::Ball() {
    for (int i = 0; i < kBallCount; i++) {
        sprite_[i] = nullptr;
        vel_[i] = { 0.0f, 0.0f };
    }
}

Ball::~Ball() {
    for (int i = 0; i < kBallCount; i++)
        delete sprite_[i];
}

void Ball::Initialize(uint32_t /*textureHandle*/) {
    textureHandle_ = TextureManager::Load("ball.png");
    debugCircleTex_ = TextureManager::Load("DebugCircle.png"); // �� �Ԋۉ摜���[�h

    int index = 0;
    const float startX = 300.0f;
    const float startY = 100.0f;
    const float ballSize = 32.0f;
    const float gap = 5.0f;

    int rowCounts[4] = { 4,3,2,1 };
    for (int row = 0; row < 4; row++) {
        int count = rowCounts[row];
        for (int col = 0; col < count; col++) {
            float offsetX = (col - count / 2.0f) * (ballSize + gap);
            float x = startX + offsetX;
            float y = startY + row * (ballSize + gap);
            pos_[index] = { x, y };
            sprite_[index] = Sprite::Create(textureHandle_, pos_[index]);
            isAlive_[index] = true;   // �� �����t���O��ON
            index++;
        }
    }

    vel_[0] = { 2.0f, 1.5f }; // �f���p�F1����������
}

void Ball::Update() {
    MoveBalls();
    CheckCollisions();
    CheckPocketCollisions(); // �� �ǉ�

}

void Ball::Draw() {
    // �{�[���`��
    for (int i = 0; i < kBallCount; i++) {
        if (isAlive_[i] && sprite_[i]) {
            sprite_[i]->SetPosition(pos_[i]);
            sprite_[i]->Draw();
        }
    }

    // �f�o�b�O�p�F�|�P�b�g�ʒu�ɐԊۂ�`��
    Vector2 pockets[6] = {
        {202,250},   // ����
        {1000,250},  // �E��
        {202,632},   // ����
        {1000,632},  // �E��
        {600,250},   // �㒆��
        {600,632}    // ������
    };

    for (int j = 0; j < 6; j++) {
        Sprite* debug = Sprite::Create(debugCircleTex_, pockets[j]);
        debug->Draw();
        
    }
}


void Ball::MoveBalls() {
    const float radius = 16.0f;
    const float screenWidth = 540;
    const float screenHeight = 800;

    for (int i = 0; i < kBallCount; i++) {
        pos_[i].x += vel_[i].x;
        pos_[i].y += vel_[i].y;

        // �ǂŔ���
        if (pos_[i].x < radius || pos_[i].x > screenWidth - radius) vel_[i].x *= -1;
        if (pos_[i].y < radius || pos_[i].y > screenHeight - radius) vel_[i].y *= -1;
    }
}

void Ball::CheckCollisions() {
    const float radius = 16.0f;
    const float minDist = radius * 2.0f;
    const float friction = 0.99f; // ���C�W���i0.0�`1.0�j 1.0�ɋ߂��قǊ���

    for (int i = 0; i < kBallCount; i++) {
        for (int j = i + 1; j < kBallCount; j++) {
            float dx = pos_[j].x - pos_[i].x;
            float dy = pos_[j].y - pos_[i].y;
            float distSq = dx * dx + dy * dy;

            if (distSq < minDist * minDist) {
                float dist = std::sqrt(distSq);
                if (dist < 0.0001f) dist = 0.0001f;
                float nx = dx / dist;
                float ny = dy / dist;

                float rvx = vel_[j].x - vel_[i].x;
                float rvy = vel_[j].y - vel_[i].y;
                float vn = rvx * nx + rvy * ny;

                if (vn < 0.0f) {
                    float impulse = -vn * 1.0f; // �����͍T����
                    vel_[i].x -= impulse * nx;
                    vel_[i].y -= impulse * ny;
                    vel_[j].x += impulse * nx;
                    vel_[j].y += impulse * ny;
                }

                // �߂荞�݉���
                float overlap = (minDist - dist) * 0.5f;
                pos_[i].x -= nx * overlap;
                pos_[i].y -= ny * overlap;
                pos_[j].x += nx * overlap;
                pos_[j].y += ny * overlap;
            }
        }

        // ���C�Ō���
        vel_[i].x *= friction;
        vel_[i].y *= friction;

        // ���x������������ꍇ�͎~�߂�
        if (std::abs(vel_[i].x) < 0.01f) vel_[i].x = 0.0f;
        if (std::abs(vel_[i].y) < 0.01f) vel_[i].y = 0.0f;
    }
}

void Ball::CheckPlayerCollision(Player& player) {
    const float radius = 16.0f;
    Vector2 playerPos = player.GetPos();
    float playerRadius = player.GetRadius();

    for (int i = 0; i < kBallCount; i++) {
        float dx = pos_[i].x - playerPos.x;
        float dy = pos_[i].y - playerPos.y;
        float distSq = dx * dx + dy * dy;
        float minDist = radius + playerRadius;

        if (distSq < minDist * minDist) {
            float dist = std::sqrt(distSq);
            if (dist < 0.0001f) dist = 0.0001f;

            float nx = dx / dist;
            float ny = dy / dist;

            float rvx = vel_[i].x - player.GetVel().x;
            float rvy = vel_[i].y - player.GetVel().y;
            float vn = rvx * nx + rvy * ny;

            if (vn < 0.0f) {
                // ����ɋ����e��
                float impulse = -vn * 6.0f; // �{���� 4 �� 6 �ɑ���
                vel_[i].x += impulse * nx;
                vel_[i].y += impulse * ny;

                // �v���C���[�ւ̉e���͍T����
                player.SetVel(player.GetVel().x - impulse * 0.2f * nx,
                    player.GetVel().y - impulse * 0.2f * ny);
            }

            // �߂荞�݉���
            float overlap = (minDist - dist) * 0.5f;
            pos_[i].x += nx * overlap;
            pos_[i].y += ny * overlap;
            player.SetPos(playerPos.x - nx * overlap, playerPos.y - ny * overlap);
        }
    }
}

void Ball::CheckPocketCollisions() {
    Vector2 pockets[6] = {
        {202,250},   // ����
        {1000,250},  // �E��
        {202,632},   // ����
        {1010,632},  // �E��
        {600,280},   // �㒆��
        {600,632}    // ������
    };

    float pocketRadius = 38.0f;

    for (int i = 0; i < kBallCount; i++) {
        if (!isAlive_[i]) continue;

        for (int j = 0; j < 6; j++) {
            float dx = pos_[i].x - pockets[j].x;
            float dy = pos_[i].y - pockets[j].y;
            float distSq = dx * dx + dy * dy;
            if (distSq < pocketRadius * pocketRadius) {
                isAlive_[i] = false;
                break;
            }
        }
    }
}
