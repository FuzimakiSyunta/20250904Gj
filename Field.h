#pragma once
#include <Vector2.h>
#include <Sprite.h>
#include "Input.h"
#include "Boss.h"

class Player;
class Ball;

class Field
{
public:
	void Initialize();

	void Update();

	void Draw();

	void DebugNumberDraw();

	void HandleBallPocket();

	void SetDamage(int damage);

	void SetPlayer(Player* player) { player_ = player; };

	void SetBalls(Ball* balls) { balls_ = balls; };

	void GenerateRandomNumber();

	void AreaDraw(int number, int AreaNumber);

	int AreaProcess(int number);

	int GetDamage() { return damage_; }

	bool CheckCollision(Vector2 pos1,Vector2 pos2);


	void SetBossType(bool isDragon); // BossがDragonかどうかを設定

	void ReviveBall();

	void SetBoss(Boss* boss) { boss_ = boss; }


private:
	int areaNumber[4]{ 0,0,0,0 };  //ポケットに入れるたびに変数を変更させている

	int areaCaunter[4]{ 0,0,0 };  //関数の値を子の変数に代入させている
	
	bool isDamage; //一回でも発動したか
	int damage_;

	Boss* boss_ = nullptr;

	
	Ball* balls_=nullptr;  //ボール
	const int kBallCount = 10;   //ボールの数
	std::vector<Vector2> ballPositions;  //ボールの座標
	Player* player_ = nullptr;

	
	Vector2 pos[12];  //エリアの画像に必要な座標
	Sprite* testSprite[12];  //エリアのスクリプト
	Input* input_ = nullptr; 
	uint32_t texttexture[3];  //エリアを表示するための画像

	Vector2 pockets[6] = {
	 { 242, 293 },   // 左上
	 { 1039, 293 },  // 右上
	 { 242, 672 },   // 左下
	 { 1039, 672 },  // 右下
	 { 641, 293 },   // 上中央
	 { 641, 672 }    // 下中央
	};

	bool hpDown;  //全ての処理をしてからHpを減らすために必要な変数


	bool isActive[10];


	bool isDragon_ = false; // デフォルトはスライムキング
	

};

