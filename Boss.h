#pragma once
#include "Sprite.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "Input.h"
class Boss
{
public:
	void Initialize(Input* input);
	void Update();
	void Draw();
	void OnDamage(); // �� �_���[�W���󂯂��Ƃ��ɌĂԊ֐�

private:
	Input* input_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t bossTexture_ = 0;
	uint32_t bossDamegeTexture_ = 0;
	//�X�v���C�g
	std::unique_ptr<Sprite> bossSprite_ = nullptr;
	std::unique_ptr<Sprite> bossDamegeSprite_ = nullptr;
	Vector2 basePos_ = { 540.0f, 40.0f }; // ���̍��W
	bool isShaking_ = false;
	int shakeTimer_ = 0;
	float shakeStrength_ = 5.0f; // �h��̋���
private:
	bool isDebugdamage_ = false;
};

