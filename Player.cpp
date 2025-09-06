#include "Player.h"
#include <algorithm>
#include <cmath>

void Player::Initialize(Input* input, const Vector2& startPos, float radius) {
    input_ = input;
    pos = startPos;
    drawRadius_ = radius;              // ��: 16 �� ���a32px�ŕ`��
    collisionRadius_ = radius * 0.6f;  // �� �����蔻�肾��60%�ɏk��
    vel_ = { 0.0f, 0.0f };

    dragging_ = false;

    // �v���C���[
    playerTexture_ = TextureManager::Load("PlayerBall.png");
    playerSprite_.reset(Sprite::Create(playerTexture_, pos, { 1,1,1,1 }, { 0.5f, 0.5f }));
    playerSprite_->SetPosition(pos);

    // ���iPivot�����[�ɐݒ�A�T�C�Y�Œ�j
    playerArrowTexture = TextureManager::Load("arrow.png");
    playerArrowSprite_.reset(Sprite::Create(playerArrowTexture, pos, { 1,1,1,1 }, { 0.0f, -1.0f }));
    playerArrowSprite_->SetSize({ radius_ * 2.0f, radius_ * 2.0f });
    playerArrowSprite_->SetPosition(pos);

    // === HP�o�[ ===
    barWidth = 400.0f;
    barHeight = 20.0f;
    screenWidth = 1280.0f;   // ��ʕ�
    barX = (screenWidth - barWidth) / 2.0f; // ����
    barY = 750.0f;           // Y�ʒu�w��
    hpBackTex_ = TextureManager::Load("PlayerHP_Back.png");
    hpGaugeTex_ = TextureManager::Load("PlayerHP.png");

    hpBackSprite_.reset(Sprite::Create(hpBackTex_, { barX, barY }));
    hpGaugeSprite_.reset(Sprite::Create(hpGaugeTex_, { barX, barY }));

    hpBackSprite_->SetSize({ barWidth, barHeight });
    hpGaugeSprite_->SetSize({ barWidth, barHeight });
    // �X�v���C�g�̃T�C�Y�Ɣ��a�𓝈�
    playerSprite_->SetSize({ 32, 32 });

}

void Player::TakeDamage(int damage) {
    currentHp_ -= damage;
    if (currentHp_ <= 0) {
        currentHp_ = 0;
    }
}

