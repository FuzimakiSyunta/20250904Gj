#pragma once
#include <Sprite.h>
class DamageText
{
public:
	void Initialize();

	void Update();

	void IsDamage();

	void Draw();

	void PlayerDraw();

	void SetDamage(int damage) { damage_ = damage; }

private:
	uint32_t damageText[10];
	uint32_t poketTexture;

	Sprite* damageSprite[20];
	Sprite* poketSprite=nullptr;
	bool isDamage;
	int damageCooltime;

	int damage_;
};

