#include "Field.h"
#include <stdlib.h>
#include <stdio.h>
#include <TextureManager.h>
#include "Ball.h"
#include <time.h>

void Field::Initialize()
{
	input_ = Input::GetInstance();
	//初期化もランダムでしておく
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

	//画像のサイズ
	for (int i = 0; i < 12; i++)
	{
		testSprite[i]->SetSize({ 419,212 });
	}

	for (int i = 0; i < 10; i++)
	{
		isActive[i] = true;
	}


	
}

void Field::Update()
{
	//ボールがポケットに入ったりボスが攻撃してきたときに処理される関数
	HandleBallPocket();
}

void Field::Draw()
{
	//画像を描画。値についてはランダムに変わる変数と順番に描画していく数(0から始まる)
	AreaDraw(areaNumber[0], 0);
	AreaDraw(areaNumber[1], 1);
	AreaDraw(areaNumber[2], 2);
	AreaDraw(areaNumber[3], 3);
}



void Field::HandleBallPocket()
{
	ballPositions = balls_->GetBallsPos();
	for (int i = 0; i < kBallCount; i++)
	{
		if (CheckCollision(ballPositions[i], pockets[0]) && isActive[i]) 
		{
			AreaProcess(areaCaunter[0]);  //左上のポケットが落ちた時のエリア効果
			//hpがダウンする効果が当たる時最後にプレイヤーにダメージを与える
			if (hpDown)
			{
				player_->TakeDamage(damage_);
				player_->SetIsDamage();
				hpDown = false;
			}
			//処理が終わったらフラグを立たせ複数処理されないようにする
			isDamage = true;
			isActive[i] = false;
			break;
		}
		else if (CheckCollision(ballPositions[i], pockets[2]) && isActive[i])
		{
			AreaProcess(areaCaunter[1]); //左下のポケットが落ちた時のエリア効果
			//hpがダウンする効果が当たる時最後にプレイヤーにダメージを与える
			if (hpDown)
			{
				player_->TakeDamage(damage_);
				player_->SetIsDamage();
				hpDown = false;
			}
			//処理が終わったらフラグを立たせ複数処理されないようにする
			isDamage = true;
			isActive[i] = false;
			break;
		}
		else if (CheckCollision(ballPositions[i], pockets[3]) && isActive[i])
		{
			AreaProcess(areaCaunter[2]); //右下のポケットが落ちた時のエリア効果
			//hpがダウンする効果が当たる時最後にプレイヤーにダメージを与える
			if (hpDown)
			{
				player_->TakeDamage(damage_);
				player_->SetIsDamage();
				hpDown = false;
			}
			//処理が終わったらフラグを立たせ複数処理されないようにする
			isDamage = true;
			isActive[i] = false;
			break;
		}
		else if (CheckCollision(ballPositions[i], pockets[1]) && isActive[i])
		{
			AreaProcess(areaCaunter[3]); //右上のポケットが落ちた時のエリア効果
			//hpがダウンする効果が当たる時最後にプレイヤーにダメージを与える
			if (hpDown)
			{
				player_->TakeDamage(damage_);
				player_->SetIsDamage();
				hpDown = false;
			}
			//処理が終わったらフラグを立たせ複数処理されないようにする
			isDamage = true;
			isActive[i] = false;
			break;
		}
		else if (CheckCollision(ballPositions[i], pockets[4]) && isActive[i])
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
			//処理が終わったらフラグを立たせ複数処理されないようにする
			isDamage = false;
			isActive[i] = false;
			break;
		}
		else if (CheckCollision(ballPositions[i], pockets[5]) && isActive[i])
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
			//処理が終わったらフラグを立たせ複数処理されないようにする
			isDamage = false;
			isActive[i] = false;
			break;
		}
	}
	
}
//ボールのダメージを代入するための関数
void Field::SetDamage(int damage)
{
	damage_ = damage;
}
//ポケットにボールを入れるたびにランダムに変数を変える処理
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

