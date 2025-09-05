#include "Player.h"
#include <algorithm>

void Player::Initialize(Input* input, const Vector2& startPos, float radius) {
    input_ = input;
    pos = startPos;
    radius_ = radius;
    vel_ = { 0.0f, 0.0f };

    dragging_ = false;

    // プレイヤー
    playerTexture_ = TextureManager::Load("PlayerBall.png");
    playerSprite_.reset(Sprite::Create(playerTexture_, pos));
    playerSprite_->SetPosition(pos);

    // 矢印（初期回転45°）
    playerArrowTexture = TextureManager::Load("arrow.png");
    playerArrowSprite_.reset(Sprite::Create(playerArrowTexture, pos));
    playerArrowSprite_->SetPosition(pos);
   
}

void Player::Update() {
    Vector2 mousePos = input_->GetMousePosition();

    // --- WASDキーで移動 ---
    const float accel = 0.5f; // 加速度
    if (input_->PushKey(DIK_W)) { vel_.y -= accel; }
    if (input_->PushKey(DIK_S)) { vel_.y += accel; }
    if (input_->PushKey(DIK_A)) { vel_.x -= accel; }
    if (input_->PushKey(DIK_D)) { vel_.x += accel; }

    // --- マウスドラッグ ---
    if (input_->IsTriggerMouse(0)) {
        dragging_ = true;
        dragStart_ = mousePos;
    }

    if (dragging_ && input_->IsPressMouse(0)) {
        dragCurrent_ = mousePos;

        // --- 矢印の回転と拡大 ---
        Vector2 diff = { dragStart_.x - dragCurrent_.x, dragStart_.y - dragCurrent_.y };
        float length = sqrtf(diff.x * diff.x + diff.y * diff.y);

        // 回転（初期45°は固定してあるのでそのままangleをセット）
        float angle = atan2f(diff.y, diff.x);
        playerArrowSprite_->SetRotation(angle);

        // 大きさ（引っ張り距離で拡大）
        float scale = std::clamp(length / 100.0f, 0.5f, 3.0f);
        playerArrowSprite_->SetSize({ radius_ * 2.0f * scale, radius_ * 2.0f * scale });

        // 位置はプレイヤーに合わせる
        playerArrowSprite_->SetPosition(pos);
    }

    if (dragging_ && !input_->IsPressMouse(0)) {
        dragging_ = false;
        Vector2 diff = { dragStart_.x - mousePos.x, dragStart_.y - mousePos.y };
        const float power = 0.1f;
        vel_.x = diff.x * power;
        vel_.y = diff.y * power;
    }

    // --- 摩擦 ---
    vel_ *= 0.98f;

    // --- 位置更新 ---
    pos += vel_;

    // --- 画面端で反射 ---
    const float left = radius_;
    const float right = 1280 - radius_;
    const float top = radius_;
    const float bottom = 720 - radius_;

    if (pos.x < left) { pos.x = left; vel_.x *= -1.0f; }
    if (pos.x > right) { pos.x = right; vel_.x *= -1.0f; }
    if (pos.y < top) { pos.y = top; vel_.y *= -1.0f; }
    if (pos.y > bottom) { pos.y = bottom; vel_.y *= -1.0f; }

    // --- プレイヤースプライト更新 ---
    playerSprite_->SetSize({ radius_ * 2.0f, radius_ * 2.0f });
    playerSprite_->SetPosition(pos);
}



void Player::Draw() {
    playerSprite_->Draw();
    // 右クリック押下中のみ矢印表示
    if (input_->IsPressMouse(0)) {
        playerArrowSprite_->Draw();
    }
}