#pragma once
#include <Vector2.h>
#include <Sprite.h>
#include "Input.h"

class Ball;

class Field
{
public:
	void Initialize();

	void Update();

	void Draw();

	void HandleBallPocket();

	void SetDamage(int damage);

	void SetBalls(Ball* balls) { balls_ = balls; };

	void GenerateRandomNumber();

	int AreaProcess(int number);

	int GetDamage() { return damage_; }

	bool CheckCollision(Vector2 pos1,Vector2 pos2);

private:
	int areaNumber[4]{ 0,0,0,0 };

	Vector2 posTopRight;  //�E��
	Vector2 posBottomRight; //�E��
	Vector2 posTopLeft; //����
	Vector2 posBottomLeft; //����
	bool isDamage; //���ł�����������
	int damage_;
	Ball* balls_=nullptr;
	const int kBallCount = 10;
	std::vector<Vector2> ballPositions;

	//���ŕϐ������
	Vector2 pos;
	Sprite* testSprite = nullptr;
	Input* input_ = nullptr; 

	Vector2 pockets[6] = {
		{202,250}, {1000,250}, {202,632},
		{1010,632}, {600,280}, {600,632}
	};




};

