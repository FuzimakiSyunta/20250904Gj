#include "Player.h"
#include <algorithm>
#include <cmath>

void Player::Initialize(Input* input, const Vector2& startPos, float radius) {
    input_ = input;
    pos = startPos;
    radius_ = radius;
    vel_ = { 0.0f, 0.0f };

    dragging_ = false;

    // �v���C���[
    playerTexture_ = TextureManager::Load("PlayerBall.png");
    playerSprite_.reset(Sprite::Create(playerTexture_, pos, { 1,1,1,1 }, {0.5,0.5}));
    playerSprite_->SetPosition(pos);

    // ���iPivot�����[�ɐݒ�A�T�C�Y�Œ�j
    playerArrowTexture = TextureManager::Load("arrow.png");
    playerArrowSprite_.reset(Sprite::Create(playerArrowTexture, pos, { 1,1,1,1 }, { 0.5f, 0.5f }));
    playerArrowSprite_->SetSize({ radius_ * 2.0f, radius_ * 2.0f });
    playerArrowSprite_->SetPosition(pos);
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
    const float left = 205.0f;
    const float right = 1005.0f;
    const float top = 265.0f;
    const float bottom = 655.0f;

    if (pos.x < left) { pos.x = left; vel_.x *= -1.0f; }
    if (pos.x > right) { pos.x = right; vel_.x *= -1.0f; }
    if (pos.y < top) { pos.y = top; vel_.y *= -1.0f; }
    if (pos.y > bottom) { pos.y = bottom; vel_.y *= -1.0f; }

    // --- �v���C���[�X�v���C�g�X�V ---
    playerSprite_->SetSize({ 32.0f, 32.0f }); // ��ɌŒ�T�C�Y
    playerSprite_->SetPosition(pos);
}

void Player::Draw() {
    playerSprite_->Draw();
    // ���N���b�N�������̂ݖ��\��
    
        playerArrowSprite_->Draw();
    
}
