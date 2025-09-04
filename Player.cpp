#include "Player.h"

void Player::Initialize(Input* input, const Vector2& startPos, float radius) {
    input_ = input;
    pos = startPos;
    radius_ = radius;

#pragma region �摜
	//�摜�̓ǂݍ���
	playerTexture_ = TextureManager::Load("PlayerBall.png");
	playerSprite_.reset(Sprite::Create(playerTexture_, pos));
    playerSprite_->SetPosition(pos);
}

void Player::Update() {
    vel_ = { 0,0 };
    // ��
    if (input_->PushKey(DIK_A)) {
        pos.x -= speed;
    }
    // �E
    if (input_->PushKey(DIK_D)) {
        pos.x += speed;
    }
    // ��
    if (input_->PushKey(DIK_W)) {
        pos.y -= speed;
    }
    // ��
    if (input_->PushKey(DIK_S)) {
        pos.y += speed;
    }

    pos.x += vel_.x;
    pos.y += vel_.y;

    playerSprite_->SetSize({ radius_ * 2.0f, radius_ * 2.0f }); // ���a�𔽉f
    // �X�v���C�g�ɍ��W�𔽉f
    playerSprite_->SetPosition(pos);
}

void Player::Draw() {
	playerSprite_->Draw();
}

