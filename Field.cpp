#include "Field.h"
#include <stdlib.h>
#include <stdio.h>
#include <TextureManager.h>

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
	testSprite->Draw();
}

void Field::HandleBallPocket()
{
	//エリアを分けて処理させる
	if (input_->PushKey(DIK_Q))
	{
		AreaProcess(areaNumber[0]);  //左上のポケットが落ちた時のエリア効果
		//isDamage = true;
	}
	else if (input_->PushKey(DIK_Z))
	{
		AreaProcess(areaNumber[1]); //左下のポケットが落ちた時のエリア効果
		//isDamage = true;
	}
	else if (input_->PushKey(DIK_M))
	{
		AreaProcess(areaNumber[2]); //右下のポケットが落ちた時のエリア効果
		//isDamage = true;
	}
	else if (input_->PushKey(DIK_O))
	{
		AreaProcess(areaNumber[3]); //右上のポケットが落ちた時のエリア効果
		//isDamage = true;
	}
	else if (input_->PushKey(DIK_Q) && input_->PushKey(DIK_O))
	{
		AreaProcess(areaNumber[0]);
		AreaProcess(areaNumber[3]); //真ん中上のポケットが落ちた時のエリア効果
		//isDamage = true;
	}
	else if (input_->PushKey(DIK_Z) && input_->PushKey(DIK_M))
	{
		AreaProcess(areaNumber[1]);
		AreaProcess(areaNumber[2]); //真ん中下のポケットが落ちた時のエリア効果
		//isDamage = true;
	}
	//ボスが攻撃をするたびに発動するもの
	//エリア効果のための変数を更新する
	if (input_->PushKey(DIK_H))
	{
		for (int i = 0; i < 4; i++)
		{
			areaNumber[i] = rand() % 100 + 1;
		}
		isDamage = false;
	}
}

int Field::AreaProcess(int number)
{
	//ナンバーが10以下の場合の処理(確率10%)
	if (number <= 10&&isDamage==false)
	{
		pos = { 100,100 };
		testSprite->SetPosition(pos);
	}
	//ナンバーが10から30の場合の処理(確率20%)
	else if (number >= 10 && number <= 30 && isDamage == false)
	{
		pos = { 300,500 };
		testSprite->SetPosition(pos);
	}
	//ナンバーが30から50の時の処理(確率20%)
	else if (number >= 30 && number <= 50 && isDamage == false)
	{
		pos = { 500,700 };
		testSprite->SetPosition(pos);
	}
	//ナンバーが50から70の時の処理(確率20%)
	else if (number >= 50 && number <= 70 && isDamage == false)
	{
		pos = { 700,700 };
		testSprite->SetPosition(pos);
	}
	//ナンバーが70から90の時の処理(確率20%)
	else if (number >= 70 && number <= 90 && isDamage == false)
	{
		pos = { 900,700 };
		testSprite->SetPosition(pos);
	}
	//ナンバーが90以上の時の処理(確率10%)
	else if (number >= 90 && isDamage == false)
	{
		pos = { 1100,700 };
		testSprite->SetPosition(pos);
	}
	return number;
}
