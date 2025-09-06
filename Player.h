#include "Sprite.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "Input.h"

class Player
{
public:
	
	void Initialize(Input* input, const Vector2& startPos = { 0,0 }, float radius = 16.0f);

	void Update();

	void Draw();

	Vector2 GetPos() const { return pos; }      // const 修飾子を追加
	
	float GetRadius() const { return radius_; } // const 修飾子を追加
	Vector2 GetVel() const { return vel_; }
	void SetVel(float x, float y) { vel_ = { x, y }; }
	void SetPos(float x, float y) { pos = { x, y }; }
	void TakeDamage(int damage);

	void CheckPocketCollision();

private:
#pragma region 画像読み込み
	Input* input_ = nullptr;
	//テクスチャハンドル
	uint32_t playerTexture_ = 0;
	uint32_t playerArrowTexture = 0;
	//スプライト
	std::unique_ptr<Sprite> playerSprite_ = nullptr;
	std::unique_ptr<Sprite> playerArrowSprite_ = nullptr;
	//HPゲージ
	uint32_t hpBackTex_ = 0;
	uint32_t hpGaugeTex_ = 0;
	std::unique_ptr<Sprite> hpBackSprite_;
	std::unique_ptr<Sprite> hpGaugeSprite_;

#pragma region 座標関連

	Vector2 pos = {250,1050};
	Vector2 ArrowpPos = {pos};
	Vector2 localPos;
	const float speed = 10.6f;
	const Vector2 center = { 5, 5 };
	float collisionRadius_; // 当たり判定用（小さめに設定）
	float drawRadius_;       // 見た目用の半径
	float radius_ = 16.0f;
	Vector2 vel_ = { 0.0f, 0.0f };
	bool dragging_;
	Vector2 dragStart_;
	Vector2 dragCurrent_;

	bool arrowFlying_ = false;
	Vector2 arrowVel_;
	bool arrowReturning_ = false; // 矢印が戻っている最中か

	int maxHp_ = 7;
	int currentHp_ = 7;

	int invincibleTimer_ = 0; // 無敵時間カウンタ

	float barWidth;
	float barHeight;
	float screenWidth;   // 画面幅
	float barX; // 中央
	float barY; // Y位置指定

	// 右下にずらすオフセット
	Vector2 offset = { 4.0f, 4.0f };
};

