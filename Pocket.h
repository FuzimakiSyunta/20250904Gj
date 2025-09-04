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
	//�e�N�X�`���n���h��
	uint32_t pocketTexture_ = 0;
	//�X�v���C�g
	std::unique_ptr<Sprite> pocketSprite_ = nullptr;
};

