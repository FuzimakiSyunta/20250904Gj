#include "Player.h"

void Player::Initialize() {
#pragma region ‰æ‘œ
	//‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	playerTexture_ = TextureManager::Load("PlayerBall.png");
	playerSprite_.reset(Sprite::Create(playerTexture_, pos));
}

void Player::Update() {
}

void Player::Draw() {
	playerSprite_->Draw();
}

