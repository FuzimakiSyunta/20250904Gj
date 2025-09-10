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

	// テクスチャファイル名一覧
	const std::string textureFiles[3] = {
		"HpDown.png", "PowerDown.png", "PowerUp.png"
	};

	// テクスチャ読み込み
	for (int i = 0; i < 3; ++i) {
		texttexture[i] = TextureManager::Load(textureFiles[i]);
	}

	// PowerDown（texttexture[1]） → testSprite[0]〜[3]
	for (int i = 0; i < 4; ++i) {
		testSprite[i] = Sprite::Create(texttexture[1], pos[i], { 1,1,1,1 }, { 0.5f,0.5f });
	}

	// PowerUp（texttexture[2]） → testSprite[4]〜[7]
	for (int i = 4; i < 8; ++i) {
		testSprite[i] = Sprite::Create(texttexture[2], pos[i], { 1,1,1,1 }, { 0.5f,0.5f });
	}

	// HpDown（texttexture[0]） → testSprite[8]〜[11]
	for (int i = 8; i < 12; ++i) {
		testSprite[i] = Sprite::Create(texttexture[0], pos[i], { 1,1,1,1 }, { 0.5f,0.5f });
	}

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
	if (boss_ && boss_->GetType() == BossType::SlimeKing)
	{
		//画像を描画。値についてはランダムに変わる変数と順番に描画していく数(0から始まる)
		AreaDraw(areaNumber[0], 0);
		AreaDraw(areaNumber[1], 1);
		AreaDraw(areaNumber[2], 2);
		AreaDraw(areaNumber[3], 3);
	}
	else if (boss_ && boss_->GetType() == BossType::Dragon)
	{
		DragoAreaDraw(areaNumber[0], 0);
		DragoAreaDraw(areaNumber[1], 1);
		DragoAreaDraw(areaNumber[2], 2);
		DragoAreaDraw(areaNumber[3], 3);
	}
}

void Field::ProcessPocket(int ballIndex, int pocketIndex, int areaIndex, bool damageFlag) {
	AreaProcess(areaCaunter[areaIndex]);

	if (hpDown) {
		player_->TakeDamage(damage_);
		player_->SetIsDamage();
		hpDown = false;
	}

	isDamage = damageFlag;
	isActive[ballIndex] = false;
}

void Field::HandleBallPocket()
{
	ballPositions = balls_->GetBallsPos();

	for (int i = 0; i < kBallCount; i++)
	{
		if (!isActive[i]) continue;

		if (CheckCollision(ballPositions[i], pockets[0])) {
			ProcessPocket(i, 0, 0, true); // 左上
			break;
		}
		else if (CheckCollision(ballPositions[i], pockets[2])) {
			ProcessPocket(i, 2, 1, true); // 左下
			break;
		}
		else if (CheckCollision(ballPositions[i], pockets[3])) {
			ProcessPocket(i, 3, 2, true); // 右下
			break;
		}
		else if (CheckCollision(ballPositions[i], pockets[1])) {
			ProcessPocket(i, 1, 3, true); // 右上
			break;
		}
		else if (CheckCollision(ballPositions[i], pockets[4])) {
			AreaProcess(areaCaunter[0]);
			isDamage = false;
			AreaProcess(areaCaunter[3]);
			if (hpDown) {
				player_->TakeDamage(damage_);
				player_->SetIsDamage();
				hpDown = false;
			}
			isDamage = false;
			isActive[i] = false;
			break;
		}
		else if (CheckCollision(ballPositions[i], pockets[5])) {
			AreaProcess(areaCaunter[1]);
			isDamage = false;
			AreaProcess(areaCaunter[2]);
			if (hpDown) {
				player_->TakeDamage(damage_);
				player_->SetIsDamage();
				hpDown = false;
			}
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

void Field::DrawAreaSprite(int spriteOffset, int AreaNumber, int number) {
	const Vector2 positions[4] = {
		{430, 376}, // 左上
		{430, 586}, // 左下
		{848, 586}, // 右下
		{848, 376}  // 右上
	};

	int spriteIndex = spriteOffset + AreaNumber;
	pos[spriteIndex] = positions[AreaNumber];
	testSprite[spriteIndex]->SetPosition(pos[spriteIndex]);
	testSprite[spriteIndex]->Draw();
	areaCaunter[AreaNumber] = number;
}
//この関数は上記にあるareaNumberの値を見てどこに画像を描画するかを決める処理AreaNumberについては順番に描画されるように0～3を設定する
//ボスがスライムキングの時の確率
void Field::AreaDraw(int number, int AreaNumber) {
	if (number <= 20) {
		DrawAreaSprite(0, AreaNumber, number);  // testSprite[0〜3]
	}
	else if (number <= 65) {
		DrawAreaSprite(4, AreaNumber, number);  // testSprite[4〜7]
	}
	else if (number <= 75) {
		DrawAreaSprite(8, AreaNumber, number);  // testSprite[8〜11]
	}
	else {
		areaCaunter[AreaNumber] = number;       // 描画なし
	}
}

void Field::DragoAreaDraw(int number, int AreaNumber) {
	if (number <= 60) {
		DrawAreaSprite(8, AreaNumber, number);  // testSprite[8〜11]
	}
	else if (number <= 80) {
		DrawAreaSprite(4, AreaNumber, number);  // testSprite[4〜7]
	}
	else if (number <= 90) {
		DrawAreaSprite(0, AreaNumber, number);  // testSprite[0〜3]
	}
	else {
		areaCaunter[AreaNumber] = number;       // 描画なし
	}
}

int Field::AreaProcess(int number) {
	if (boss_ && boss_->GetType() == BossType::Dragon) {
		// ドラゴン用確率: ダメージ30%, バフ20%, デバフ10%, 他40%
		if (number <= 60 && !isDamage) {
			if (hpDown)
			{
				damage_ *= 2;
			}
			else if (!hpDown)
			{
				hpDown = true;
			}
			isDamage = true;
		}
		else if (number > 60 && number <= 80 && !isDamage) {
			damage_ *= 2; // バフ
			isDamage = true;
		}
		else if (number > 80 && number <= 90 && !isDamage) {
			damage_ /= 2; // デバフ
			isDamage = true;
		}
		else if (number > 90 && !isDamage) {
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
			if (hpDown)
			{
				damage_ *= 2;
			}
			else if (!hpDown)
			{
				hpDown = true;
			}
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

