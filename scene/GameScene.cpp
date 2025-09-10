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
	player_->Initialize(input_, { 300.0f, 450.0f }, 32.0f);

	ball_ = new Ball();
	ball_->Initialize(textureHandle_);

	//ビリヤード台
	billiardstable_ = std::make_unique<Billiardstable>();
	billiardstable_->Initialize();

	//ボス
	boss_ = std::make_unique<Boss>();
	boss_->Initialize(input_);

	//フィールドのエリア
	field_ = std::make_unique<Field>();
	field_->Initialize();
	field_->SetBalls(ball_);
	field_->SetPlayer(player_.get());

	damageText_ = std::make_unique<DamageText>();
	damageText_->Initialize();
	isSceneEnd_ = false;
	ball_->SetField(field_.get());
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
		field_->GenerateRandomNumber();
		testDamage = 0;
		damage = 0;
	}
	boss_->Update();

	if (player_->IsSceneEnd() || boss_->IsSceneEnd())
	{
		isSceneEnd_ = true;
	}
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
	
		ball_->Draw();
		player_->Draw();
	}
	boss_->Draw();

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