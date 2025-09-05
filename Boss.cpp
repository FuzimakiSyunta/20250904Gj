#include "Boss.h"
#include <cstdlib> // rand()

void Boss::Initialize(Input* input) {
    input_ = input;
    bossTexture_ = TextureManager::Load("slimeKing.png");
    bossDamegeTexture_ = TextureManager::Load("slimeKing_Dmaege.png");
    basePos_ = { 540.0f, 40.0f };
    bossSprite_.reset(Sprite::Create(bossTexture_, basePos_));
    bossDamegeSprite_.reset(Sprite::Create(bossDamegeTexture_, basePos_));
    bossSprite_->SetPosition(basePos_);
    bossDamegeSprite_->SetPosition(basePos_);
}

void Boss::Update() {
    if (isShaking_) {
        shakeTimer_--;
        if (shakeTimer_ <= 0) {
            isShaking_ = false;
            bossSprite_->SetPosition(basePos_);
			bossDamegeSprite_->SetPosition(basePos_);
        }
        else {
            // ランダムに揺らす
            float offsetX = (rand() % 100 / 100.0f - 0.5f) * 2 * shakeStrength_;
            float offsetY = (rand() % 100 / 100.0f - 0.5f) * 2 * shakeStrength_;
            bossSprite_->SetPosition({ basePos_.x + offsetX, basePos_.y + offsetY });
			bossDamegeSprite_->SetPosition({ basePos_.x + offsetX, basePos_.y + offsetY });
        }
    }

    if (input_->PushKey(DIK_1)) { 
        if (!isDebugdamage_) {
            OnDamage();
            isDebugdamage_ = true;
        }
    }
    else if(input_->PushKey(DIK_2)){
		isDebugdamage_ = false;
    }
}

void Boss::Draw() {
    if (bossSprite_&&!isShaking_) {
        bossSprite_->Draw();
    }
    if (isShaking_ && bossDamegeSprite_) {
        bossDamegeSprite_->Draw();
	}
}

// ★ ダメージを受けたときに呼ぶ関数
void Boss::OnDamage() {
    isShaking_ = true;
    shakeTimer_ = 20;  // 揺れるフレーム数
}
