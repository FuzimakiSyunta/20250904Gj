#include "Billiardstable.h"

void Billiardstable::Initialize() {
	#pragma region ‰æ‘œ
	//‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	billiardstableTexture_ = TextureManager::Load("Billiards.png");
	billiardstableSprite_.reset(Sprite::Create(billiardstableTexture_, pos));
	billiardstableSprite_->SetPosition(pos);
}

void Billiardstable::Update() {
	
}

void Billiardstable::Draw() {
	billiardstableSprite_->Draw();
}