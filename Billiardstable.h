#include "Sprite.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "Input.h"

class Billiardstable
{
public:

	void Initialize();

	void Update();

	void Draw();

	Vector2 GetPos() { return pos; }
private:
#pragma region �摜�ǂݍ���
	//�e�N�X�`���n���h��
	uint32_t billiardstableTexture_ = 0;
	//�X�v���C�g
	std::unique_ptr<Sprite> billiardstableSprite_ = nullptr;

#pragma region ���W�֘A

	Vector2 pos = { 0,0 };
	Vector2 localPos;
	const Vector2 center = { 1, 1 };
};

