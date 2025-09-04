#pragma once
#include "Sprite.h"
#include "TextureManager.h"
#include "Vector2.h"
class Pocket
{
public:
	void Initialize();

	void Update();

	void Draw();

private:
	Vector2 pos = { 0,0 };
	float radius_ = 16.0f;
	//テクスチャハンドル
	uint32_t pocketTexture_ = 0;
	//スプライト
	std::unique_ptr<Sprite> pocketSprite_ = nullptr;
};

