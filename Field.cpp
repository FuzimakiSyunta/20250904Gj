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

	areaCooltime=0;

	for (int i = 0; i < 12; i++)
	{
		isArea[i] = false;
	}
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
			isDamage = true;
		}
		else if (CheckCollision(ballPositions[i], pockets[2]))
		{
			AreaProcess(areaNumber[1]); //左下のポケットが落ちた時のエリア効果
			isDamage = true;
		}
		else if (CheckCollision(ballPositions[i], pockets[3]))
		{
			AreaProcess(areaNumber[2]); //右下のポケットが落ちた時のエリア効果
			isDamage = true;
		}
		else if (CheckCollision(ballPositions[i], pockets[1]))
		{
			AreaProcess(areaNumber[3]); //右上のポケットが落ちた時のエリア効果
			isDamage = true;
		}
		else if (CheckCollision(ballPositions[i], pockets[4]))
		{
			AreaProcess(areaNumber[0]);
			AreaProcess(areaNumber[3]); //真ん中上のポケットが落ちた時のエリア効果
			isDamage = true;
		}
		else if (CheckCollision(ballPositions[i], pockets[5]))
		{
			AreaProcess(areaNumber[1]);
			AreaProcess(areaNumber[2]); //真ん中下のポケットが落ちた時のエリア効果
			isDamage = true;
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
	if (number <= 25 )
	{
		if (AreaNumber == 0)
		{
			pos[0] = { 420,370 };
			testSprite[0]->SetPosition(pos[0]);
			/*if (pos1.x == pockets[0].x)
			{
				pos[0] = { 420,370 };
				testSprite[0]->SetPosition(pos[0]);
			}
			else if (pos1.x == pockets[2].x)
			{
				pos[0] = { 420,595 };
				testSprite[0]->SetPosition(pos[0]);
			}
			else if (pos1.x == pockets[3].x)
			{
				pos[0] = { 858,595 };
				testSprite[0]->SetPosition(pos[0]);
			}
			else if (pos1.x == pockets[1].x)
			{
				pos[0] = { 858,370 };
				testSprite[0]->SetPosition(pos[0]);
			}*/
			testSprite[0]->Draw();
		}
		if(AreaNumber==1)
		{
			pos[1] = { 420,595 };
			testSprite[1]->SetPosition(pos[1]);
			/*if (pos1.x == pockets[0].x)
			{
				pos[1] = { 420,370 };
				testSprite[1]->SetPosition(pos[1]);
			}
			else if (pos1.x == pockets[2].x)
			{
				pos[1] = { 420,595 };
				testSprite[1]->SetPosition(pos[1]);
			}
			else if (pos1.x == pockets[3].x)
			{
				pos[1] = { 858,595 };
				testSprite[1]->SetPosition(pos[1]);
			}
			else if (pos1.x == pockets[1].x)
			{
				pos[1] = { 858,370 };
				testSprite[1]->SetPosition(pos[1]);
			}*/
			testSprite[1]->Draw();
		}

		if (AreaNumber == 2)
		{
			pos[2] = { 858,595 };
			testSprite[2]->SetPosition(pos[2]);
			/*if (pos1.x == pockets[0].x)
			{
				pos[2] = { 420,370 };
				testSprite[2]->SetPosition(pos[2]);
			}
			else if (pos1.x == pockets[2].x)
			{
				pos[2] = { 420,595 };
				testSprite[2]->SetPosition(pos[2]);
			}
			else if (pos1.x == pockets[3].x)
			{
				pos[2] = { 858,595 };
				testSprite[2]->SetPosition(pos[2]);
			}
			else if (pos1.x == pockets[1].x)
			{
				pos[2] = { 858,370 };
				testSprite[2]->SetPosition(pos[2]);
			}*/
			testSprite[2]->Draw();
		}

		if (AreaNumber == 3)
		{
			pos[3] = { 858,370 };
			testSprite[3]->SetPosition(pos[3]);
			/*if (pos1.x == pockets[0].x)
			{
				pos[3] = { 420,370 };
				testSprite[3]->SetPosition(pos[3]);
			}
			else if (pos1.x == pockets[2].x)
			{
				pos[3] = { 420,595 };
				testSprite[3]->SetPosition(pos[3]);
			}
			else if (pos1.x == pockets[3].x)
			{
				pos[3] = { 858,595 };
				testSprite[3]->SetPosition(pos[3]);
			}
			else if (pos1.x == pockets[1].x)
			{
				pos[3] = { 858,370 };
				testSprite[3]->SetPosition(pos[3]);
			}*/
			testSprite[3]->Draw();
		}
		
	}
	//ナンバーが25から50の場合の処理(確率25%)
	else if (number >= 25 && number <= 50 )
	{
		if (AreaNumber == 0)
		{
			pos[4] = { 420,370 };
			testSprite[4]->SetPosition(pos[4]);
			/*if (pos1.x == pockets[0].x)
			{
				pos[4] = { 420,370 };
				testSprite[4]->SetPosition(pos[4]);
			}
			else if (pos1.x == pockets[2].x)
			{
				pos[4] = { 420,595 };
				testSprite[4]->SetPosition(pos[4]);
			}
			else if (pos1.x == pockets[3].x)
			{
				pos[4] = { 858,595 };
				testSprite[4]->SetPosition(pos[4]);
			}
			else if (pos1.x == pockets[1].x)
			{
				pos[4] = { 858,370 };
				testSprite[4]->SetPosition(pos[4]);
			}*/
			testSprite[4]->Draw();
		}
		if (AreaNumber == 1)
		{
			pos[5] = { 420,595 };
			testSprite[5]->SetPosition(pos[5]);
			/*if (pos1.x == pockets[0].x)
			{
				pos[5] = { 420,370 };
				testSprite[5]->SetPosition(pos[5]);
			}
			else if (pos1.x == pockets[2].x)
			{
				pos[5] = { 420,595 };
				testSprite[5]->SetPosition(pos[5]);
			}
			else if (pos1.x == pockets[3].x)
			{
				pos[5] = { 858,595 };
				testSprite[5]->SetPosition(pos[5]);
			}
			else if (pos1.x == pockets[1].x)
			{
				pos[5] = { 858,370 };
				testSprite[5]->SetPosition(pos[5]);
			}*/
			testSprite[5]->Draw();
		}

		if (AreaNumber == 2)
		{
			pos[6] = { 858,595 };
			testSprite[6]->SetPosition(pos[6]);
			/*if (pos1.x == pockets[0].x)
			{
				pos[6] = { 420,370 };
				testSprite[6]->SetPosition(pos[6]);
			}
			else if (pos1.x == pockets[2].x)
			{
				pos[6] = { 420,595 };
				testSprite[6]->SetPosition(pos[6]);
			}
			else if (pos1.x == pockets[3].x)
			{
				pos[6] = { 858,595 };
				testSprite[6]->SetPosition(pos[6]);
			}
			else if (pos1.x == pockets[1].x)
			{
				pos[6] = { 858,370 };
				testSprite[6]->SetPosition(pos[6]);
			}*/
			testSprite[6]->Draw();
		}

		if (AreaNumber == 3)
		{
			pos[7] = { 858,370 };
			testSprite[7]->SetPosition(pos[7]);
			/*if (pos1.x == pockets[0].x)
			{
				pos[7] = { 420,370 };
				testSprite[7]->SetPosition(pos[7]);
			}
			else if (pos1.x == pockets[2].x)
			{
				pos[7] = { 420,595 };
				testSprite[7]->SetPosition(pos[7]);
			}
			else if (pos1.x == pockets[3].x)
			{
				pos[7] = { 858,595 };
				testSprite[7]->SetPosition(pos[7]);
			}
			else if (pos1.x == pockets[1].x)
			{
				pos[7] = { 858,370 };
				testSprite[7]->SetPosition(pos[7]);
			}*/
			testSprite[7]->Draw();
		}
	}
	//ナンバーが50から75の時の処理(確率25%)
	else if (number >= 50 && number <= 75 )
	{
		if (AreaNumber == 0)
		{
			pos[8] = { 420,370 };
			testSprite[8]->SetPosition(pos[8]);
			/*if (pos1.x == pockets[0].x)
			{
				pos[8] = { 420,370 };
				testSprite[8]->SetPosition(pos[8]);
			}
			else if (pos1.x == pockets[2].x)
			{
				pos[8] = { 420,595 };
				testSprite[8]->SetPosition(pos[8]);
			}
			else if (pos1.x == pockets[3].x)
			{
				pos[8] = { 858,595 };
				testSprite[8]->SetPosition(pos[8]);
			}
			else if (pos1.x == pockets[1].x)
			{
				pos[8] = { 858,370 };
				testSprite[8]->SetPosition(pos[8]);
			}*/
			testSprite[8]->Draw();
		}
		if (AreaNumber == 1)
		{
			pos[9] = { 420,595 };
			testSprite[9]->SetPosition(pos[9]);
			/*if (pos1.x == pockets[0].x)
			{
				pos[9] = { 420,370 };
				testSprite[9]->SetPosition(pos[9]);
			}
			else if (pos1.x == pockets[2].x)
			{
				pos[9] = { 420,595 };
				testSprite[9]->SetPosition(pos[9]);
			}
			else if (pos1.x == pockets[3].x)
			{
				pos[9] = { 858,595 };
				testSprite[9]->SetPosition(pos[9]);
			}
			else if (pos1.x == pockets[1].x)
			{
				pos[9] = { 858,370 };
				testSprite[9]->SetPosition(pos[9]);
			}*/
			testSprite[9]->Draw();
		}

		if (AreaNumber == 2)
		{
			pos[10] = { 858,595 };
			testSprite[10]->SetPosition(pos[10]);
			/*if (pos1.x == pockets[0].x)
			{
				pos[10] = { 420,370 };
				testSprite[10]->SetPosition(pos[10]);
			}
			else if (pos1.x == pockets[2].x)
			{
				pos[10] = { 420,595 };
				testSprite[10]->SetPosition(pos[10]);
			}
			else if (pos1.x == pockets[3].x)
			{
				pos[10] = { 858,595 };
				testSprite[10]->SetPosition(pos[10]);
			}
			else if (pos1.x == pockets[1].x)
			{
				pos[10] = { 858,370 };
				testSprite[10]->SetPosition(pos[10]);
			}*/
			testSprite[10]->Draw();
		}

		if (AreaNumber == 3)
		{
			pos[11] = { 858,370 };
			testSprite[11]->SetPosition(pos[11]);
			/*if (pos1.x == pockets[0].x)
			{
				pos[11] = { 420,370 };
				testSprite[11]->SetPosition(pos[11]);
			}
			else if (pos1.x == pockets[2].x)
			{
				pos[11] = { 420,595 };
				testSprite[11]->SetPosition(pos[11]);
			}
			else if (pos1.x == pockets[3].x)
			{
				pos[11] = { 858,595 };
				testSprite[11]->SetPosition(pos[11]);
			}
			else if (pos1.x == pockets[1].x)
			{
				pos[11] = { 858,370 };
				testSprite[11]->SetPosition(pos[11]);
			}*/
			testSprite[11]->Draw();
		}
	}
}

void Field::GenerateRandomArea()
{
	if (areaCooltime <= 20)
	{
		areaCooltime++;
	}
	if (areaCooltime <= 10)
	{
		//ボスが攻撃をするたびに発動するもの
		//エリア効果のための変数を更新する
		unsigned int currentTime = (unsigned int)time(nullptr);
		srand(currentTime);
		for (int i = 0; i < 3; i++)
		{
			areaCaunter[i] = rand() % 100 + 1;
		}
	}
}

int Field::AreaProcess(int number)
{
	//今はプレイヤーのHPを回復したりターンという概念がないためコメントアウト
	//ナンバーが10以下の場合の処理(確率10%)
	if (number <= 25 && isDamage == false)
	{
		damage_ = damage_ / 2;
	}
	//ナンバーが10から30の場合の処理(確率20%)
	else if (number >= 25 && number <= 50 && isDamage == false)
	{
		damage_ = damage_ * 2;
	}
	//ナンバーが30から50の時の処理(確率20%)
	else if (number >= 50 && number <= 75 && isDamage == false)
	{
		player_->TakeDamage(1);
	}
	//ナンバーが90以上の時の処理(確率10%)
	else if (number >= 75 && isDamage == false)
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
