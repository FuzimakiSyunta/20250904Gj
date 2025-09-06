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

	void TakeDamage(int damage);  // ダメージを受ける
	int GetHp() const { return currentHp_; }

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
private://HPゲージ
	uint32_t hpBackTex_ = 0u;
	uint32_t hpGaugeTex_ = 0u;
	std::unique_ptr<Sprite> hpBackSprite_;
	std::unique_ptr<Sprite> hpGaugeSprite_;
	bool isDebugdamage_ = false;
	int maxHp_ = 100;        // 最大HP
	int currentHp_ = 100;    // 現在HP
	bool isDead_ = false;    // 死亡フラグ
};

