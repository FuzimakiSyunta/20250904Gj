#include "DamageText.h"
#include <TextureManager.h>

void DamageText::Initialize()
{

	// 0〜9のテクスチャ読み込み
	for (int i = 0; i <= 9; ++i) {
		damageText[i] = TextureManager::Load("number" + std::to_string(i) + ".png");
	}

	// 1〜9のダメージ表示（位置: 800,150）
	for (int i = 0; i <= 9; ++i) {
		damageSprite[i] = Sprite::Create(damageText[i], { 800, 150 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	}

	// 特別な位置の1（位置: 900,500）
	damageSprite[10] = Sprite::Create(damageText[1], { 900, 500 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });

	// 10〜90のダメージ表示（位置: 750,150）
	for (int i = 1; i <= 9; ++i) {
		damageSprite[10 + i] = Sprite::Create(damageText[i], { 750, 150 }, { 1, 1, 1, 1 }, { 0.5f, 0.5f });
	}

	poketTexture = TextureManager::Load("pocket.png");
	poketSprite = Sprite::Create(poketTexture, { 640,410 }, { 1,1,1,1 }, { 0.5f,0.5f });
}

void DamageText::Update()
{
	if (isDamage == true)
	{
		damageCooltime++;
	}
	if (damageCooltime >= 50)
	{
		isDamage = false;
		damageCooltime = 0;
	}
}

void DamageText::IsDamage()
{
	isDamage = true;
	damageCooltime = 0;
}

void DamageText::Draw()
{

	if (damageCooltime >= 1 && damageCooltime <= 50) {
		int ones = damage_ % 10;      // 一の位（0〜9）
		int tens = damage_ / 10;      // 十の位（0〜9）

		// 一の位の描画（damageSprite[0]〜[9]）
		if (damage_ >= 0 && damage_ <= 99) {
			damageSprite[ones]->Draw();
		}

		// 十の位が1以上なら、damageSprite[11]〜[19]を描画
		if (damage_ >= 10 && damage_ <= 99) {
			damageSprite[10 + tens]->Draw();
		}
	}

	poketSprite->Draw();
}

void DamageText::PlayerDraw()
{
	damageSprite[10]->Draw();
}

