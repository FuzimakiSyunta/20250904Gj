#include "Player.h"
#include <algorithm>


void Player::Initialize(Input* input, const Vector2& startPos, float radius) {
    input_ = input;
    pos = startPos;
    drawRadius_ = radius;              // 例: 16 → 直径32pxで描画
    collisionRadius_ = radius;  // ★ 当たり判定だけ60%に縮小
    vel_ = { 0.0f, 0.0f };

    dragging_ = false;

    // プレイヤー
    playerTexture_ = TextureManager::Load("PlayerBall.png");
    playerSprite_.reset(Sprite::Create(playerTexture_, pos, { 1,1,1,1 }, { 0.5f, 0.5f }));
    playerSprite_->SetPosition(pos);
    
    nextStrikeTexture_ = TextureManager::Load("YOURTURN.png");
    nextStrikeSprite_.reset(Sprite::Create(nextStrikeTexture_, nextStriket_, { 1,1,1,1 } ,{ 0.5f, 0.5f }));
   
    // 矢印（初期回転45°）
    playerArrowTexture = TextureManager::Load("arrow.png");
    playerArrowSprite_.reset(Sprite::Create(playerArrowTexture, pos, { 1,1,1,1 }, { 0.5f, 0.5f }));
    playerArrowSprite_->SetSize({ radius_ * 2.0f, radius_ * 2.0f });
    
    playerSprite_->SetSize({ radius_ * 2.0f, radius_ * 2.0f });
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
   
   

}

void Player::TakeDamage(int damage) {
    currentHp_ -= damage;
    if (currentHp_ <= 0) {
        currentHp_ = 0;
    }
}

void Player::Update() {
    

    Vector2 mousePos = input_->GetMousePosition();

    // --- WASDで移動 ---
    const float accel = 0.5f;
    if (input_->PushKey(DIK_W)) vel_.y -= accel;
    if (input_->PushKey(DIK_S)) vel_.y += accel;
    if (input_->PushKey(DIK_A)) vel_.x -= accel;
    if (input_->PushKey(DIK_D)) vel_.x += accel;

    // --- ボールがすべて停止している場合のみドラッグ処理 ---
   
    if (ballspeed0 == true && IsStopped() == true)
    {
        // ドラッグ開始
        if (input_->IsTriggerMouse(0)) 
        {
            dragging_ = true;
            dragStart_ = mousePos;
        }
        
        // ドラッグ中
        if (!arrowFlying_ && !arrowReturning_ && dragging_ && input_->IsPressMouse(0)) 
        {
            dragCurrent_ = mousePos;

            Vector2 diff = { dragStart_.x - dragCurrent_.x, dragStart_.y - dragCurrent_.y };
            float length = sqrtf(diff.x * diff.x + diff.y * diff.y);
            float angle = atan2f(diff.y, diff.x);

            playerArrowSprite_->SetRotation(angle);
            float scale = std::clamp(length / 100.0f, 0.5f, 3.0f);
            playerArrowSprite_->SetSize({ drawRadius_ * 2.0f * scale, drawRadius_ * 2.0f * scale });
            Vector2 offset = { 10.0f, 30.0f };
            playerArrowSprite_->SetPosition({ pos.x + offset.x, pos.y + offset.y });
        }
       
        // ドラッグ終了
        if (dragging_ && !input_->IsPressMouse(0)) {
            dragging_ = false;
            Vector2 diff = { dragStart_.x - mousePos.x, dragStart_.y - mousePos.y };
            const float power = 0.1f;
            vel_.x = diff.x * power;
            vel_.y = diff.y * power;
           
        }
    }

    // --- 摩擦 ---
    vel_ *= 0.98f;

    // --- 位置更新 ---
    pos += vel_;

    // --- 画面端で反射 ---
    const float left = 235.0f;
    const float right = 1050.0f;
    const float top = 280.0f;
    const float bottom = 680.0f;

    if (pos.x < left) { pos.x = left; vel_.x *= -1.0f; }
    if (pos.x > right) { pos.x = right; vel_.x *= -1.0f; }
    if (pos.y < top) { pos.y = top; vel_.y *= -1.0f; }
    if (pos.y > bottom) { pos.y = bottom; vel_.y *= -1.0f; }

    // 無敵時間を減算
    if (invincibleTimer_ > 0) {
        invincibleTimer_--;
    }
    ////  プレイヤースプライト更新 

    playerSprite_->SetPosition(pos);

    CheckPocketCollision();
   
    // --- nextStriket_ の動き制御 ---
    if (!strikeWaiting_&&ballspeed0 == true && IsStopped() == true) {
        // 動かす
        nextStriket_.x += nextStriketSpeed;

        // 特定座標に到達したら待機開始
        if (nextStriket_.x >= strikeTargetX_&& NextStop == true) {
            nextStriket_.x = strikeTargetX_; // 位置をピッタリ固定
            strikeWaiting_ = true;
            strikeWaitTimer_ = 60;
            NextStop = false;
            
        }
    }
    else {
        // 待機中
        strikeWaitTimer_--;
        if (strikeWaitTimer_ <= 0) {
            strikeWaiting_ = false; // 待機終了 → 動き出す
        }
       

    }

    nextStrikeSprite_->SetPosition(nextStriket_);

    if(ballspeed0 == false && IsStopped() == false)
    {
        nextStriket_ = { -400,400 };
        strikeWaitTimer_ = 60; // 60フレーム(=約1秒)待機
        NextStop = true;
    }
   
}


  

void Player::Draw() {
    playerSprite_->Draw();
    // 左クリック押下中のみ矢印表示
    if (dragging_ == true && ballspeed0 == true && IsStopped() == true) {
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

    if (ballspeed0 == true && IsStopped() == true)
    {
        nextStrikeSprite_->Draw();
    }

}

void Player::CheckPocketCollision() {
    if (invincibleTimer_ > 0) return; // 無敵中はスキップ

    //ここ
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


bool Player::IsStopped() const {
    const float threshold = 0.01f; // 停止判定の閾値
    // 止まっているなら true、動いているなら false
    return (std::abs(vel_.x) < threshold && std::abs(vel_.y) < threshold);
}
