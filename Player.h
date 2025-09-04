#include "Sprite.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "Input.h"

class Player
{
public:
	
	void Initialize();

	void Update();

	void Draw();

	Vector2 GetPos() { return pos; }
private:
#pragma region 画像読み込み

	//テクスチャハンドル
	uint32_t playerTexture_ = 0;
	//スプライト
	std::unique_ptr<Sprite> playerSprite_ = nullptr;

#pragma region 座標関連

	Vector2 pos = {0,0};
	Vector2 localPos;
	const float speed = 2.6f;
	const Vector2 center = { 5, 5 };

};

