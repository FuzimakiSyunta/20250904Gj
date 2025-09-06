#pragma once
#include <Sprite.h>
class DamageText
{
public:
	void Initialize();

	void Update();

	void Draw();

private:
	uint32_t damageText;

	Sprite* damageSprite = nullptr;
};

