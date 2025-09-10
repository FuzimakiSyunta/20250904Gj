#include "Sprite.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "Input.h"
#include "WinApp.h"
class Boss;
class Field;
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
	void SetBoss(Boss* boss) { boss_ = boss; }
	void SetField(Field* field) { field_ = field; }
	// Getter
	bool GetBallSpeed0() const { return  ballspeed0; }

	bool IsSceneEnd() { return isSceneEnd_; }
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

	uint32_t nextStrikeTexture_ = 0;
	std::unique_ptr<Sprite>  nextStrikeSprite_ = nullptr;
	//HPゲージ
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
	Vector2  nextStriket_{ -400,400 };
	float nextStriketSpeed = 15.0f;
	bool arrowFlying_ = false;
	Vector2 arrowVel_;
	bool arrowReturning_ = false; // ��󂪖߂��Ă���Œ���

	int maxHp_ = 100;
	int currentHp_ = 100;

	int invincibleTimer_ = 0; // ���G���ԃJ�E���^

	
	bool isDamage;
	int damageCooltime;

	uint32_t damageText[10];
	Sprite* damageSprite[20];
	Vector2 damagePos[2];

	uint32_t gameOverText;
	Sprite* gameOverSprite = nullptr;
	uint32_t gameButton;
	std::unique_ptr<Sprite> gameButtonSprite;
	POINT mousePosition;
	bool isSceneEnd_;
	int damage_;
	
	int playerDamage; //プレイヤーがポケットに入った時に食らうダメージ
	Boss* boss_;
	Field* field_=nullptr;
	bool isChange;

	int slimeDamage = 10;  //スライムのダメージ
	int dragonDamage = 20;  //ドラゴンのダメージ
	
	int nextStriketstop = 0;
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
	bool NextStop = true;
	bool strikeWaiting_ = false;   // 待機中かどうか
	int strikeWaitTimer_ = 120;      // 待機時間（フレーム）
	float strikeTargetX_ = 600.0f; // 目標座標（例: X=600で停止）
};

//650, 400