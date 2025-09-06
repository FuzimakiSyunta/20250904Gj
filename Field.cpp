#include "Field.h"
#include <stdlib.h>
#include <stdio.h>
#include <TextureManager.h>

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
	testSprite->Draw();
}

void Field::HandleBallPocket()
{
	//�G���A�𕪂��ď���������
	if (input_->PushKey(DIK_Q))
	{
		AreaProcess(areaNumber[0]);  //����̃|�P�b�g�����������̃G���A����
		//isDamage = true;
	}
	else if (input_->PushKey(DIK_Z))
	{
		AreaProcess(areaNumber[1]); //�����̃|�P�b�g�����������̃G���A����
		//isDamage = true;
	}
	else if (input_->PushKey(DIK_M))
	{
		AreaProcess(areaNumber[2]); //�E���̃|�P�b�g�����������̃G���A����
		//isDamage = true;
	}
	else if (input_->PushKey(DIK_O))
	{
		AreaProcess(areaNumber[3]); //�E��̃|�P�b�g�����������̃G���A����
		//isDamage = true;
	}
	else if (input_->PushKey(DIK_Q) && input_->PushKey(DIK_O))
	{
		AreaProcess(areaNumber[0]);
		AreaProcess(areaNumber[3]); //�^�񒆏�̃|�P�b�g�����������̃G���A����
		//isDamage = true;
	}
	else if (input_->PushKey(DIK_Z) && input_->PushKey(DIK_M))
	{
		AreaProcess(areaNumber[1]);
		AreaProcess(areaNumber[2]); //�^�񒆉��̃|�P�b�g�����������̃G���A����
		//isDamage = true;
	}
	//�{�X���U�������邽�тɔ����������
	//�G���A���ʂ̂��߂̕ϐ����X�V����
	if (input_->PushKey(DIK_H))
	{
		for (int i = 0; i < 4; i++)
		{
			areaNumber[i] = rand() % 100 + 1;
		}
		isDamage = false;
	}
}

int Field::AreaProcess(int number)
{
	//�i���o�[��10�ȉ��̏ꍇ�̏���(�m��10%)
	if (number <= 10&&isDamage==false)
	{
		pos = { 100,100 };
		testSprite->SetPosition(pos);
	}
	//�i���o�[��10����30�̏ꍇ�̏���(�m��20%)
	else if (number >= 10 && number <= 30 && isDamage == false)
	{
		pos = { 300,500 };
		testSprite->SetPosition(pos);
	}
	//�i���o�[��30����50�̎��̏���(�m��20%)
	else if (number >= 30 && number <= 50 && isDamage == false)
	{
		pos = { 500,700 };
		testSprite->SetPosition(pos);
	}
	//�i���o�[��50����70�̎��̏���(�m��20%)
	else if (number >= 50 && number <= 70 && isDamage == false)
	{
		pos = { 700,700 };
		testSprite->SetPosition(pos);
	}
	//�i���o�[��70����90�̎��̏���(�m��20%)
	else if (number >= 70 && number <= 90 && isDamage == false)
	{
		pos = { 900,700 };
		testSprite->SetPosition(pos);
	}
	//�i���o�[��90�ȏ�̎��̏���(�m��10%)
	else if (number >= 90 && isDamage == false)
	{
		pos = { 1100,700 };
		testSprite->SetPosition(pos);
	}
	return number;
}
