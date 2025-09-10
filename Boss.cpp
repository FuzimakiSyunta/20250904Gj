#include "Boss.h"
#include <cstdlib> // rand()

void Boss::Initialize(Input* input) {
    input_ = input;

    // ★ 乱数シードを1回だけ初期化
    srand((unsigned int)time(nullptr));
    // === ランダムでボスタイプを決定 ===
    int bossType = rand() % 2; // 0 = スライムキング, 1 = ドラゴン

    if (bossType == 0) {
        // スライムキング
        type_ = BossType::SlimeKing;  // ← 保存
        bossTexture_ = TextureManager::Load("slimeKing.png");
        bossDamegeTexture_ = TextureManager::Load("slimeKing_Dmaege.png");
        maxHp_ = 100; // HP少なめ
    }
    else {
        // ドラゴン
        type_ = BossType::Dragon;     // ← 保存
        bossTexture_ = TextureManager::Load("dragon.png");
        bossDamegeTexture_ = TextureManager::Load("dragon_Damege.png");
        maxHp_ = 200; // HP多め
    }

    // === HPゲージ ===
    hpBackTex_ = TextureManager::Load("BossHpBack.png");
    hpGaugeTex_ = TextureManager::Load("BossHpRed.png");
    hpBackSprite_.reset(Sprite::Create(hpBackTex_, { 400, 20 }));
    hpGaugeSprite_.reset(Sprite::Create(hpGaugeTex_, { 400, 20 }));
    hpBackSprite_->SetSize({ 480, 20 });
    hpGaugeSprite_->SetSize({ 480, 20 });

    // === ボスのスプライト ===
    basePos_ = { 540.0f, 40.0f };
    bossSprite_.reset(Sprite::Create(bossTexture_, basePos_));
    bossDamegeSprite_.reset(Sprite::Create(bossDamegeTexture_, basePos_));
    bossSprite_->SetPosition(basePos_);
    bossDamegeSprite_->SetPosition(basePos_);

    // HP初期化
    currentHp_ = maxHp_;

    // === 勝利画面関連 ===
    gameClearText_ = TextureManager::Load("YOUWIN.png");
    gameClearSprite_.reset(Sprite::Create(gameClearText_, { 640,370 }, { 1,1,1,1 }, { 0.5f,0.5f }));

    gameButton = TextureManager::Load("Back.png");
    gameButtonSprite.reset(Sprite::Create(gameButton, { 0,0 }, { 1,1,1,1 }, { 0.0f,0.0f }));

    isSceneEnd_ = false;
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

    /*if (input_->PushKey(DIK_1)) { 
        if (!isDebugdamage_) {
            OnDamage();
            isDebugdamage_ = true;
        }
    }
    else if(input_->PushKey(DIK_2)){
		isDebugdamage_ = false;
    }*/
	// デバッグ用：1キーで10ダメージ
 /*   if (input_->PushKey(DIK_1)) {
        TakeDamage(10);
    }*/
    //ゲームクリア処理
    if (isDead_==true)
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
}

void Boss::Draw() {
    if (bossSprite_&&!isShaking_) {
        bossSprite_->Draw();
    }
    if (isShaking_ && bossDamegeSprite_) {
        bossDamegeSprite_->Draw();
	}
    // HPゲージを描画
    if (hpBackSprite_) {
        hpBackSprite_->Draw();
    }
    if (hpGaugeSprite_) {
        float hpPercent = (float)currentHp_ / maxHp_;
        if (hpPercent < 0.0f) hpPercent = 0.0f;

        // 横幅をHP割合に応じて縮める
        hpGaugeSprite_->SetSize({ 480 * hpPercent, 20 });
        hpGaugeSprite_->SetPosition({ 400, 20 });

        hpGaugeSprite_->Draw();
    }
    if (isDead_ == true)
    {
        gameClearSprite_->Draw();
        gameButtonSprite->Draw();
    }
}

// ★ ダメージを受けたときに呼ぶ関数
void Boss::OnDamage() {
    isShaking_ = true;
    shakeTimer_ = 20;  // 揺れるフレーム数
}

void Boss::TakeDamage(int damage) {
    if (isDead_) return;

    currentHp_ -= damage;
    if (currentHp_ < 0) currentHp_ = 0;

    if (currentHp_ == 0) {
        isDead_ = true;
        // 倒れた演出などをここに
    }
    else {
        OnDamage(); // ダメージ演出（シェイク）
    }
}
