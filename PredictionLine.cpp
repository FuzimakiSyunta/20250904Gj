#include "PredictionLine.h"
#include <TextureManager.h>
#include <WinApp.h>
#include <algorithm>
#include <Player.h>

void PredictionLine::Initialize()
{
	pos = { 400,400 };
	uint32_t arrowTexture = TextureManager::Load("arrow.png");
	arrowSprite = Sprite::Create(arrowTexture, pos, { 1,1,1,1 }, { 0.0f,0.5f });
	arrowSprite->SetPosition(Vector2(pos));

	isLocked = false;
	lockedAngle = 0.0f;

	wasCharging = false;
	frame = 0.0f;
	endframe = 20.0f;
	cueStartPos = player_->GetPos();
	//cueStartPos.x = cueStartPos.x - 90;
	angle = 0.0f;
	rotationSpeed = 1.0f;
}

void PredictionLine::Update()
{
	MouseProcess();
	//Rotate();
}

void PredictionLine::MouseProcess()
{
	//マウス位置取得 
	GetCursorPos(&mousePosition);
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	Vector2 mousePos((float)mousePosition.x, (float)mousePosition.y);

	//マウスボタンの状態
	SHORT mouseState = GetAsyncKeyState(VK_LBUTTON);
	isMouseDown = (mouseState & 0x8000) != 0;
	if (isMouseDown&&frame>=endframe) {
		//押している状態
		if (!isCharging) {
			dragStartPos = mousePos; //初回だけ記録
			moveDir = Normalize(Subtract(cueStartPos, dragStartPos));

		}
		isCharging = true;
		
		//マウス位置と棒の位置の方向ベクトル
		
		Vector2 dragDelta = Subtract(mousePos, dragStartPos);
		float projectedLength = dragDelta.x * moveDir.x + dragDelta.y * moveDir.y;

		//現在の棒の位置と初期位置の差
		Vector2 cueDelta = Subtract(cueCurrentPos, cueStartPos);
		float cueDirection = cueDelta.x * moveDir.x + cueDelta.y * moveDir.y;

		//方向に応じてprojectedLengthを制限
		if (cueDirection >= 0.0f && projectedLength < 0.0f) {
			projectedLength = 0.0f;
		}
		else if (cueDirection < 0.0f && projectedLength > 0.0f) {
			projectedLength = 0.0f;
		}

		float maxPullDistance = 240.0f;
		projectedLength = std::clamp(projectedLength, 0.0f, maxPullDistance);

		//画像のずれ量を計算
		Vector2 dragOffset = Multiply(projectedLength, moveDir);
		cueCurrentPos = Add(cueStartPos, dragOffset);
	}
	else {
		if (isCharging) {
			startReleasePos = cueCurrentPos;
			frame = 0;
			isCharging = false;
		}
		if (frame < endframe) {
			frame++;
			float t = std::clamp(frame / endframe, 0.0f, 1.0f);
			float easing = easeInSine(t);
			cueCurrentPos.x = startReleasePos.x + (cueStartPos.x - startReleasePos.x) * easing;
			cueCurrentPos.y = startReleasePos.y + (cueStartPos.y - startReleasePos.y) * easing;

			//近づいたら位置を固定
			if (t >= 1.0f)
			{
				cueCurrentPos = cueStartPos;
			}
			
		}
		
		
		if (!isCharging && frame >= endframe) {
			Vector2 target = player_->GetPos(); // 白い球の中心


			Vector2 arrowPos = mousePos; // 矢印をマウスの位置に置く
			arrowSprite->SetPosition(arrowPos);



			//float radius = 90.0f; // キューの長さや距離に応じて調整
			//Vector2 offset = { cosf(angle) * radius, sinf(angle) * radius };
			//Vector2 cuePos = Add(center, offset);

			Vector2 toTarget = Subtract(target, arrowPos);
			float angle = atan2f(toTarget.y, toTarget.x);
			arrowSprite->SetRotation(angle-PI/2); // 画像が右向きなら補正不要




		}
	}

	finalSpritePos = cueCurrentPos;
	//棒の位置を更新
	arrowSprite->SetPosition(finalSpritePos);
	

}

void PredictionLine::Rotate()
{
	

	angle += rotationSpeed;
	if (angle > 2 * PI) {
		angle -= 2 * PI; // ラップ処理（角度が無限に増えないように）
	}


	Vector2 center = player_->GetPos();
	float radius = 90.0f;
	Vector2 offset = { cosf(angle) * radius, sinf(angle) * radius };
	cueCurrentPos = Add(center, offset);
	arrowSprite->SetRotation(angle + PI / 2);
	arrowSprite->SetPosition(cueCurrentPos);


}

void PredictionLine::Draw()
{
	arrowSprite->Draw();
}


