#pragma once
#include <Vector2.h>
#include <Sprite.h>
#include <cassert>
class PredictionLine
{
public:
	void Initialize();

	void Update();

	void MouseProcess();

	void Draw();

	Vector2 Normalize(const Vector2& v)
	{
		Vector2 result;
		float length = (float)sqrt(v.x * v.x + v.y * v.y);
		if (length == 0.0f) {
			result.x = 0.0f;
			result.y = 0.0f;
		}
		else {
			result.x = v.x / length;
			result.y = v.y / length;
		}


		return result;
	}

	Vector2 Subtract(const Vector2& v1, Vector2& v2)
	{
		Vector2 result;
		result.x = v1.x - v2.x;
		result.y = v1.y - v2.y;
		return result;
	}

	Vector2 Multiply(float scalar, const Vector2& v)
	{
		Vector2 result;
		result.x = scalar * v.x;
		result.y = scalar * v.y;
		return result;
	}

	float Length(const Vector2& v)
	{
		float length = (float)sqrt(v.x * v.x + v.y * v.y);
		return length;
	}

	Vector2 Add(const Vector2& v1, const Vector2& v2)
	{
		Vector2 result;
		result.x = v1.x + v2.x;
		result.y = v1.y + v2.y;
		return result;
	}

	float easeInSine(float x) {

		return 1 - cos((x * PI) / 2);
	}

private:
	Vector2 pos;

	Vector2 acceleration;

	Sprite* arrowSprite = nullptr;

	POINT mousePosition;

	bool isLocked;
	float lockedAngle;

	const float PI = 3.1415926f;

	bool isCharging;
	Vector2 cueStartPos;
	Vector2 cueCurrentPos;
	float chargeSpeed; //引き速度
	float releaseSpeed; //戻る速度

	Vector2 dragStartPos; //マウスをクリックした位置を記録
	bool wasCharging;
	Vector2 finalSpritePos;
	Vector2 moveDir;

	//イージングに必要な変数
	float frame;
	float endframe;
	float easing;
	Vector2 startReleasePos;
	bool isMouseDown;
};

