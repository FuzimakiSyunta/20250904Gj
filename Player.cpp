#include "Player.h"
#include <algorithm>

void Player::Initialize(Input* input, const Vector2& startPos, float radius) {
    input_ = input;
    pos = startPos;
    radius_ = radius;
    vel_ = { 0.0f, 0.0f };

    dragging_ = false;

    // �v���C���[
    playerTexture_ = TextureManager::Load("PlayerBall.png");
    playerSprite_.reset(Sprite::Create(playerTexture_, pos));
    playerSprite_->SetPosition(pos);

    // ���i������]45���j
    playerArrowTexture = TextureManager::Load("arrow.png");
    playerArrowSprite_.reset(Sprite::Create(playerArrowTexture, pos));
    playerArrowSprite_->SetPosition(pos);
   
}

void Player::Update() {
    Vector2 mousePos = input_->GetMousePosition();

    // --- WASD�L�[�ňړ� ---
    const float accel = 0.5f; // �����x
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

        // �ʒu�̓v���C���[�ɍ��킹��
        playerArrowSprite_->SetPosition(pos);
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
    const float left = radius_;
    const float right = 1280 - radius_;
    const float top = radius_;
    const float bottom = 720 - radius_;

    if (pos.x < left) { pos.x = left; vel_.x *= -1.0f; }
    if (pos.x > right) { pos.x = right; vel_.x *= -1.0f; }
    if (pos.y < top) { pos.y = top; vel_.y *= -1.0f; }
    if (pos.y > bottom) { pos.y = bottom; vel_.y *= -1.0f; }

    // --- �v���C���[�X�v���C�g�X�V ---
    playerSprite_->SetSize({ radius_ * 2.0f, radius_ * 2.0f });
    playerSprite_->SetPosition(pos);
}



void Player::Draw() {
    playerSprite_->Draw();
    // �E�N���b�N�������̂ݖ��\��
    if (input_->IsPressMouse(0)) {
        playerArrowSprite_->Draw();
    }
}