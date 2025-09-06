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

	void TakeDamage(int damage);  // �_���[�W���󂯂�
	int GetHp() const { return currentHp_; }

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
private://HP�Q�[�W
	uint32_t hpBackTex_ = 0u;
	uint32_t hpGaugeTex_ = 0u;
	std::unique_ptr<Sprite> hpBackSprite_;
	std::unique_ptr<Sprite> hpGaugeSprite_;
	bool isDebugdamage_ = false;
	int maxHp_ = 100;        // �ő�HP
	int currentHp_ = 100;    // ����HP
	bool isDead_ = false;    // ���S�t���O
};

