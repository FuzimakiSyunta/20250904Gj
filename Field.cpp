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
	uint32_t texttexture = TextureManager::Load("uvChecker.png");
	
	testSprite = Sprite::Create(texttexture, pos, { 1,1,1,1 }, { 0.5f,0.5f });
}

void Field::Update()
{
	//ボールがポケットに入ったりボスが攻撃してきたときに処理される関数
	HandleBallPocket();
}

void Field::Draw()
{
	//testSprite->Draw();
}

void Field::HandleBallPocket()
{
	ballPositions = balls_->GetBallsPos();
	for (int i = 0; i < kBallCount; i++)
	{
		//エリアを分けて処理させる
		if (CheckCollision(ballPositions[i], pockets[0]))
		{
			AreaProcess(areaNumber[0]);  //左上のポケットが落ちた時のエリア効果
		}
		else if (CheckCollision(ballPositions[i], pockets[2]))
		{
			AreaProcess(areaNumber[1]); //左下のポケットが落ちた時のエリア効果
		}
		else if (CheckCollision(ballPositions[i], pockets[3]))
		{
			AreaProcess(areaNumber[2]); //右下のポケットが落ちた時のエリア効果
		}
		else if (CheckCollision(ballPositions[i], pockets[1]))
		{
			AreaProcess(areaNumber[3]); //右上のポケットが落ちた時のエリア効果
		}
		else if (CheckCollision(ballPositions[i], pockets[4]))
		{
			AreaProcess(areaNumber[0]);
			AreaProcess(areaNumber[3]); //真ん中上のポケットが落ちた時のエリア効果
		}
		else if (CheckCollision(ballPositions[i], pockets[5]))
		{
			AreaProcess(areaNumber[1]);
			AreaProcess(areaNumber[2]); //真ん中下のポケットが落ちた時のエリア効果
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

int Field::AreaProcess(int number)
{
	//今はプレイヤーのHPを回復したりターンという概念がないためコメントアウト
	////ナンバーが10以下の場合の処理(確率10%)
	//if (number <= 10&&isDamage==false)
	//{
	//	//damage_ = damage_ / 2;
	//	pos = { 100,700 };
	//	testSprite->SetPosition(pos);
	//}
	////ナンバーが10から30の場合の処理(確率20%)
	//else if (number >= 10 && number <= 30 && isDamage == false)
	//{
	//	//damage_ = damage_ * 2;
	//	pos = { 300,700 };
	//	testSprite->SetPosition(pos);
	//}
	////ナンバーが30から50の時の処理(確率20%)
	//else if (number >= 30 && number <= 50 && isDamage == false)
	//{
	//	pos = { 500,700 };
	//	testSprite->SetPosition(pos);
	//}
	////ナンバーが50から70の時の処理(確率20%)
	//else if (number >= 50 && number <= 70 && isDamage == false)
	//{
	//	pos = { 700,700 };
	//	testSprite->SetPosition(pos);
	//}
	////ナンバーが70から90の時の処理(確率20%)
	//else if (number >= 70 && number <= 90 && isDamage == false)
	//{
	//	pos = { 900,700 };
	//	testSprite->SetPosition(pos);
	//}
	////ナンバーが90以上の時の処理(確率10%)
	//else if (number >= 90 && isDamage == false)
	//{
	//	pos = { 1100,700 };
	//	testSprite->SetPosition(pos);
	//}
	//とりあえず今適応できる効果をここに追加(すべて揃ったらこれらは削除して上記のコメントアウトを解除する)
	if (number <= 40 )
	{
		damage_ = 0;
	}
	else if (number >= 40 && number <= 80 )
	{
		damage_ = damage_ * 20;
	}
	else if (number >= 80 )
	{
		damage_ = damage_;
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
