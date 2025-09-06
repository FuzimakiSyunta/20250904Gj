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

	Vector2 posTopRight;  //‰Eã
	Vector2 posBottomRight; //‰E‰º
	Vector2 posTopLeft; //¶ã
	Vector2 posBottomLeft; //¶‰º
	bool isDamage; //ˆê‰ñ‚Å‚à”­“®‚µ‚½‚©

	//‰¼‚Å•Ï”‚ğì‚é
	Vector2 pos;
	Sprite* testSprite = nullptr;
	Input* input_ = nullptr;

};