void Player::Update() {
    Vector2 mousePos = input_->GetMousePosition();

    // --- WASD�L�[�ňړ� ---
    const float accel = 0.5f;
    if (input_->PushKey(DIK_W)) { vel_.y -= accel; }
    if (input_->PushKey(DIK_S)) { vel_.y += accel; }
    if (input_->PushKey(DIK_A)) { vel_.x -= accel; }
    if (input_->PushKey(DIK_D)) { vel_.x += accel; }

    // --- �}�E�X�h���b�O�J�n ---
    if (input_->IsTriggerMouse(0)) {
        dragging_ = true;
        dragStart_ = mousePos;
    }

    // --- �}�E�X�h���b�O�� ---
    if (!arrowFlying_ && !arrowReturning_ && dragging_ && input_->IsPressMouse(0)) {
        dragCurrent_ = mousePos;

        Vector2 diff = { dragStart_.x - dragCurrent_.x, dragStart_.y - dragCurrent_.y };
        float angle = atan2f(diff.y, diff.x);
        playerArrowSprite_->SetRotation(angle);

        playerArrowSprite_->SetSize({ radius_ * 2.0f, radius_ * 2.0f });
        Vector2 dragOffset = { -diff.x * 0.1f - 20.0f, -diff.y * 0.1f };
        playerArrowSprite_->SetPosition({ pos.x + dragOffset.x, pos.y + dragOffset.y });
    }
    else {
        if (dragging_ && !input_->IsPressMouse(0)) {
            dragging_ = false;

            // --- �����v���C���[�ɖ߂������J�n ---
            arrowReturning_ = true;
        }
    }

    if (arrowReturning_) {
        Vector2 arrowPos = playerArrowSprite_->GetPosition();

        // �v���C���[�ʒu�֕�Ԃ��Ė߂�
        Vector2 dir = { pos.x - arrowPos.x, pos.y - arrowPos.y };
        float dist = sqrtf(dir.x * dir.x + dir.y * dir.y);

        if (dist < 5.0f) {
            // �߂肫�����狅���΂�
            playerArrowSprite_->SetPosition(pos);
            arrowReturning_ = false;

            // --- ���̔��ˏ��� ---
            // �}�E�X�̈ړ������̋t�����ɔ�΂�
            Vector2 mouseDir = { dragCurrent_.x - dragStart_.x, dragCurrent_.y - dragStart_.y };
            float len = sqrtf(mouseDir.x * mouseDir.x + mouseDir.y * mouseDir.y);
            if (len != 0) {
                mouseDir.x /= len;
                mouseDir.y /= len;
            }
            float power = 10.0f; // ���˂̋���
            vel_.x = -mouseDir.x * power; // �t�����ɔ�΂�
            vel_.y = -mouseDir.y * power;
        }
        else {
            // �߂�r��
            dir.x /= dist;
            dir.y /= dist;
            float returnSpeed = 20.0f;
            arrowPos.x += dir.x * returnSpeed;
            arrowPos.y += dir.y * returnSpeed;
            playerArrowSprite_->SetPosition(arrowPos);
        }
        
    }


    // --- ���C ---
    vel_ *= 0.98f;

    // --- �ʒu�X�V ---
    pos += vel_;

    // --- ��ʒ[�Ŕ��� ---
    const float left = 235.0f;
    const float right = 1050.0f;
    const float top = 280.0f;
    const float bottom = 680.0f;

    if (pos.x < left) { pos.x = left; vel_.x *= -1.0f; }
    if (pos.x > right) { pos.x = right; vel_.x *= -1.0f; }
    if (pos.y < top) { pos.y = top; vel_.y *= -1.0f; }
    if (pos.y > bottom) { pos.y = bottom; vel_.y *= -1.0f; }

    // ���G���Ԃ����Z
    if (invincibleTimer_ > 0) {
        invincibleTimer_--;
    }


    playerSprite_->SetPosition({ pos.x + offset.x, pos.y + offset.y });
    // --- �|�P�b�g���� ---
    CheckPocketCollision();
}

void Player::Draw() {
    playerSprite_->Draw();
    // ���N���b�N�������̂ݖ��\��
    if (input_->IsPressMouse(0)) {
        playerArrowSprite_->Draw();
    }

    // === HP�Q�[�W ===
    if (hpBackSprite_) {

        hpBackSprite_->Draw();
    }
    if (hpGaugeSprite_) {
        float hpPercent = (float)currentHp_ / maxHp_;
        hpGaugeSprite_->SetSize({ barWidth * hpPercent, barHeight });

        // �ʒu�͔w�i�̍��[�ɌŒ肷��
        hpGaugeSprite_->SetPosition({ barX, barY });

        hpGaugeSprite_->Draw();
    }
}

void Player::CheckPocketCollision() {
    if (invincibleTimer_ > 0) return; // ���G���̓X�L�b�v

    Vector2 pockets[6] = {
        { 220, 290 },   // ����
        { 1000, 250 },  // �E��
        { 202, 632 },   // ����
        { 1000, 632 },  // �E��
        { 600, 250 },   // �㒆��
        { 610, 660 }    // ������
    };

    float pocketRadius = 38.0f;

    for (int i = 0; i < 6; i++) {
        float dx = pos.x - pockets[i].x;
        float dy = pos.y - pockets[i].y;
        float distSq = dx * dx + dy * dy;

        if (distSq < pocketRadius * pocketRadius) {
            // �� �_���[�W���󂯂�
            TakeDamage(1);
            invincibleTimer_ = 60; // ��1�b�̖��G���ԁi60fps�z��j

            // �� �����_���ŕʂ̃|�P�b�g��I��
            int newPocket = i;
            while (newPocket == i) {
                newPocket = rand() % 6;
            }

            // �㑤�|�P�b�g�Ȃ班�����ɁA�����Ȃ班����ɏo��
            Vector2 spawnPos = pockets[newPocket];
            if (spawnPos.y < 400) {
                spawnPos.y += 50;
            }
            else {
                spawnPos.y -= 50;
            }

            pos = spawnPos;
            playerSprite_->SetPosition(pos);

            break;
        }
    }
}
