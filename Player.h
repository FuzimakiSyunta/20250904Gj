#include "Sprite.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "Input.h"
class Player
{
public:
	
	void Initialize(Input* input, const Vector2& startPos = { 0,0 }, float radius = 16.0f);

	void Update();

	void Draw();

	void DamageTextDraw();

	Vector2 GetPos() const { return pos; }      // const �C���q��ǉ�
	
	float GetRadius() const { return radius_; } // const �C���q��ǉ�
	Vector2 GetVel() const { return vel_; }
	int GetHp() { return currentHp_; }
	void SetVel(float x, float y) { vel_ = { x, y }; }
	void SetPos(float x, float y) { pos = { x, y }; }
	void TakeDamage(int damage);

	void CheckPocketCollision();
	// Setter
	void SetBallSpeed0(bool value) { ballspeed0 = value; }
	void SetIsDamage() { isDamage = true; }
	// Getter
	bool GetBallSpeed0() const { return  ballspeed0; }
private:
	bool IsStopped() const;


private:
#pragma region �摜�ǂݍ���
	Input* input_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t playerTexture_ = 0;
	uint32_t playerArrowTexture = 0;
	//�X�v���C�g
	std::unique_ptr<Sprite> playerSprite_ = nullptr;
	std::unique_ptr<Sprite> playerArrowSprite_ = nullptr;
	//HP�Q�[�W
	uint32_t hpBackTex_ = 0;
	uint32_t hpGaugeTex_ = 0;
	uint32_t hphartTex_ = 0;
	std::unique_ptr<Sprite> hpBackSprite_;
	std::unique_ptr<Sprite> hpGaugeSprite_;
	std::unique_ptr<Sprite> hpHartSprite_;

#pragma region ���W�֘A

	Vector2 pos = {250,1050};
	Vector2 ArrowpPos = {pos};
	Vector2 localPos;
	const float speed = 10.6f;
	const Vector2 center = { 5, 5 };
	float collisionRadius_; // �����蔻��p�i�����߂ɐݒ�j
	float drawRadius_;       // �����ڗp�̔��a
	float radius_ = 16.0f;
	Vector2 vel_ = { 0.0f, 0.0f };
	bool dragging_;
	Vector2 dragStart_;
	Vector2 dragCurrent_;

	bool arrowFlying_ = false;
	Vector2 arrowVel_;
	bool arrowReturning_ = false; // ��󂪖߂��Ă���Œ���

	int maxHp_ = 7;
	int currentHp_ = 7;

	int invincibleTimer_ = 0; // ���G���ԃJ�E���^

	std::unique_ptr<Sprite> damageSprite_;
	uint32_t damageText;
	bool isDamage;
	int damageCooltime;

	uint32_t gameOverText;
	Sprite* gameOverSprite = nullptr;

	float barWidth;
	float barHeight;
	float screenWidth;   // ��ʕ�
	float barX; // ����
	float barY; // Y�ʒu�w��
	// �E���ɂ��炷�I�t�Z�b�g
	Vector2 offset = { 4.0f, 4.0f };
	// HPバー揺れ
	bool hpBarShaking_ = false;
	int hpBarShakeTimer_ = 0;
	float hpBarShakeStrength_ = 5.0f; // 揺れ幅
	bool ballspeed0 = true;
};

