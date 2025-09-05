#include "Player.h"
#include <algorithm> // std::clamp

void Player::Initialize(Input* input, const Vector2& startPos, float radius) {
    input_ = input;
    pos = startPos;
    radius_ = radius;
    vel_ = { 0.0f, 0.0f };

#pragma region 画像
    // 画像の読み込み
    playerTexture_ = TextureManager::Load("PlayerBall.png");
    playerSprite_.reset(Sprite::Create(playerTexture_, pos));
    playerSprite_->SetPosition(pos);
#pragma endregion
}

void Player::Update() {
    // 入力で「力」を加える（キーボード押しっぱなしで加速）
    const float accel = 0.5f;
    if (input_->PushKey(DIK_A)) { vel_.x -= accel; }
    if (input_->PushKey(DIK_D)) { vel_.x += accel; }
    if (input_->PushKey(DIK_W)) { vel_.y -= accel; }
    if (input_->PushKey(DIK_S)) { vel_.y += accel; }

    // 摩擦（徐々に止まる）
    const float friction = 0.98f; // 1.0に近いほど滑る
    vel_.x *= friction;
    vel_.y *= friction;

    // 位置を更新
    pos.x += vel_.x;
    pos.y += vel_.y;

    // 画面端で反射（ビリヤードっぽくする）
    const float left = radius_;
    const float right = 1280 - radius_; // 画面幅に合わせて調整
    const float top = radius_;
    const float bottom = 720 - radius_; // 画面高さに合わせて調整

    if (pos.x < left) {
        pos.x = left;
        vel_.x *= -1.0f; // 反射
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

    // スプライトに更新を反映
    playerSprite_->SetSize({ radius_ * 2.0f, radius_ * 2.0f });
    playerSprite_->SetPosition(pos);
}

void Player::Draw() {
    playerSprite_->Draw();
}
