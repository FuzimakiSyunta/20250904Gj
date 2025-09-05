#pragma once
#include "Sprite.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "Input.h"
class Boss
{
public:
	void Initialize(Input* input);
	void Update();
	void Draw();
	void OnDamage(); // ★ ダメージを受けたときに呼ぶ関数

private:
	Input* input_ = nullptr;
	//テクスチャハンドル
	uint32_t bossTexture_ = 0;
	uint32_t bossDamegeTexture_ = 0;
	//スプライト
	std::unique_ptr<Sprite> bossSprite_ = nullptr;
	std::unique_ptr<Sprite> bossDamegeSprite_ = nullptr;
	Vector2 basePos_ = { 540.0f, 40.0f }; // 元の座標
	bool isShaking_ = false;
	int shakeTimer_ = 0;
	float shakeStrength_ = 5.0f; // 揺れの強さ
private:
	bool isDebugdamage_ = false;
};

