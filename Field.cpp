#include "Field.h"
#include <stdlib.h>
#include <stdio.h>
#include <TextureManager.h>
#include "Ball.h"
#include <time.h>

void Field::Initialize()
{
	input_ = Input::GetInstance();
	for (int i = 0; i < 4; i++)
	{
		areaNumber[i] = rand()%100+1;
	}
	texttexture[0] = TextureManager::Load("HpDown.png");
	texttexture[1] = TextureManager::Load("PowerDown.png");
	texttexture[2] = TextureManager::Load("PowerUp.png");
	
	testSprite[0] = Sprite::Create(texttexture[1], pos[0], {1,1,1,1}, {0.5f,0.5f});
	testSprite[1] = Sprite::Create(texttexture[1], pos[1], { 1,1,1,1 }, { 0.5f,0.5f });
	testSprite[2] = Sprite::Create(texttexture[1], pos[2], { 1,1,1,1 }, { 0.5f,0.5f });
	testSprite[3] = Sprite::Create(texttexture[1], pos[3], { 1,1,1,1 }, { 0.5f,0.5f });

	testSprite[4] = Sprite::Create(texttexture[2], pos[4], {1,1,1,1}, {0.5f,0.5f});
	testSprite[5] = Sprite::Create(texttexture[2], pos[5], { 1,1,1,1 }, { 0.5f,0.5f });
	testSprite[6] = Sprite::Create(texttexture[2], pos[6], { 1,1,1,1 }, { 0.5f,0.5f });
	testSprite[7] = Sprite::Create(texttexture[2], pos[7], { 1,1,1,1 }, { 0.5f,0.5f });

	testSprite[8] = Sprite::Create(texttexture[0], pos[8], {1,1,1,1}, {0.5f,0.5f});
	testSprite[9] = Sprite::Create(texttexture[0], pos[9], { 1,1,1,1 }, { 0.5f,0.5f });
	testSprite[10] = Sprite::Create(texttexture[0], pos[10], { 1,1,1,1 }, { 0.5f,0.5f });
	testSprite[11] = Sprite::Create(texttexture[0], pos[11], { 1,1,1,1 }, { 0.5f,0.5f });

	for (int i = 0; i < 12; i++)
	{
		testSprite[i]->SetSize({ 419,212 });
	}

	areaCooltime=0;

	for (int i = 0; i < 12; i++)
	{
		isArea[i] = false;
	}



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

	//1左上

	//1から9までのダメージ数値
	damageSprite[0] = Sprite::Create(damageText[0], { 202,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[1] = Sprite::Create(damageText[1], { 202,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[2] = Sprite::Create(damageText[2], { 202,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[3] = Sprite::Create(damageText[3], { 202,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[4] = Sprite::Create(damageText[4], { 202,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[5] = Sprite::Create(damageText[5], { 202,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[6] = Sprite::Create(damageText[6], { 202,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[7] = Sprite::Create(damageText[7], { 202,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[8] = Sprite::Create(damageText[8], { 202,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[9] = Sprite::Create(damageText[9], { 202,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	//damageSprite[10] = Sprite::Create(damageText[1], { 202,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	//10から90までのダメージ数値
	damageSprite[11] = Sprite::Create(damageText[1], { 152,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[12] = Sprite::Create(damageText[2], { 152,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[13] = Sprite::Create(damageText[3], { 152,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[14] = Sprite::Create(damageText[4], { 152,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[15] = Sprite::Create(damageText[5], { 152,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[16] = Sprite::Create(damageText[6], { 152,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[17] = Sprite::Create(damageText[7], { 152,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[18] = Sprite::Create(damageText[8], { 152,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[19] = Sprite::Create(damageText[9], { 152,250 }, { 1,1,1,1 }, { 0.5f,0.5f });

	//2左下

	//1から9までのダメージ数値
	damageSprite[20] = Sprite::Create(damageText[0], { 202,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[21] = Sprite::Create(damageText[1], { 202,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[22] = Sprite::Create(damageText[2], { 202,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[23] = Sprite::Create(damageText[3], { 202,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[24] = Sprite::Create(damageText[4], { 202,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[25] = Sprite::Create(damageText[5], { 202,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[26] = Sprite::Create(damageText[6], { 202,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[27] = Sprite::Create(damageText[7], { 202,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[28] = Sprite::Create(damageText[8], { 202,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[29] = Sprite::Create(damageText[9], { 202,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[30] = Sprite::Create(damageText[0], { 900,500 }, { 1,1,1,1 }, { 0.5f,0.5f });
	//10から90までのダメージ数値
	damageSprite[31] = Sprite::Create(damageText[1], { 152,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[32] = Sprite::Create(damageText[2], { 152,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[33] = Sprite::Create(damageText[3], { 152,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[34] = Sprite::Create(damageText[4], { 152,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[35] = Sprite::Create(damageText[5], { 152,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[36] = Sprite::Create(damageText[6], { 152,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[37] = Sprite::Create(damageText[7], { 152,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[38] = Sprite::Create(damageText[8], { 152,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[39] = Sprite::Create(damageText[9], { 152,632 }, { 1,1,1,1 }, { 0.5f,0.5f });

	//3右下

	//1から9までのダメージ数値
	damageSprite[40] = Sprite::Create(damageText[0], { 1010,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[41] = Sprite::Create(damageText[1], { 1010,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[42] = Sprite::Create(damageText[2], { 1010,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[43] = Sprite::Create(damageText[3], { 1010,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[44] = Sprite::Create(damageText[4], { 1010,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[45] = Sprite::Create(damageText[5], { 1010,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[46] = Sprite::Create(damageText[6], { 1010,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[47] = Sprite::Create(damageText[7], { 1010,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[48] = Sprite::Create(damageText[8], { 1010,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[49] = Sprite::Create(damageText[9], { 1010,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[50] = Sprite::Create(damageText[0], { 900,500 }, { 1,1,1,1 }, { 0.5f,0.5f });
	//10から90までのダメージ数値
	damageSprite[51] = Sprite::Create(damageText[1], { 960,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[52] = Sprite::Create(damageText[2], { 960,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[53] = Sprite::Create(damageText[3], { 960,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[54] = Sprite::Create(damageText[4], { 960,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[55] = Sprite::Create(damageText[5], { 960,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[56] = Sprite::Create(damageText[6], { 960,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[57] = Sprite::Create(damageText[7], { 960,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[58] = Sprite::Create(damageText[8], { 960,632 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[59] = Sprite::Create(damageText[9], { 960,632 }, { 1,1,1,1 }, { 0.5f,0.5f });

	//4右上

	//1から9までのダメージ数値
	damageSprite[60] = Sprite::Create(damageText[0], { 1000,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[61] = Sprite::Create(damageText[1], { 1000,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[62] = Sprite::Create(damageText[2], { 1000,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[63] = Sprite::Create(damageText[3], { 1000,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[64] = Sprite::Create(damageText[4], { 1000,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[65] = Sprite::Create(damageText[5], { 1000,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[66] = Sprite::Create(damageText[6], { 1000,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[67] = Sprite::Create(damageText[7], { 1000,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[68] = Sprite::Create(damageText[8], { 1000,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[69] = Sprite::Create(damageText[9], { 1000,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[70] = Sprite::Create(damageText[0], { 900,500 }, { 1,1,1,1 }, { 0.5f,0.5f });
	//10から90までのダメージ数値
	damageSprite[71] = Sprite::Create(damageText[1], { 950,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[72] = Sprite::Create(damageText[2], { 950,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[73] = Sprite::Create(damageText[3], { 950,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[74] = Sprite::Create(damageText[4], { 950,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[75] = Sprite::Create(damageText[5], { 950,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[76] = Sprite::Create(damageText[6], { 950,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[77] = Sprite::Create(damageText[7], { 950,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[78] = Sprite::Create(damageText[8], { 950,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
	damageSprite[79] = Sprite::Create(damageText[9], { 950,250 }, { 1,1,1,1 }, { 0.5f,0.5f });
}

void Field::Update()
{
	//ボールがポケットに入ったりボスが攻撃してきたときに処理される関数
	HandleBallPocket();
}

void Field::Draw()
{
	AreaDraw(areaNumber[0], pockets[0],0);
	AreaDraw(areaNumber[1], pockets[2],1);
	AreaDraw(areaNumber[2], pockets[3],2);
	AreaDraw(areaNumber[3], pockets[1],3);
	
	DebugNumberDraw();
}

void Field::DebugNumberDraw()
{
	//4右上

	if (areaNumber[3] == 10 || areaNumber[3] == 20 || areaNumber[3] == 30 || areaNumber[3] == 40 || areaNumber[3] == 50 || areaNumber[3] == 60 || areaNumber[3] == 70 || areaNumber[3] == 80 || areaNumber[3] == 90)
	{
		damageSprite[60]->Draw();
	}
	else if (areaNumber[3] == 1 || areaNumber[3] == 11 || areaNumber[3] == 21 || areaNumber[3] == 31 || areaNumber[3] == 41 || areaNumber[3] == 51 || areaNumber[3] == 61 || areaNumber[3] == 71 || areaNumber[3] == 81 || areaNumber[3] == 91)
	{
		damageSprite[61]->Draw();
	}
	else if (areaNumber[3] == 2 || areaNumber[3] == 12 || areaNumber[3] == 22 || areaNumber[3] == 32 || areaNumber[3] == 42 || areaNumber[3] == 52 || areaNumber[3] == 62 || areaNumber[3] == 72 || areaNumber[3] == 82 || areaNumber[3] == 92)
	{
		damageSprite[62]->Draw();
	}
	else if (areaNumber[3] == 3 || areaNumber[3] == 13 || areaNumber[3] == 23 || areaNumber[3] == 33 || areaNumber[3] == 43 || areaNumber[3] == 53 || areaNumber[3] == 63 || areaNumber[3] == 73 || areaNumber[3] == 83 || areaNumber[3] == 93)
	{
		damageSprite[63]->Draw();
	}
	else if (areaNumber[3] == 4 || areaNumber[3] == 14 || areaNumber[3] == 24 || areaNumber[3] == 34 || areaNumber[3] == 44 || areaNumber[3] == 54 || areaNumber[3] == 64 || areaNumber[3] == 74 || areaNumber[3] == 84 || areaNumber[3] == 94)
	{
		damageSprite[64]->Draw();
	}
	else if (areaNumber[3] == 5 || areaNumber[3] == 15 || areaNumber[3] == 25 || areaNumber[3] == 35 || areaNumber[3] == 45 || areaNumber[3] == 55 || areaNumber[3] == 65 || areaNumber[3] == 75 || areaNumber[3] == 85 || areaNumber[3] == 95)
	{
		damageSprite[65]->Draw();
	}
	else if (areaNumber[3] == 6 || areaNumber[3] == 16 || areaNumber[3] == 26 || areaNumber[3] == 36 || areaNumber[3] == 46 || areaNumber[3] == 56 || areaNumber[3] == 66 || areaNumber[3] == 76 || areaNumber[3] == 86 || areaNumber[3] == 96)
	{
		damageSprite[66]->Draw();
	}
	else if (areaNumber[3] == 7 || areaNumber[3] == 17 || areaNumber[3] == 27 || areaNumber[3] == 37 || areaNumber[3] == 47 || areaNumber[3] == 57 || areaNumber[3] == 67 || areaNumber[3] == 77 || areaNumber[3] == 87 || areaNumber[3] == 97)
	{
		damageSprite[67]->Draw();
	}
	else if (areaNumber[3] == 8 || areaNumber[3] == 18 || areaNumber[3] == 28 || areaNumber[3] == 38 || areaNumber[3] == 48 || areaNumber[3] == 58 || areaNumber[3] == 68 || areaNumber[3] == 78 || areaNumber[3] == 88 || areaNumber[3] == 98)
	{
		damageSprite[68]->Draw();
	}
	else if (areaNumber[3] == 9 || areaNumber[3] == 19 || areaNumber[3] == 29 || areaNumber[3] == 39 || areaNumber[3] == 49 || areaNumber[3] == 59 || areaNumber[3] == 69 || areaNumber[3] == 79 || areaNumber[3] == 89 || areaNumber[3] == 99)
	{
		damageSprite[69]->Draw();
	}

	if (areaNumber[3] >= 10 && areaNumber[3] <= 19)
	{
		damageSprite[71]->Draw();
	}
	else if (areaNumber[3] >= 20 && areaNumber[3] <= 29)
	{
		damageSprite[72]->Draw();
	}
	else if (areaNumber[3] >= 30 && areaNumber[3] <= 39)
	{
		damageSprite[73]->Draw();
	}
	else if (areaNumber[3] >= 40 && areaNumber[3] <= 49)
	{
		damageSprite[74]->Draw();
	}
	else if (areaNumber[3] >= 50 && areaNumber[3] <= 59)
	{
		damageSprite[75]->Draw();
	}
	else if (areaNumber[3] >= 60 && areaNumber[3] <= 69)
	{
		damageSprite[76]->Draw();
	}
	else if (areaNumber[3] >= 70 && areaNumber[3] <= 79)
	{
		damageSprite[77]->Draw();
	}
	else if (areaNumber[3] >= 80 && areaNumber[3] <= 89)
	{
		damageSprite[78]->Draw();
	}
	else if (areaNumber[3] >= 90 && areaNumber[3] <= 99)
	{
		damageSprite[79]->Draw();
	}



	//1左上

	if (areaNumber[0] == 10 || areaNumber[0] == 20 || areaNumber[0] == 30 || areaNumber[0] == 40 || areaNumber[0] == 50 || areaNumber[0] == 60 || areaNumber[0] == 70 || areaNumber[0] == 80 || areaNumber[0] == 90)
	{
		damageSprite[0]->Draw();
	}
	else if (areaNumber[0] == 1 || areaNumber[0] == 11 || areaNumber[0] == 21 || areaNumber[0] == 31 || areaNumber[0] == 41 || areaNumber[0] == 51 || areaNumber[0] == 61 || areaNumber[0] == 71 || areaNumber[0] == 81 || areaNumber[0] == 91)
	{
		damageSprite[1]->Draw();
	}
	else if (areaNumber[0] == 2 || areaNumber[0] == 12 || areaNumber[0] == 22 || areaNumber[0] == 32 || areaNumber[0] == 42 || areaNumber[0] == 52 || areaNumber[0] == 62 || areaNumber[0] == 72 || areaNumber[0] == 82 || areaNumber[0] == 92)
	{
		damageSprite[2]->Draw();
	}
	else if (areaNumber[0] == 3 || areaNumber[0] == 13 || areaNumber[0] == 23 || areaNumber[0] == 33 || areaNumber[0] == 43 || areaNumber[0] == 53 || areaNumber[0] == 63 || areaNumber[0] == 73 || areaNumber[0] == 83 || areaNumber[0] == 93)
	{
		damageSprite[3]->Draw();
	}
	else if (areaNumber[0] == 4 || areaNumber[0] == 14 || areaNumber[0] == 24 || areaNumber[0] == 34 || areaNumber[0] == 44 || areaNumber[0] == 54 || areaNumber[0] == 64 || areaNumber[0] == 74 || areaNumber[0] == 84 || areaNumber[0] == 94)
	{
		damageSprite[4]->Draw();
	}
	else if (areaNumber[0] == 5 || areaNumber[0] == 15 || areaNumber[0] == 25 || areaNumber[0] == 35 || areaNumber[0] == 45 || areaNumber[0] == 55 || areaNumber[0] == 65 || areaNumber[0] == 75 || areaNumber[0] == 85 || areaNumber[0] == 95)
	{
		damageSprite[5]->Draw();
	}
	else if (areaNumber[0] == 6 || areaNumber[0] == 16 || areaNumber[0] == 26 || areaNumber[0] == 36 || areaNumber[0] == 46 || areaNumber[0] == 56 || areaNumber[0] == 66 || areaNumber[0] == 76 || areaNumber[0] == 86 || areaNumber[0] == 96)
	{
		damageSprite[6]->Draw();
	}
	else if (areaNumber[0] == 7 || areaNumber[0] == 17 || areaNumber[0] == 27 || areaNumber[0] == 37 || areaNumber[0] == 47 || areaNumber[0] == 57 || areaNumber[0] == 67 || areaNumber[0] == 77 || areaNumber[0] == 87 || areaNumber[0] == 97)
	{
		damageSprite[7]->Draw();
	}
	else if (areaNumber[0] == 8 || areaNumber[0] == 18 || areaNumber[0] == 28 || areaNumber[0] == 38 || areaNumber[0] == 48 || areaNumber[0] == 58 || areaNumber[0] == 68 || areaNumber[0] == 78 || areaNumber[0] == 88 || areaNumber[0] == 98)
	{
		damageSprite[8]->Draw();
	}
	else if (areaNumber[0] == 9 || areaNumber[0] == 19 || areaNumber[0] == 29 || areaNumber[0] == 39 || areaNumber[0] == 49 || areaNumber[0] == 59 || areaNumber[0] == 69 || areaNumber[0] == 79 || areaNumber[0] == 89 || areaNumber[0] == 99)
	{
		damageSprite[9]->Draw();
	}

	if (areaNumber[0] >= 10 && areaNumber[0] <= 19)
	{
		damageSprite[11]->Draw();
	}
	else if (areaNumber[0] >= 20 && areaNumber[0] <= 29)
	{
		damageSprite[12]->Draw();
	}
	else if (areaNumber[0] >= 30 && areaNumber[0] <= 39)
	{
		damageSprite[13]->Draw();
	}
	else if (areaNumber[0] >= 40 && areaNumber[0] <= 49)
	{
		damageSprite[14]->Draw();
	}
	else if (areaNumber[0] >= 50 && areaNumber[0] <= 59)
	{
		damageSprite[15]->Draw();
	}
	else if (areaNumber[0] >= 60 && areaNumber[0] <= 69)
	{
		damageSprite[16]->Draw();
	}
	else if (areaNumber[0] >= 70 && areaNumber[0] <= 79)
	{
		damageSprite[17]->Draw();
	}
	else if (areaNumber[0] >= 80 && areaNumber[0] <= 89)
	{
		damageSprite[18]->Draw();
	}
	else if (areaNumber[0] >= 90 && areaNumber[0] <= 99)
	{
		damageSprite[19]->Draw();
	}


	//2

	if (areaNumber[1] == 10 || areaNumber[1] == 20 || areaNumber[1] == 30 || areaNumber[1] == 40 || areaNumber[1] == 50 || areaNumber[1] == 60 || areaNumber[1] == 70 || areaNumber[1] == 80 || areaNumber[1] == 90)
	{
		damageSprite[20]->Draw();
	}
	else if (areaNumber[1] == 1 || areaNumber[1] == 11 || areaNumber[1] == 21 || areaNumber[1] == 31 || areaNumber[1] == 41 || areaNumber[1] == 51 || areaNumber[1] == 61 || areaNumber[1] == 71 || areaNumber[1] == 81 || areaNumber[1] == 91)
	{
		damageSprite[21]->Draw();
	}
	else if (areaNumber[1] == 2 || areaNumber[1] == 12 || areaNumber[1] == 22 || areaNumber[1] == 32 || areaNumber[1] == 42 || areaNumber[1] == 52 || areaNumber[1] == 62 || areaNumber[1] == 72 || areaNumber[1] == 82 || areaNumber[1] == 92)
	{
		damageSprite[22]->Draw();
	}
	else if (areaNumber[1] == 3 || areaNumber[1] == 13 || areaNumber[1] == 23 || areaNumber[1] == 33 || areaNumber[1] == 43 || areaNumber[1] == 53 || areaNumber[1] == 63 || areaNumber[1] == 73 || areaNumber[1] == 83 || areaNumber[1] == 93)
	{
		damageSprite[23]->Draw();
	}
	else if (areaNumber[1] == 4 || areaNumber[1] == 14 || areaNumber[1] == 24 || areaNumber[1] == 34 || areaNumber[1] == 44 || areaNumber[1] == 54 || areaNumber[1] == 64 || areaNumber[1] == 74 || areaNumber[1] == 84 || areaNumber[1] == 94)
	{
		damageSprite[24]->Draw();
	}
	else if (areaNumber[1] == 5 || areaNumber[1] == 15 || areaNumber[1] == 25 || areaNumber[1] == 35 || areaNumber[1] == 45 || areaNumber[1] == 55 || areaNumber[1] == 65 || areaNumber[1] == 75 || areaNumber[1] == 85 || areaNumber[1] == 95)
	{
		damageSprite[25]->Draw();
	}
	else if (areaNumber[1] == 6 || areaNumber[1] == 16 || areaNumber[1] == 26 || areaNumber[1] == 36 || areaNumber[1] == 46 || areaNumber[1] == 56 || areaNumber[1] == 66 || areaNumber[1] == 76 || areaNumber[1] == 86 || areaNumber[1] == 96)
	{
		damageSprite[26]->Draw();
	}
	else if (areaNumber[1] == 7 || areaNumber[1] == 17 || areaNumber[1] == 27 || areaNumber[1] == 37 || areaNumber[1] == 47 || areaNumber[1] == 57 || areaNumber[1] == 67 || areaNumber[1] == 77 || areaNumber[1] == 87 || areaNumber[1] == 97)
	{
		damageSprite[27]->Draw();
	}
	else if (areaNumber[1] == 8 || areaNumber[1] == 18 || areaNumber[1] == 28 || areaNumber[1] == 38 || areaNumber[1] == 48 || areaNumber[1] == 58 || areaNumber[1] == 68 || areaNumber[1] == 78 || areaNumber[1] == 88 || areaNumber[1] == 98)
	{
		damageSprite[28]->Draw();
	}
	else if (areaNumber[1] == 9 || areaNumber[1] == 19 || areaNumber[1] == 29 || areaNumber[1] == 39 || areaNumber[1] == 49 || areaNumber[1] == 59 || areaNumber[1] == 69 || areaNumber[1] == 79 || areaNumber[1] == 89 || areaNumber[1] == 99)
	{
		damageSprite[29]->Draw();
	}

	if (areaNumber[1] >= 10 && areaNumber[1] <= 19)
	{
		damageSprite[31]->Draw();
	}
	else if (areaNumber[1] >= 20 && areaNumber[1] <= 29)
	{
		damageSprite[32]->Draw();
	}
	else if (areaNumber[1] >= 30 && areaNumber[1] <= 39)
	{
		damageSprite[33]->Draw();
	}
	else if (areaNumber[1] >= 40 && areaNumber[1] <= 49)
	{
		damageSprite[34]->Draw();
	}
	else if (areaNumber[1] >= 50 && areaNumber[1] <= 59)
	{
		damageSprite[35]->Draw();
	}
	else if (areaNumber[1] >= 60 && areaNumber[1] <= 69)
	{
		damageSprite[36]->Draw();
	}
	else if (areaNumber[1] >= 70 && areaNumber[1] <= 79)
	{
		damageSprite[37]->Draw();
	}
	else if (areaNumber[1] >= 80 && areaNumber[1] <= 89)
	{
		damageSprite[38]->Draw();
	}
	else if (areaNumber[1] >= 90 && areaNumber[1] <= 99)
	{
		damageSprite[39]->Draw();
	}

	//3


	if (areaNumber[2] == 10 || areaNumber[2] == 20 || areaNumber[2] == 30 || areaNumber[2] == 40 || areaNumber[2] == 50 || areaNumber[2] == 60 || areaNumber[2] == 70 || areaNumber[2] == 80 || areaNumber[2] == 90)
	{
		damageSprite[40]->Draw();
	}
	else if (areaNumber[2] == 1 || areaNumber[2] == 11 || areaNumber[2] == 21 || areaNumber[2] == 31 || areaNumber[2] == 41 || areaNumber[2] == 51 || areaNumber[2] == 61 || areaNumber[2] == 71 || areaNumber[2] == 81 || areaNumber[2] == 91)
	{
		damageSprite[41]->Draw();
	}
	else if (areaNumber[2] == 2 || areaNumber[2] == 12 || areaNumber[2] == 22 || areaNumber[2] == 32 || areaNumber[2] == 42 || areaNumber[2] == 52 || areaNumber[2] == 62 || areaNumber[2] == 72 || areaNumber[2] == 82 || areaNumber[2] == 92)
	{
		damageSprite[42]->Draw();
	}
	else if (areaNumber[2] == 3 || areaNumber[2] == 13 || areaNumber[2] == 23 || areaNumber[2] == 33 || areaNumber[2] == 43 || areaNumber[2] == 53 || areaNumber[2] == 63 || areaNumber[2] == 73 || areaNumber[2] == 83 || areaNumber[0] == 93)
	{
		damageSprite[43]->Draw();
	}
	else if (areaNumber[2] == 4 || areaNumber[2] == 14 || areaNumber[2] == 24 || areaNumber[2] == 34 || areaNumber[2] == 44 || areaNumber[2] == 54 || areaNumber[2] == 64 || areaNumber[2] == 74 || areaNumber[2] == 84 || areaNumber[0] == 94)
	{
		damageSprite[44]->Draw();
	}
	else if (areaNumber[2] == 5 || areaNumber[2] == 15 || areaNumber[2] == 25 || areaNumber[2] == 35 || areaNumber[2] == 45 || areaNumber[2] == 55 || areaNumber[2] == 65 || areaNumber[2] == 75 || areaNumber[2] == 85 || areaNumber[2] == 95)
	{
		damageSprite[45]->Draw();
	}
	else if (areaNumber[2] == 6 || areaNumber[2] == 16 || areaNumber[2] == 26 || areaNumber[2] == 36 || areaNumber[2] == 46 || areaNumber[2] == 56 || areaNumber[2] == 66 || areaNumber[2] == 76 || areaNumber[2] == 86 || areaNumber[2] == 96)
	{
		damageSprite[46]->Draw();
	}
	else if (areaNumber[2] == 7 || areaNumber[2] == 17 || areaNumber[2] == 27 || areaNumber[2] == 37 || areaNumber[2] == 47 || areaNumber[2] == 57 || areaNumber[2] == 67 || areaNumber[2] == 77 || areaNumber[2] == 87 || areaNumber[2] == 97)
	{
		damageSprite[47]->Draw();
	}
	else if (areaNumber[2] == 8 || areaNumber[2] == 18 || areaNumber[2] == 28 || areaNumber[2] == 38 || areaNumber[2] == 48 || areaNumber[2] == 58 || areaNumber[2] == 68 || areaNumber[2] == 78 || areaNumber[2] == 88 || areaNumber[2] == 98)
	{
		damageSprite[48]->Draw();
	}
	else if (areaNumber[2] == 9 || areaNumber[2] == 19 || areaNumber[2] == 29 || areaNumber[2] == 39 || areaNumber[2] == 49 || areaNumber[2] == 59 || areaNumber[2] == 69 || areaNumber[2] == 79 || areaNumber[2] == 89 || areaNumber[2] == 99)
	{
		damageSprite[49]->Draw();
	}

	if (areaNumber[2] >= 10 && areaNumber[2] <= 19)
	{
		damageSprite[51]->Draw();
	}
	else if (areaNumber[2] >= 20 && areaNumber[2] <= 29)
	{
		damageSprite[52]->Draw();
	}
	else if (areaNumber[2] >= 30 && areaNumber[2] <= 39)
	{
		damageSprite[53]->Draw();
	}
	else if (areaNumber[2] >= 40 && areaNumber[2] <= 49)
	{
		damageSprite[54]->Draw();
	}
	else if (areaNumber[2] >= 50 && areaNumber[2] <= 59)
	{
		damageSprite[55]->Draw();
	}
	else if (areaNumber[2] >= 60 && areaNumber[2] <= 69)
	{
		damageSprite[56]->Draw();
	}
	else if (areaNumber[2] >= 70 && areaNumber[2] <= 79)
	{
		damageSprite[57]->Draw();
	}
	else if (areaNumber[2] >= 80 && areaNumber[2] <= 89)
	{
		damageSprite[58]->Draw();
	}
	else if (areaNumber[2] >= 90 && areaNumber[2] <= 99)
	{
		damageSprite[59]->Draw();
	}
}

void Field::HandleBallPocket()
{
	ballPositions = balls_->GetBallsPos();
	for (int i = 0; i < kBallCount; i++)
	{
		//エリアを分けて処理させる
		if (CheckCollision(ballPositions[i], pockets[0]))
		{
			AreaProcess(areaCaunter[0]);  //左上のポケットが落ちた時のエリア効果
			if (hpDown)
			{
				player_->TakeDamage(damage_);
				player_->SetIsDamage();
				hpDown = false;
			}
			isDamage = true;
		}
		else if (CheckCollision(ballPositions[i], pockets[2]))
		{
			AreaProcess(areaCaunter[1]); //左下のポケットが落ちた時のエリア効果
			if (hpDown)
			{
				player_->TakeDamage(damage_);
				player_->SetIsDamage();
				hpDown = false;
			}
			isDamage = true;
		}
		else if (CheckCollision(ballPositions[i], pockets[3]))
		{
			AreaProcess(areaCaunter[2]); //右下のポケットが落ちた時のエリア効果
			if (hpDown)
			{
				player_->TakeDamage(damage_);
				player_->SetIsDamage();
				hpDown = false;
			}
			isDamage = true;
		}
		else if (CheckCollision(ballPositions[i], pockets[1]))
		{
			AreaProcess(areaCaunter[3]); //右上のポケットが落ちた時のエリア効果
			if (hpDown)
			{
				player_->TakeDamage(damage_);
				player_->SetIsDamage();
				hpDown = false;
			}
			isDamage = true;
		}
		else if (CheckCollision(ballPositions[i], pockets[4]))
		{
			AreaProcess(areaCaunter[0]);
			isDamage = false;
			AreaProcess(areaCaunter[3]); //真ん中上のポケットが落ちた時のエリア効果
			if (hpDown)
			{
				player_->TakeDamage(damage_);
				player_->SetIsDamage();
				hpDown = false;
			}
			
		}
		else if (CheckCollision(ballPositions[i], pockets[5]))
		{
			AreaProcess(areaCaunter[1]);
			isDamage = false;
			AreaProcess(areaCaunter[2]); //真ん中下のポケットが落ちた時のエリア効果
			if (hpDown)
			{
				player_->TakeDamage(damage_);
				player_->SetIsDamage();
				hpDown = false;
			}
			
		}
	}
	
}

void Field::SetDamage(int damage)
{
	damage_ = damage;
}

void Field::GenerateRandomNumber()
{
	//ボスが攻撃をするたびに発動するもの
	//エリア効果のための変数を更新する
	unsigned int currentTime = (unsigned int)time(nullptr);
	srand(currentTime);
	for (int i = 0; i < 4; i++)
	{
		areaNumber[i] = rand() % 100 + 1;
	}
	isDamage = false;
}

void Field::AreaDraw(int number,Vector2 pos1,int AreaNumber)
{
	//ナンバーが25以下の場合の処理(確率25%)
	if (number <= 20 )
	{
		if (AreaNumber == 0)
		{
			pos[0] = { 430,376 };
			testSprite[0]->SetPosition(pos[0]);
			testSprite[0]->Draw();
			areaCaunter[0] = number;
		}
		if(AreaNumber==1)
		{
			pos[1] = { 430,586 };
			testSprite[1]->SetPosition(pos[1]);
			testSprite[1]->Draw();
			areaCaunter[1] = number;
		}

		if (AreaNumber == 2)
		{
			pos[2] = { 848,586 };
			testSprite[2]->SetPosition(pos[2]);
			testSprite[2]->Draw();
			areaCaunter[2] = number;
		}

		if (AreaNumber == 3)
		{
			pos[3] = { 848,376 };
			testSprite[3]->SetPosition(pos[3]);
			testSprite[3]->Draw();
			areaCaunter[3] = number;
		}
		
	}
	//ナンバーが25から50の場合の処理(確率25%)
	else if (number >= 20 && number <= 65 )
	{
		if (AreaNumber == 0)
		{
			pos[4] = { 430,376 };
			testSprite[4]->SetPosition(pos[4]);
			testSprite[4]->Draw();
			areaCaunter[0] = number;
		}
		if (AreaNumber == 1)
		{
			pos[5] = { 430,586 };
			testSprite[5]->SetPosition(pos[5]);
			testSprite[5]->Draw();
			areaCaunter[1] = number;
		}

		if (AreaNumber == 2)
		{
			pos[6] = { 848,586 };
			testSprite[6]->SetPosition(pos[6]);
			testSprite[6]->Draw();
			areaCaunter[2] = number;
		}

		if (AreaNumber == 3)
		{
			pos[7] = { 848,376 };
			testSprite[7]->SetPosition(pos[7]);
			testSprite[7]->Draw();
			areaCaunter[3] = number;
		}
	}
	//ナンバーが50から75の時の処理(確率25%)
	else if (number >= 65 && number <= 75 )
	{
		if (AreaNumber == 0)
		{
			pos[8] = { 430,376 };
			testSprite[8]->SetPosition(pos[8]);
			testSprite[8]->Draw();
			areaCaunter[0] = number;
		}
		if (AreaNumber == 1)
		{
			pos[9] = { 430,586 };
			testSprite[9]->SetPosition(pos[9]);
			testSprite[9]->Draw();
			areaCaunter[1] = number;
		}

		if (AreaNumber == 2)
		{
			pos[10] = { 848,586 };
			testSprite[10]->SetPosition(pos[10]);
			testSprite[10]->Draw();
			areaCaunter[2] = number;
		}

		if (AreaNumber == 3)
		{
			pos[11] = { 848,376 };
			testSprite[11]->SetPosition(pos[11]);
			testSprite[11]->Draw();
			areaCaunter[3] = number;
		}
	}
	else if (number >= 75 )
	{
		if (AreaNumber == 0)
		{
			areaCaunter[0] = number;
		}
		if (AreaNumber == 1)
		{
			areaCaunter[1] = number;
		}

		if (AreaNumber == 2)
		{
			areaCaunter[2] = number;
		}

		if (AreaNumber == 3)
		{
			areaCaunter[3] = number;
		}
    }
}


int Field::AreaProcess(int number)
{
	//今はプレイヤーのHPを回復したりターンという概念がないためコメントアウト
	//ナンバーが10以下の場合の処理(確率10%)
	if (number <= 20 && isDamage == false)
	{
		damage_ = damage_ / 2;
		isDamage = true;
	}
	//ナンバーが10から30の場合の処理(確率40%)
	else if (number >= 20 && number <= 65 && isDamage == false)
	{
		damage_ = damage_ * 2;
		isDamage = true;
	}
	//ナンバーが30から50の時の処理(確率15%)
	else if (number >= 65 && number <= 75 && isDamage == false)
	{
		hpDown = true;
		isDamage = true;
	}
	//ナンバーが75以上の時の処理(確率30%)
	else if (number >= 75 && isDamage == false)
	{
		damage_ = damage_;
		isDamage = true;
	}
	return number;
}

bool Field::CheckCollision(Vector2 pos1, Vector2 pos2)
{
	float pocketRadius = 38.0f;
	float dx = pos1.x - pos2.x;
	float dy = pos1.y - pos2.y;
	float distSq = dx * dx + dy * dy;
	if (distSq < pocketRadius * pocketRadius) 
	{
		return true;
	}
	else
	{
		return false;
	}
}
