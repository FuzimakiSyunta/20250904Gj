#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Scene.h"
class GameExplanation
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameExplanation();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameExplanation();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	bool IsSceneEnd() { return isSceneEnd_; }
	Scene::SceneType NextScene() { return Scene::SceneType::kGamePlay; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	Sprite* explanationSprite = nullptr;
	Vector2 pos;
	bool isSceneEnd_ = false;
	POINT mousePosition;

	int sceneCooltime; //�V�[���Ɉڂ�ς��������u�����N�[���^�C����p�ӂ��A���ňڂ�ς��Ȃ��悤�ɂ���
};

