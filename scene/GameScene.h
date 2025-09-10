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
#include "Field.h"
#include "DamageText.h"
#include "Scene.h"

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

	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

	void BGMReset();

	void BGMStop();

	bool IsSceneEnd() { return isSceneEnd_; }

	Scene::SceneType NextScene() { return Scene::SceneType::kTitle; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	uint32_t ballCollideHandle_;
	uint32_t fallPocketHandle_;
	uint32_t playSound_;
	uint32_t playfallSound_;
	uint32_t backSoundHandle_;

	std::unique_ptr<Player> player_;
	std::unique_ptr<Billiardstable> billiardstable_;
	std::unique_ptr<Boss> boss_;
	int damage = 0; // ボールのダメージ値を受け取る変数
	std::unique_ptr<Field> field_;
	std::unique_ptr<DamageText> damageText_;

	uint32_t fadeOutTexture;
	std::unique_ptr<Sprite> fadeOutSprite_;
	Vector4 color;
	float fadeColor;
	bool isFade;
	bool fadeFlag;

	int testDamage = 0;

	bool isSceneEnd_;

	bool hitBall = false;
	bool hitPlayer = false;
	bool fallPocket = false;

	Ball* ball_ = nullptr;
	uint32_t textureHandle_ = 0;

	bool wasHitBall_ = false;    // 前フレームでボール同士が衝突していたか
	bool wasHitPlayer_ = false;  // 前フレームでプレイヤーと衝突していたか
	bool wasHitPocket_ = false;  


	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
