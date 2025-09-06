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

    // ���i������]45���j
    playerArrowTexture = TextureManager::Load("arrow.png");
    playerArrowSprite_.reset(Sprite::Create(playerArrowTexture, ArrowpPos, { 1,1,1,1 }, { 0.5,0.5 }));
    playerArrowSprite_->SetPosition(ArrowpPos);

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

    // --- �}�E�X�h���b�O ---
    if (input_->IsTriggerMouse(0)) {
        dragging_ = true;
        dragStart_ = mousePos;
    }

    if (dragging_ && input_->IsPressMouse(0)) {
        dragCurrent_ = mousePos;

        // --- ���̉�]�Ɗg�� ---
        Vector2 diff = { dragStart_.x - dragCurrent_.x, dragStart_.y - dragCurrent_.y };
        float length = sqrtf(diff.x * diff.x + diff.y * diff.y);

        // ��]�i����45���͌Œ肵�Ă���̂ł��̂܂�angle���Z�b�g�j
        float angle = atan2f(diff.y, diff.x);
        playerArrowSprite_->SetRotation(angle);

        // �傫���i�������苗���Ŋg��j
        float scale = std::clamp(length / 100.0f, 0.5f, 3.0f);
        playerArrowSprite_->SetSize({ radius_ * 2.0f * scale, radius_ * 2.0f * scale });
        Vector2 offset = { 10.0f, 30.0f };
        playerArrowSprite_->SetPosition({ pos.x + offset.x, pos.y + offset.y });
    }

    if (dragging_ && !input_->IsPressMouse(0)) {
        dragging_ = false;
        Vector2 diff = { dragStart_.x - mousePos.x, dragStart_.y - mousePos.y };
        const float power = 0.1f;
        vel_.x = diff.x * power;
        vel_.y = diff.y * power;
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
    // ���N���b�N�������̂ݖ��\��
    if (input_->IsPressMouse(0)) {
        playerArrowSprite_->Draw();
    }
    playerSprite_->Draw();

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
