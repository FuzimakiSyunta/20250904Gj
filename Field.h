#pragma once
#include <Vector2.h>
#include <Sprite.h>
#include "Input.h"

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

	void AreaDraw(int number, Vector2 pos, int AreaNumber);

	void GenerateRandomArea();

	int AreaProcess(int number);

	int GetDamage() { return damage_; }

	bool CheckCollision(Vector2 pos1,Vector2 pos2);

private:
	int areaNumber[4]{ 0,0,0,0 };

	int areaCaunter[3]{ 0,0,0 };
	int areaCooltime;
	
	bool isDamage; //ˆê‰ñ‚Å‚à”­“®‚µ‚½‚©
	int damage_;

	int playerDamage;
	Ball* balls_=nullptr;
	const int kBallCount = 10;
	std::vector<Vector2> ballPositions;
	Player* player_ = nullptr;

	//‰¼‚Å•Ï”‚ğì‚é
	Vector2 pos[12];
	Sprite* testSprite[12];
	Input* input_ = nullptr; 
	uint32_t texttexture[3];
	bool isArea[12];

	Vector2 pockets[6] = {
		{202,250}, {1000,250}, {202,632},
		{1010,632}, {600,280}, {600,632}
	};


	uint32_t damageText[10];
	uint32_t poketTexture;

	Sprite* damageSprite[80];

};

