#include "Player.h"
#include <algorithm>
#include <cmath>

void Player::Initialize(Input* input, const Vector2& startPos, float radius) {
    input_ = input;
    pos = startPos;
    radius_ = radius;
    vel_ = { 0.0f, 0.0f };

    dragging_ = false;

    // プレイヤー
    playerTexture_ = TextureManager::Load("PlayerBall.png");
    playerSprite_.reset(Sprite::Create(playerTexture_, pos, { 1,1,1,1 }, {0.5,0.5}));
    playerSprite_->SetPosition(pos);

    // 矢印（Pivotを下端に設定、サイズ固定）
    playerArrowTexture = TextureManager::Load("arrow.png");
    playerArrowSprite_.reset(Sprite::Create(playerArrowTexture, pos, { 1,1,1,1 }, { 0.5f, 0.5f }));
    playerArrowSprite_->SetSize({ radius_ * 2.0f, radius_ * 2.0f });
    playerArrowSprite_->SetPosition(pos);
}

void Player::Update() {
    Vector2 mousePos = input_->GetMousePosition();

    // --- WASDキーで移動 ---
    const float accel = 0.5f;
    if (input_->PushKey(DIK_W)) { vel_.y -= accel; }
    if (input_->PushKey(DIK_S)) { vel_.y += accel; }
    if (input_->PushKey(DIK_A)) { vel_.x -= accel; }
    if (input_->PushKey(DIK_D)) { vel_.x += accel; }

    // --- マウスドラッグ開始 ---
    if (input_->IsTriggerMouse(0)) {
        dragging_ = true;
        dragStart_ = mousePos;
    }

    // --- マウスドラッグ中 ---
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

            // --- 矢印をプレイヤーに戻す処理開始 ---
            arrowReturning_ = true;
        }
    }

    if (arrowReturning_) {
        Vector2 arrowPos = playerArrowSprite_->GetPosition();

        // プレイヤー位置へ補間して戻す
        Vector2 dir = { pos.x - arrowPos.x, pos.y - arrowPos.y };
        float dist = sqrtf(dir.x * dir.x + dir.y * dir.y);

        if (dist < 5.0f) {
            // 戻りきったら球を飛ばす
            playerArrowSprite_->SetPosition(pos);
            arrowReturning_ = false;

            // --- 球の発射処理 ---
            // マウスの移動方向の逆方向に飛ばす
            Vector2 mouseDir = { dragCurrent_.x - dragStart_.x, dragCurrent_.y - dragStart_.y };
            float len = sqrtf(mouseDir.x * mouseDir.x + mouseDir.y * mouseDir.y);
            if (len != 0) {
                mouseDir.x /= len;
                mouseDir.y /= len;
            }
            float power = 10.0f; // 発射の強さ
            vel_.x = -mouseDir.x * power; // 逆方向に飛ばす
            vel_.y = -mouseDir.y * power;
        }
        else {
            // 戻る途中
            dir.x /= dist;
            dir.y /= dist;
            float returnSpeed = 20.0f;
            arrowPos.x += dir.x * returnSpeed;
            arrowPos.y += dir.y * returnSpeed;
            playerArrowSprite_->SetPosition(arrowPos);
        }
    }


    // --- 摩擦 ---
    vel_ *= 0.98f;

    // --- 位置更新 ---
    pos += vel_;

    // --- 画面端で反射 ---
    const float left = 205.0f;
    const float right = 1005.0f;
    const float top = 265.0f;
    const float bottom = 655.0f;

    if (pos.x < left) { pos.x = left; vel_.x *= -1.0f; }
    if (pos.x > right) { pos.x = right; vel_.x *= -1.0f; }
    if (pos.y < top) { pos.y = top; vel_.y *= -1.0f; }
    if (pos.y > bottom) { pos.y = bottom; vel_.y *= -1.0f; }

    // --- プレイヤースプライト更新 ---
    playerSprite_->SetSize({ 32.0f, 32.0f }); // 常に固定サイズ
    playerSprite_->SetPosition(pos);
}

void Player::Draw() {
    playerSprite_->Draw();
    // 左クリック押下中のみ矢印表示
    
        playerArrowSprite_->Draw();
    
}
