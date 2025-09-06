#include "Player.h"
#include <algorithm>
#include <cmath>

void Player::Initialize(Input* input, const Vector2& startPos, float radius) {
    input_ = input;
    pos = startPos;
    drawRadius_ = radius;              // 例: 16 → 直径32pxで描画
    collisionRadius_ = radius * 0.6f;  // ★ 当たり判定だけ60%に縮小
    vel_ = { 0.0f, 0.0f };

    dragging_ = false;

    // プレイヤー
    playerTexture_ = TextureManager::Load("PlayerBall.png");
    playerSprite_.reset(Sprite::Create(playerTexture_, pos, { 1,1,1,1 }, { 0.5f, 0.5f }));
    playerSprite_->SetPosition(pos);

    // 矢印（Pivotを下端に設定、サイズ固定）
    playerArrowTexture = TextureManager::Load("arrow.png");
    playerArrowSprite_.reset(Sprite::Create(playerArrowTexture, pos, { 1,1,1,1 }, { 0.0f, -1.0f }));
    playerArrowSprite_->SetSize({ radius_ * 2.0f, radius_ * 2.0f });
    playerArrowSprite_->SetPosition(pos);

    // === HPバー ===
    barWidth = 400.0f;
    barHeight = 20.0f;
    screenWidth = 1280.0f;   // 画面幅
    barX = (screenWidth - barWidth) / 2.0f; // 中央
    barY = 750.0f;           // Y位置指定
    hpBackTex_ = TextureManager::Load("PlayerHP_Back.png");
    hpGaugeTex_ = TextureManager::Load("PlayerHP.png");

    hpBackSprite_.reset(Sprite::Create(hpBackTex_, { barX, barY }));
    hpGaugeSprite_.reset(Sprite::Create(hpGaugeTex_, { barX, barY }));

    hpBackSprite_->SetSize({ barWidth, barHeight });
    hpGaugeSprite_->SetSize({ barWidth, barHeight });
    // スプライトのサイズと半径を統一
    playerSprite_->SetSize({ 32, 32 });

}

void Player::TakeDamage(int damage) {
    currentHp_ -= damage;
    if (currentHp_ <= 0) {
        currentHp_ = 0;
    }
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
        
        //矢印の回転と拡大
        Vector2 diff = { dragStart_.x - dragCurrent_.x, dragStart_.y - dragCurrent_.y };
        float length = sqrtf(diff.x * diff.x + diff.y * diff.y);

        // 回転
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

    //摩擦
    vel_ *= 0.98f;

    //位置更新
    pos += vel_;

    //画面端で反射
    const float left = 205.0f;
    const float right = 1005.0f;
    const float top = 265.0f;
    const float bottom = 655.0f;

    if (pos.x < left) { pos.x = left; vel_.x *= -1.0f; }
    if (pos.x > right) { pos.x = right; vel_.x *= -1.0f; }
    if (pos.y < top) { pos.y = top; vel_.y *= -1.0f; }
    if (pos.y > bottom) { pos.y = bottom; vel_.y *= -1.0f; }

    // 無敵時間を減算
    if (invincibleTimer_ > 0) {
        invincibleTimer_--;
    }
    //  プレイヤースプライト更新 
    playerSprite_->SetSize({ radius_ * 2.0f, radius_ * 2.0f });
    playerSprite_->SetPosition(pos);
}


    playerSprite_->SetPosition({ pos.x + offset.x, pos.y + offset.y });
    // --- ポケット判定 ---
    CheckPocketCollision();
}

void Player::Draw() {
    playerSprite_->Draw();
    // 左クリック押下中のみ矢印表示
    if (input_->IsPressMouse(0)) {
        playerArrowSprite_->Draw();
    }

    // === HPゲージ ===
    if (hpBackSprite_) {

        hpBackSprite_->Draw();
    }
    if (hpGaugeSprite_) {
        float hpPercent = (float)currentHp_ / maxHp_;
        hpGaugeSprite_->SetSize({ barWidth * hpPercent, barHeight });

        // 位置は背景の左端に固定する
        hpGaugeSprite_->SetPosition({ barX, barY });

        hpGaugeSprite_->Draw();
    }
}

void Player::CheckPocketCollision() {
    if (invincibleTimer_ > 0) return; // 無敵中はスキップ

    Vector2 pockets[6] = {
        { 220, 290 },   // 左上
        { 1000, 250 },  // 右上
        { 202, 632 },   // 左下
        { 1000, 632 },  // 右下
        { 600, 250 },   // 上中央
        { 610, 660 }    // 下中央
    };

    float pocketRadius = 38.0f;

    for (int i = 0; i < 6; i++) {
        float dx = pos.x - pockets[i].x;
        float dy = pos.y - pockets[i].y;
        float distSq = dx * dx + dy * dy;

        if (distSq < pocketRadius * pocketRadius) {
            // ★ ダメージを受ける
            TakeDamage(1);
            invincibleTimer_ = 60; // 約1秒の無敵時間（60fps想定）

            // ★ ランダムで別のポケットを選択
            int newPocket = i;
            while (newPocket == i) {
                newPocket = rand() % 6;
            }

            // 上側ポケットなら少し下に、下側なら少し上に出す
            Vector2 spawnPos = pockets[newPocket];
            if (spawnPos.y < 400) {
                spawnPos.y += 50;
            }
            else {
                spawnPos.y -= 50;
            }

            pos = spawnPos;
            playerSprite_->SetPosition(pos);

            break;
        }
    }
}
