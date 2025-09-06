#include "Field.h"
#include <stdlib.h>
#include <stdio.h>
#include <TextureManager.h>
#include "Ball.h"
#include <time.h>

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
	//�{�[�����|�P�b�g�ɓ�������{�X���U�����Ă����Ƃ��ɏ��������֐�
	HandleBallPocket();
}

void Field::Draw()
{
	//testSprite->Draw();
}

void Field::HandleBallPocket()
{
	ballPositions = balls_->GetBallsPos();
	for (int i = 0; i < kBallCount; i++)
	{
		//�G���A�𕪂��ď���������
		if (CheckCollision(ballPositions[i], pockets[0]))
		{
			AreaProcess(areaNumber[0]);  //����̃|�P�b�g�����������̃G���A����
		}
		else if (CheckCollision(ballPositions[i], pockets[2]))
		{
			AreaProcess(areaNumber[1]); //�����̃|�P�b�g�����������̃G���A����
		}
		else if (CheckCollision(ballPositions[i], pockets[3]))
		{
			AreaProcess(areaNumber[2]); //�E���̃|�P�b�g�����������̃G���A����
		}
		else if (CheckCollision(ballPositions[i], pockets[1]))
		{
			AreaProcess(areaNumber[3]); //�E��̃|�P�b�g�����������̃G���A����
		}
		else if (CheckCollision(ballPositions[i], pockets[4]))
		{
			AreaProcess(areaNumber[0]);
			AreaProcess(areaNumber[3]); //�^�񒆏�̃|�P�b�g�����������̃G���A����
		}
		else if (CheckCollision(ballPositions[i], pockets[5]))
		{
			AreaProcess(areaNumber[1]);
			AreaProcess(areaNumber[2]); //�^�񒆉��̃|�P�b�g�����������̃G���A����
		}
	}
	
}

void Field::SetDamage(int damage)
{
	damage_ = damage;
}

void Field::GenerateRandomNumber()
{
	//�{�X���U�������邽�тɔ����������
	//�G���A���ʂ̂��߂̕ϐ����X�V����
	unsigned int currentTime = (unsigned int)time(nullptr);
	srand(currentTime);
	for (int i = 0; i < 4; i++)
	{
		areaNumber[i] = rand() % 100 + 1;
	}
	isDamage = false;
}

int Field::AreaProcess(int number)
{
	//���̓v���C���[��HP���񕜂�����^�[���Ƃ����T�O���Ȃ����߃R�����g�A�E�g
	////�i���o�[��10�ȉ��̏ꍇ�̏���(�m��10%)
	//if (number <= 10&&isDamage==false)
	//{
	//	//damage_ = damage_ / 2;
	//	pos = { 100,700 };
	//	testSprite->SetPosition(pos);
	//}
	////�i���o�[��10����30�̏ꍇ�̏���(�m��20%)
	//else if (number >= 10 && number <= 30 && isDamage == false)
	//{
	//	//damage_ = damage_ * 2;
	//	pos = { 300,700 };
	//	testSprite->SetPosition(pos);
	//}
	////�i���o�[��30����50�̎��̏���(�m��20%)
	//else if (number >= 30 && number <= 50 && isDamage == false)
	//{
	//	pos = { 500,700 };
	//	testSprite->SetPosition(pos);
	//}
	////�i���o�[��50����70�̎��̏���(�m��20%)
	//else if (number >= 50 && number <= 70 && isDamage == false)
	//{
	//	pos = { 700,700 };
	//	testSprite->SetPosition(pos);
	//}
	////�i���o�[��70����90�̎��̏���(�m��20%)
	//else if (number >= 70 && number <= 90 && isDamage == false)
	//{
	//	pos = { 900,700 };
	//	testSprite->SetPosition(pos);
	//}
	////�i���o�[��90�ȏ�̎��̏���(�m��10%)
	//else if (number >= 90 && isDamage == false)
	//{
	//	pos = { 1100,700 };
	//	testSprite->SetPosition(pos);
	//}
	//�Ƃ肠�������K���ł�����ʂ������ɒǉ�(���ׂđ������炱���͍폜���ď�L�̃R�����g�A�E�g����������)
	if (number <= 40 )
	{
		damage_ = 0;
	}
	else if (number >= 40 && number <= 80 )
	{
		damage_ = damage_ * 20;
	}
	else if (number >= 80 )
	{
		damage_ = damage_;
	}
	return number;
}

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
