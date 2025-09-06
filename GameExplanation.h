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
#include "Scene.h"
class GameExplanation
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameExplanation();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameExplanation();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsSceneEnd() { return isSceneEnd_; }
	Scene::SceneType NextScene() { return Scene::SceneType::kGamePlay; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	Sprite* explanationSprite = nullptr;
	Vector2 pos;
	bool isSceneEnd_ = false;
	POINT mousePosition;

	int sceneCooltime; //シーンに移り変わった時一瞬だけクールタイムを用意し連続で移り変わらないようにする
};

