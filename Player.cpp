#include "Player.h"
#include <algorithm>
#include <cmath>
#include "DamageText.h"
#include"imgui/imgui.h"
#include "Boss.h"
#include "Field.h"
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
    
    nextStrikeTexture_ = TextureManager::Load("YOURTURN2.png");
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
	hphartTex_ = TextureManager::Load("Hart.png");

    hpBackSprite_.reset(Sprite::Create(hpBackTex_, { barX, barY }));
    hpGaugeSprite_.reset(Sprite::Create(hpGaugeTex_, { barX, barY }));
    hpHartSprite_.reset(Sprite::Create(hphartTex_, { 380, 732 }));

    hpBackSprite_->SetSize({ barWidth, barHeight });
    hpGaugeSprite_->SetSize({ barWidth, barHeight });
    // スプライトのサイズと半径を統一
    playerSprite_->SetSize({ 32, 32 });

    damagePos[0] = { 900,750 };
    damagePos[1] = { 850,750 };

    // 0〜9のテクスチャ読み込み
    for (int i = 0; i <= 9; ++i) {
        damageText[i] = TextureManager::Load("Damege_" + std::to_string(i) + ".png");
    }

    // 1〜9のダメージ表示（位置: 800,150）
    for (int i = 0; i <= 9; ++i) {
        damageSprite[i] = Sprite::Create(damageText[i], { damagePos[0] }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
    }

    // 特別な位置の1（位置: 900,500）
    damageSprite[10] = Sprite::Create(damageText[1], { 900, 500 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });

    // 10〜90のダメージ表示（位置: 750,150）
    for (int i = 1; i <= 9; ++i) {
        damageSprite[10 + i] = Sprite::Create(damageText[i], { damagePos[1] }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
    }

  

    damageCooltime = 0;

    gameOverText = TextureManager::Load("GAMEOVER.png");
    gameOverSprite = Sprite::Create(gameOverText, { 640,370 }, { 1,1,1,1 }, { 0.5f,0.5f });

    gameButton = TextureManager::Load("Back.png");
    gameButtonSprite.reset(Sprite::Create(gameButton, { 0,0 }, { 1,1,1,1 }, { 0.0f,0.0f }));

    //ボスに応じてプレイヤーのダメージに変化をもたらす時はここのplayerDamageをいじれば変わる
    if (boss_ && boss_->GetType() == BossType::SlimeKing)
    {
        playerDamage = slimeDamage;
    }
    else if (boss_ && boss_->GetType() == BossType::Dragon)
    {
        playerDamage = dragonDamage;
    }

    isSceneEnd_ = false;
    isChange = false;  //このフラグを削除するとターンごとにエリアを変える処理の一部がなくなります
    boss_ = new Boss();
}

void Player::TakeDamage(int damage) {
    currentHp_ -= damage;
    damage_ = damage;
    if (currentHp_ <= 0) {
        currentHp_ = 0;
    }
    // ★ HPバーを揺らす
    hpBarShaking_ = true;
    hpBarShakeTimer_ = 20; // 揺れるフレーム数
    isDamage = false;
}

void Player::Update() {

   
        Vector2 mousePos = input_->GetMousePosition();

    // --- WASDで移動 ---
  /*  const float accel = 0.5f;
    if (input_->PushKey(DIK_W)) vel_.y -= accel;
    if (input_->PushKey(DIK_S)) vel_.y += accel;
    if (input_->PushKey(DIK_A)) vel_.x -= accel;
    if (input_->PushKey(DIK_D)) vel_.x += accel;*/

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
                playerArrowSprite_->SetSize({ drawRadius_ + 40 * 1.5f * scale, drawRadius_ + 40 * 1.5f * scale });
                Vector2 offset = { 0.0f, 0.0f };
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

        // --- 最大速度制限 ---
        const float maxSpeed = 35.0f; // 最大速度
        float speed = std::sqrt(vel_.x * vel_.x + vel_.y * vel_.y);
        if (speed > maxSpeed) {
            float scale = maxSpeed / speed;
            vel_.x *= scale;
            vel_.y *= scale;
        }

        // --- 位置更新 ---
        pos += vel_;

        // --- 画面端で反射 ---
        const float left = 240.0f;
        const float right = 1040.0f;
        const float top = 290.0f;
        const float bottom = 670.0f;

        if (pos.x < left) { pos.x = left; vel_.x *= -1.0f; }
        if (pos.x > right) { pos.x = right; vel_.x *= -1.0f; }
        if (pos.y < top) { pos.y = top; vel_.y *= -1.0f; }
        if (pos.y > bottom) { pos.y = bottom; vel_.y *= -1.0f; }

        // 無敵時間を減算
        if (invincibleTimer_ > 0) {
            invincibleTimer_--;
        }
        // HPバーの揺れ更新
        if (hpBarShaking_) {
            hpBarShakeTimer_--;
            if (hpBarShakeTimer_ <= 0) {
                hpBarShaking_ = false;
            }
        }

    playerSprite_->SetPosition(pos);

    if (currentHp_ <= 0)
    {
        //マウスの座標を取得
        GetCursorPos(&mousePosition);
        HWND hwnd = WinApp::GetInstance()->GetHwnd();
        ScreenToClient(hwnd, &mousePosition);
        if (mousePosition.x >= 480 && mousePosition.x <= 765 && mousePosition.y >= 420 && mousePosition.y <= 560 && input_->IsPressMouse(WM_LBUTTONDOWN == 0))
        {
            isSceneEnd_ = true;
        }
    }

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
       

    nextStrikeSprite_->SetPosition(nextStriket_);

    if (ballspeed0 == false && IsStopped() == false)
    {
        nextStriket_ = { -400,400 };
        strikeWaitTimer_ = 60; // 60フレーム(=約1秒)待機
        NextStop = true;
        isChange = false;  //このフラグを削除するとターンごとにエリアを変える処理の一部がなくなります
    }
    //このフラグを削除するとターンごとにエリアを変える処理の一部がなくなります
    if (ballspeed0 == true && IsStopped() == true&&isChange==false)
    {
        field_->GenerateRandomNumber();
        isChange = true;
    }
}


  

void Player::Draw() {
    
        // 左クリック押下中のみ矢印表示
        if (dragging_ == true && ballspeed0 == true && IsStopped() == true) {
            playerArrowSprite_->Draw();
        }

        playerSprite_->Draw();
    
    // === HPゲージ ===
    if (hpBackSprite_) {
        float shakeX = 0.0f;
        float shakeY = 0.0f;
        if (hpBarShaking_) {
            shakeX = (rand() % 5 - 2) * hpBarShakeStrength_ * 0.1f;
            shakeY = (rand() % 5 - 2) * hpBarShakeStrength_ * 0.1f;
        }

        hpBackSprite_->SetPosition({ barX + shakeX, barY + shakeY });
        hpBackSprite_->Draw();
        hpHartSprite_->Draw();

        float hpPercent = (float)currentHp_ / maxHp_;
        hpGaugeSprite_->SetSize({ barWidth * hpPercent, barHeight });
        hpGaugeSprite_->SetPosition({ barX + shakeX, barY + shakeY });
        hpGaugeSprite_->Draw();
    }
    if (isDamage == true)
    {
        DamageTextDraw();
    }
    
    if (currentHp_ >= 1)
    {
        if (ballspeed0 == true && IsStopped() == true)
        {
            nextStrikeSprite_->Draw();
        }
    }
}

void Player::DamageTextDraw()
{
    damageCooltime++;

    if (damageCooltime >= 1 && damageCooltime <= 50) {
        int ones = damage_ % 10;      // 一の位（0〜9）
        int tens = damage_ / 10;      // 十の位（0〜9）

        // 一の位の描画（damageSprite[0]〜[9]）
        if (damage_ >= 0 && damage_ <= 99) {
            damageSprite[ones]->Draw();
        }

        // 十の位が1以上なら、damageSprite[11]〜[19]を描画
        if (damage_ >= 10 && damage_ <= 99) {
            damageSprite[10 + tens]->Draw();
        }
    }
 
    if (damageCooltime >= 50)
    {
        isDamage = false;
        damageCooltime = 0;
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
       { 242, 293 },   // 左上
       { 1039, 293 },  // 右上
       { 242, 672 },   // 左下
       { 1039, 672 },  // 右下
       { 641, 293 },   // 上中央
       { 641, 672 }    // 下中央
    };

    float pocketRadius = 36.0f;

    for (int i = 0; i < 6; i++) {
        float dx = pos.x - pockets[i].x;
        float dy = pos.y - pockets[i].y;
        float distSq = dx * dx + dy * dy;

        if (distSq < pocketRadius * pocketRadius) {
            // ★ ダメージを受ける
            TakeDamage(playerDamage);
            invincibleTimer_ = 60; // 約1秒の無敵時間（60fps想定）
            isDamage = true;
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


void Player::GameOver()
{
    if (currentHp_ <= 0)
    {
        //マウスの座標を取得
        GetCursorPos(&mousePosition);
        HWND hwnd = WinApp::GetInstance()->GetHwnd();
        ScreenToClient(hwnd, &mousePosition);
        if (mousePosition.x >= 480 && mousePosition.x <= 765 && mousePosition.y >= 420 && mousePosition.y <= 560 && input_->IsPressMouse(WM_LBUTTONDOWN == 0))
        {
            isSceneEnd_ = true;
        }
    }

    if (boss_->GetHp() >= 1)
    {
        // --- nextStriket_ の動き制御 ---
        if (!strikeWaiting_ && ballspeed0 == true && IsStopped() == true) {
            // 動かす
            nextStriket_.x += nextStriketSpeed;

            // 特定座標に到達したら待機開始
            if (nextStriket_.x >= strikeTargetX_ && NextStop == true) {
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
    }
}

void Player::GameDraw()
{
    if (currentHp_ <= 1 && boss_->GetHp() >= 1)
    {
        gameOverSprite->Draw();
        gameButtonSprite->Draw();
    }
}

bool Player::IsStopped() const {
    const float threshold = 0.01f; // 停止判定の閾値
    // 止まっているなら true、動いているなら false
    return (std::abs(vel_.x) < threshold && std::abs(vel_.y) < threshold);
}