//この関数は上記にあるareaNumberの値を見てどこに画像を描画するかを決める処理AreaNumberについては順番に描画されるように0～3を設定する
void Field::AreaDraw(int number,int AreaNumber)
{
	//ドラゴン
	if (!isDragon_)
	{
		//ナンバーが25以下の場合の処理(確率25%)
		if (number <= 20)
		{
			if (AreaNumber == 0)
			{
				//左上の画像
				pos[0] = { 430,376 };
				testSprite[0]->SetPosition(pos[0]);
				testSprite[0]->Draw();
				areaCaunter[0] = number;
			}
			if (AreaNumber == 1)
			{
				//左下の画像
				pos[1] = { 430,586 };
				testSprite[1]->SetPosition(pos[1]);
				testSprite[1]->Draw();
				areaCaunter[1] = number;
			}

			if (AreaNumber == 2)
			{
				//右下の画像
				pos[2] = { 848,586 };
				testSprite[2]->SetPosition(pos[2]);
				testSprite[2]->Draw();
				areaCaunter[2] = number;
			}

			if (AreaNumber == 3)
			{
				//右上の画像
				pos[3] = { 848,376 };
				testSprite[3]->SetPosition(pos[3]);
				testSprite[3]->Draw();
				areaCaunter[3] = number;
			}

		}
		//ナンバーが25から50の場合の処理(確率25%)
		else if (number >= 20 && number <= 65)
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
		else if (number >= 65 && number <= 75)
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
		else if (number >= 75)
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

	if (isDragon_)
	{
		if (number <= 40)
		{
			if (AreaNumber == 0)
			{
				//左上の画像
				pos[0] = { 430,376 };
				testSprite[0]->SetPosition(pos[0]);
				testSprite[0]->Draw();
				areaCaunter[0] = number;
			}
			if (AreaNumber == 1)
			{
				//左下の画像
				pos[1] = { 430,586 };
				testSprite[1]->SetPosition(pos[1]);
				testSprite[1]->Draw();
				areaCaunter[1] = number;
			}

			if (AreaNumber == 2)
			{
				//右下の画像
				pos[2] = { 848,586 };
				testSprite[2]->SetPosition(pos[2]);
				testSprite[2]->Draw();
				areaCaunter[2] = number;
			}

			if (AreaNumber == 3)
			{
				//右上の画像
				pos[3] = { 848,376 };
				testSprite[3]->SetPosition(pos[3]);
				testSprite[3]->Draw();
				areaCaunter[3] = number;
			}

		}
	}

}


int Field::AreaProcess(int number) {
	if (boss_ && boss_->GetType() == BossType::Dragon) {
		// ドラゴン用確率: ダメージ30%, バフ20%, デバフ10%, 他40%
		if (number <= 30 && !isDamage) {
			hpDown = true;
			isDamage = true;
		}
		//else if (number > 30 && number <= 50 && !isDamage) {
		//	damage_ *= 2; // バフ
		//	isDamage = true;
		//}
		//else if (number > 50 && number <= 60 && !isDamage) {
		//	damage_ /= 2; // デバフ
		//	isDamage = true;
		//}
		else if (number > 60 && !isDamage) {
			damage_ = damage_; // 何もなし
			isDamage = true;
		}
	}
	else {
		// スライムキング従来処理
		if (number <= 20 && !isDamage) {
			damage_ /= 2;
			isDamage = true;
		}
		else if (number > 20 && number <= 65 && !isDamage) {
			damage_ *= 2;
			isDamage = true;
		}
		else if (number > 65 && number <= 75 && !isDamage) {
			hpDown = true;
			isDamage = true;
		}
		else if (number > 75 && !isDamage) {
			damage_ = damage_;
			isDamage = true;
		}
	}
	return number;
}

//当たり判定(各ボールの座標と各ポケットの座標)
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

void Field::SetBossType(bool isDragon) {
	isDragon_ = isDragon;
}


void Field::ReviveBall()
{
	for (int i = 0; i < 10; i++)
	{
		isActive[i] = true;   // �ĂюQ�Ɖ\�ɂ���
	}
}

