#include "PredictionLine.h"
#include <TextureManager.h>
#include <WinApp.h>
#include <algorithm>
#include <Player.h>

void PredictionLine::Initialize()
{
	pos = { 400,400 };
	uint32_t arrowTexture = TextureManager::Load("arrow.png");
	arrowSprite = Sprite::Create(arrowTexture, pos, { 1,1,1,1 }, { 0.5f,0.5f });
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
	//�}�E�X�ʒu�擾 
	GetCursorPos(&mousePosition);
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	Vector2 mousePos((float)mousePosition.x, (float)mousePosition.y);

	//�}�E�X�{�^���̏��
	SHORT mouseState = GetAsyncKeyState(VK_LBUTTON);
	isMouseDown = (mouseState & 0x8000) != 0;
	if (isMouseDown&&frame>=endframe) {
		//�����Ă�����
		if (!isCharging) {
			dragStartPos = mousePos; //���񂾂��L�^
			moveDir = Normalize(Subtract(cueStartPos, dragStartPos));

		}
		isCharging = true;
		
		//�}�E�X�ʒu�Ɩ_�̈ʒu�̕����x�N�g��
		
		Vector2 dragDelta = Subtract(mousePos, dragStartPos);
		float projectedLength = dragDelta.x * moveDir.x + dragDelta.y * moveDir.y;

		//���݂̖_�̈ʒu�Ə����ʒu�̍�
		Vector2 cueDelta = Subtract(cueCurrentPos, cueStartPos);
		float cueDirection = cueDelta.x * moveDir.x + cueDelta.y * moveDir.y;

		//�����ɉ�����projectedLength�𐧌�
		if (cueDirection >= 0.0f && projectedLength < 0.0f) {
			projectedLength = 0.0f;
		}
		else if (cueDirection < 0.0f && projectedLength > 0.0f) {
			projectedLength = 0.0f;
		}

		float maxPullDistance = 240.0f;
		projectedLength = std::clamp(projectedLength, 0.0f, maxPullDistance);

		//�摜�̂���ʂ��v�Z
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

			//�߂Â�����ʒu���Œ�
			if (t >= 1.0f)
			{
				cueCurrentPos = cueStartPos;
			}
			
		}
		
		
		if (!isCharging && frame >= endframe) {
			// �v���C���[�̒��S���W
			Vector2 center = player_->GetPos();
			if (frame == endframe) {
				cueStartPos = center;
			}


			// �}�E�X�ʒu����v���C���[�ւ̕����x�N�g��
			Vector2 toMouse = Subtract(mousePos, center);
			float angle = atan2f(toMouse.y, toMouse.x); // ���W�A���Ŋp�x�擾

			// �v���C���[�̎��͂ɔz�u�i�~����j
			float radius = 90.0f;
			Vector2 offset = { cosf(angle) * radius, sinf(angle) * radius };
			cueCurrentPos = Add(center, offset);

			// ���̌������}�E�X�����ɍ��킹��
			arrowSprite->SetRotation(angle + PI / 2);
		}
	}

	finalSpritePos = cueCurrentPos;
	//�_�̈ʒu���X�V
	arrowSprite->SetPosition(finalSpritePos);
	

}

void PredictionLine::Rotate()
{
	

	angle += rotationSpeed;
	if (angle > 2 * PI) {
		angle -= 2 * PI; // ���b�v�����i�p�x�������ɑ����Ȃ��悤�Ɂj
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


