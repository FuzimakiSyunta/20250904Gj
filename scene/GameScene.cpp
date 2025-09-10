#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//プレイヤー
	player_ = std::make_unique<Player>();

	ball_ = new Ball();
	ball_->Initialize(textureHandle_);

	//ビリヤード台
	billiardstable_ = std::make_unique<Billiardstable>();
	billiardstable_->Initialize();

	//ボス
	boss_ = std::make_unique<Boss>();
	boss_->Initialize(input_);
	player_->SetBoss(boss_.get());
	player_->Initialize(input_, { 300.0f, 450.0f }, 32.0f);

	ballCollideHandle_ = audio_->LoadWave("/sound/SE/collide_ball.wav");
	fallPocketHandle_ = audio_->LoadWave("/sound/SE/fallsound.wav");

	backSoundHandle_ = audio_->LoadWave("/sound/SE/backMusic.mp3");
	audio_->PlayWave(backSoundHandle_, true, 1.0f);
	//フィールドのエリア
	field_ = std::make_unique<Field>();
	field_->Initialize();
	field_->SetBoss(boss_.get());
	field_->SetBalls(ball_);
	field_->SetPlayer(player_.get());
	player_->SetField(field_.get());

	damageText_ = std::make_unique<DamageText>();
	damageText_->Initialize();
	isSceneEnd_ = false;
	ball_->SetField(field_.get());

	color = { 0,0,0,1 };
	fadeColor = 0.01f;
	fadeFlag = false;
	fadeOutTexture = TextureManager::Load("uvChecker.png");
	fadeOutSprite_.reset(Sprite::Create(fadeOutTexture, { 640,420 }, color, { 0.5f,0.5f }));
	fadeOutSprite_->SetSize({ 1280,920 });
	isFade = false;
}

void GameScene::Update(){
	player_->SetBallSpeed0(ball_->AreAllBallsStopped());
	player_->Update();
	ball_->Update();
	ball_->CheckPlayerCollision(*player_);
	damage = ball_->CheckPocketCollisions();
	damageText_->Update();
	if (damage > 0) {
		damageText_->IsDamage();
		field_->SetDamage(damage);
		field_->Update();
		testDamage = field_->GetDamage();
		damageText_->SetDamage(testDamage);
		boss_->TakeDamage(testDamage);
		//field_->GenerateRandomNumber();  //このコメントを復活させるとポケットに入るごとにエリアが変わります。
		testDamage = 0;
		damage = 0;
	}
	boss_->Update();
	//turnChange();  //ターンが変わるごとにエリアを変える
	FadeOut(); //シーン遷移する時の演出をする処理
	
	// 衝突判定
	//hitBall = ball_->CheckCollisions();
	//hitPlayer = ball_->CheckPlayerCollision(*player_);
	//fallPocket = ball_->CheckPocketCollisions();

	//// === 衝突の「瞬間」だけ音を鳴らす ===
	//if (hitBall && !wasHitBall_) {
	//	audio_->PlayWave(ballCollideHandle_, false, 1.0f);
	//}
	//if (hitPlayer && !wasHitPlayer_) {
	//	audio_->PlayWave(ballCollideHandle_, false, 1.0f);
	//}
	//if (fallPocket && !wasHitPocket_) {
	//	audio_->PlayWave(fallPocketHandle_, false, 1.0f);
	//}

	// 状態を保存
	wasHitBall_ = hitBall;
	wasHitPlayer_ = hitPlayer;
	wasHitPocket_ = fallPocket;

	// ★ 衝突が終わったらリセット
	if (!hitBall)   wasHitBall_ = false;
	if (!hitPlayer) wasHitPlayer_ = false;
	if (!fallPocket) wasHitPocket_ = false;

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	billiardstable_->Draw();
	field_->Draw();
	damageText_->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	if (player_->GetHp()>=1 ||boss_->GetHp()>=1 )
	{
		player_->Draw();
		ball_->Draw();
	}
	boss_->Draw();
	fadeOutSprite_->Draw();
	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Reset()
{
	Initialize();
}

void GameScene::FadeOut()
{
	if (player_->IsSceneEnd() || boss_->IsSceneEnd())
	{
		isFade = true;
	}

	if (fadeFlag == false)
	{
		color.w -= fadeColor;
		fadeOutSprite_->SetColor(color);
	}
	if (color.w <= 0 && fadeFlag == false)
	{
		fadeFlag = true;
	}

	if (isFade == true)
	{
		color.w += fadeColor;
		fadeOutSprite_->SetColor(color);
	}
	if (color.w >= 1 && isFade == true)
	{
		isSceneEnd_ = true;
	}
}

