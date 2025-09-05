#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Billiardstable.h"
#include "Ball.h"
#include "Boss.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	std::unique_ptr<Player> player_;
	std::unique_ptr<Billiardstable> billiardstable_;
	std::unique_ptr<Boss> boss_;
	int damage = 0; // ボールのダメージ値を受け取る変数

	Ball* ball_ = nullptr;
	uint32_t textureHandle_ = 0;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
