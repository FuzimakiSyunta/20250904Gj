#include "DamageText.h"
#include <TextureManager.h>

void DamageText::Initialize()
{
	damageText[0] = TextureManager::Load("number0.png");
	damageText[1] = TextureManager::Load("number1.png");
	damageText[2] = TextureManager::Load("number2.png");
	damageText[3] = TextureManager::Load("number3.png");
	damageText[4] = TextureManager::Load("number4.png");
	damageText[5] = TextureManager::Load("number5.png");
	damageText[6] = TextureManager::Load("number6.png");
	damageText[7] = TextureManager::Load("number7.png");
	damageText[8] = TextureManager::Load("number8.png");
	damageText[9] = TextureManager::Load("number9.png");
	//1から9までのダメージ数値
	damageSprite[0] = Sprite::Create(damageText[0], { 800,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[1] = Sprite::Create(damageText[1], { 800,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[2] = Sprite::Create(damageText[2], { 800,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[3] = Sprite::Create(damageText[3], { 800,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[4] = Sprite::Create(damageText[4], { 800,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[5] = Sprite::Create(damageText[5], { 800,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[6] = Sprite::Create(damageText[6], { 800,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[7] = Sprite::Create(damageText[7], { 800,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[8] = Sprite::Create(damageText[8], { 800,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[9] = Sprite::Create(damageText[9], { 800,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[10] = Sprite::Create(damageText[1], { 900,500 }, { 1,1,1,1 }, { 0.5f,0.5f });
	//10から90までのダメージ数値
	damageSprite[11] = Sprite::Create(damageText[1], { 750,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[12] = Sprite::Create(damageText[2], { 750,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[13] = Sprite::Create(damageText[3], { 750,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[14] = Sprite::Create(damageText[4], {750,150}, {1,1,1,1}, {0.5f,0.5f});
	damageSprite[15] = Sprite::Create(damageText[5], { 750,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[16] = Sprite::Create(damageText[6], { 750,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[17] = Sprite::Create(damageText[7], { 750,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[18] = Sprite::Create(damageText[8], { 750,150 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[19] = Sprite::Create(damageText[9], { 750,150 }, { 1,1,1,1 }, { 0.5f,0.5f });

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
	if (damageCooltime >= 1&&damageCooltime<=50)
	{
		if (damage_ == 0||damage_ == 10 || damage_ == 20 || damage_ == 30 || damage_ == 40 || damage_ == 50 || damage_ == 60 || damage_ == 70 || damage_ == 80 || damage_ == 90)
		{
			damageSprite[0]->Draw();
		}
		else if (damage_ == 1 || damage_ == 11 || damage_ == 21 || damage_ == 31 || damage_ == 41 || damage_ == 51 || damage_ == 61 || damage_ == 71 || damage_ == 81 || damage_ == 91)
		{
			damageSprite[1]->Draw();
		}
		else if (damage_ == 2 || damage_ == 12 || damage_ == 22 || damage_ == 32 || damage_ == 42 || damage_ == 52 || damage_ == 62 || damage_ == 72 || damage_ == 82 || damage_ == 92)
		{
			damageSprite[2]->Draw();
		}
		else if (damage_ == 3 || damage_ == 13 || damage_ == 23 || damage_ == 33 || damage_ == 43 || damage_ == 53 || damage_ == 63 || damage_ == 73 || damage_ == 83 || damage_ == 93)
		{
			damageSprite[3]->Draw();
		}
		else if (damage_ == 4 || damage_ == 14 || damage_ == 24 || damage_ == 34 || damage_ == 44 || damage_ == 54 || damage_ == 64 || damage_ == 74 || damage_ == 84 || damage_ == 94)
		{
			damageSprite[4]->Draw();
		}
		else if (damage_ == 5 || damage_ == 15 || damage_ == 25 || damage_ == 35 || damage_ == 45 || damage_ == 55 || damage_ == 65 || damage_ == 75 || damage_ == 85 || damage_ == 95)
		{
			damageSprite[5]->Draw();
		}
		else if (damage_ == 6 || damage_ == 16 || damage_ == 26 || damage_ == 36 || damage_ == 46 || damage_ == 56 || damage_ == 66 || damage_ == 76 || damage_ == 86 || damage_ == 96)
		{
			damageSprite[6]->Draw();
		}
		else if (damage_ == 7 || damage_ == 17 || damage_ == 27 || damage_ == 37 || damage_ == 47 || damage_ == 57 || damage_ == 67 || damage_ == 77 || damage_ == 87 || damage_ == 97)
		{
			damageSprite[7]->Draw();
		}
		else if (damage_ == 8 || damage_ == 18 || damage_ == 28 || damage_ == 38 || damage_ == 48 || damage_ == 58 || damage_ == 68 || damage_ == 78 || damage_ == 88 || damage_ == 98)
		{
			damageSprite[8]->Draw();
		}
		else if (damage_ == 9 || damage_ == 19 || damage_ == 29 || damage_ == 39 || damage_ == 49 || damage_ == 59 || damage_ == 69 || damage_ == 79 || damage_ == 89 || damage_ == 99)
		{
			damageSprite[9]->Draw();
		}

		if (damage_ >= 10 && damage_ <= 19)
		{
			damageSprite[11]->Draw();
		}
		else if (damage_ >= 20 && damage_ <= 29)
		{
			damageSprite[12]->Draw();
		}
		else if (damage_ >= 30 && damage_ <= 39)
		{
			damageSprite[13]->Draw();
		}
		else if (damage_ >= 40 && damage_ <= 49)
		{
			damageSprite[14]->Draw();
		}
		else if (damage_ >= 50 && damage_ <= 59)
		{
			damageSprite[15]->Draw();
		}
		else if (damage_ >= 60 && damage_ <= 69)
		{
			damageSprite[16]->Draw();
		}
		else if (damage_ >= 70 && damage_ <= 79)
		{
			damageSprite[17]->Draw();
		}
		else if (damage_ >= 80 && damage_ <= 89)
		{
			damageSprite[18]->Draw();
		}
		else if (damage_ >= 90 && damage_ <= 99)
		{
			damageSprite[19]->Draw();
		}

	}

	poketSprite->Draw();
}

void DamageText::PlayerDraw()
{
	damageSprite[10]->Draw();
}

