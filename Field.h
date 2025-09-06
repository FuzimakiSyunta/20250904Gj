#pragma once
#include <Vector2.h>
#include <Sprite.h>
#include "Input.h"
class Field
{
public:
	void Initialize();

	void Update();

	void Draw();

	void HandleBallPocket();

	int AreaProcess(int number);

private:
	int areaNumber[4]{ 0,0,0,0 };

	Vector2 posTopRight;  //�E��
	Vector2 posBottomRight; //�E��
	Vector2 posTopLeft; //����
	Vector2 posBottomLeft; //����
	bool isDamage; //���ł�����������

	//���ŕϐ������
	Vector2 pos;
	Sprite* testSprite = nullptr;
	Input* input_ = nullptr;

};

