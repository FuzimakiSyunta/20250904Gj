#include "GameExplanation.h"
GameExplanation::GameExplanation()
{
}

GameExplanation::~GameExplanation()
{
}

void GameExplanation::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	//�w�i�̉摜�̃f�[�^�擾
	uint32_t Explanationtexture = TextureManager::Load("sample.png");
	//�摜�̍��W
	pos = { 400,400 };
	explanationSprite = Sprite::Create(Explanationtexture, pos, { 1,1,1,1 }, { 0.5f,0.5f });
	//�����ɃV�[���Ɉڂ�Ȃ����߂̃N�[���^�C��������
	sceneCooltime = 0;
}

void GameExplanation::Update()
{
	//�}�E�X�̍��W���擾
	GetCursorPos(&mousePosition);
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);
	//--------------------//
	
	//�����ɃV�[���Ɉڂ�Ȃ��悤�ɂ��鏈��
	if (isSceneEnd_ == false)
	{
		sceneCooltime++;
	}
	//�{�^����N���b�N�������玟�̃V�[���ɍs�����߂̏���
	if (input_->PushKey(DIK_SPACE)&&sceneCooltime>10||
		mousePosition.x >= 400 && mousePosition.x <= 700 && mousePosition.y >= 200 && mousePosition.y <= 500 && input_->IsPressMouse(WM_LBUTTONDOWN == 0)&&sceneCooltime>10)
	{
		isSceneEnd_ = true;
	}
}

void GameExplanation::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>
	explanationSprite->Draw();
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Model::PreDraw(commandList);

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	// 3D�I�u�W�F�N�g�`��㏈��
	Model::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(commandList);

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();

#pragma endregion
}