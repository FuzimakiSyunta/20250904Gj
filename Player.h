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

	Vector2 GetPos() { return pos; }
private:
#pragma region �摜�ǂݍ���
	Input* input_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t playerTexture_ = 0;
	//�X�v���C�g
	std::unique_ptr<Sprite> playerSprite_ = nullptr;

#pragma region ���W�֘A

	Vector2 pos = {0,0};
	Vector2 localPos;
	const float speed = 2.6f;
	const Vector2 center = { 5, 5 };
	float radius_ = 16.0f;

};

