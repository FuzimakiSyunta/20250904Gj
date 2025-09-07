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

	Sprite* damageSprite[20];
	bool isDamage;
	int damageCooltime;

	int damage_;
};

