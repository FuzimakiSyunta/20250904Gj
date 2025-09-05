#include "Player.h"
#include <algorithm> // std::clamp

void Player::Initialize(Input* input, const Vector2& startPos, float radius) {
    input_ = input;
    pos = startPos;
    radius_ = radius;
    vel_ = { 0.0f, 0.0f };

#pragma region �摜
    // �摜�̓ǂݍ���
    playerTexture_ = TextureManager::Load("PlayerBall.png");
    playerSprite_.reset(Sprite::Create(playerTexture_, pos));
    playerSprite_->SetPosition(pos);
#pragma endregion
}

void Player::Update() {
    // ���͂Łu�́v��������i�L�[�{�[�h�������ςȂ��ŉ����j
    const float accel = 0.5f;
    if (input_->PushKey(DIK_A)) { vel_.x -= accel; }
    if (input_->PushKey(DIK_D)) { vel_.x += accel; }
    if (input_->PushKey(DIK_W)) { vel_.y -= accel; }
    if (input_->PushKey(DIK_S)) { vel_.y += accel; }

    // ���C�i���X�Ɏ~�܂�j
    const float friction = 0.98f; // 1.0�ɋ߂��قǊ���
    vel_.x *= friction;
    vel_.y *= friction;

    // �ʒu���X�V
    pos.x += vel_.x;
    pos.y += vel_.y;

    // ��ʒ[�Ŕ��ˁi�r�����[�h���ۂ�����j
    const float left = radius_;
    const float right = 1280 - radius_; // ��ʕ��ɍ��킹�Ē���
    const float top = radius_;
    const float bottom = 720 - radius_; // ��ʍ����ɍ��킹�Ē���

    if (pos.x < left) {
        pos.x = left;
        vel_.x *= -1.0f; // ����
    }
    if (pos.x > right) {
        pos.x = right;
        vel_.x *= -1.0f;
    }
    if (pos.y < top) {
        pos.y = top;
        vel_.y *= -1.0f;
    }
    if (pos.y > bottom) {
        pos.y = bottom;
        vel_.y *= -1.0f;
    }

    // �X�v���C�g�ɍX�V�𔽉f
    playerSprite_->SetSize({ radius_ * 2.0f, radius_ * 2.0f });
    playerSprite_->SetPosition(pos);
}

void Player::Draw() {
    playerSprite_->Draw();
}
