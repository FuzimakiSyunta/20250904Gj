#include "Player.h"

void Player::Initialize() {
#pragma region �摜
	//�摜�̓ǂݍ���
	playerTexture_ = TextureManager::Load("PlayerBall.png");
	playerSprite_.reset(Sprite::Create(playerTexture_, pos));
}

void Player::Update() {
}

void Player::Draw() {
	playerSprite_->Draw();
}

