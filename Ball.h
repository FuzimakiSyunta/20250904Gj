#include "Sprite.h"
#include "TextureManager.h"
#include "Vector2.h"
#include <vector>
#include"Player.h"
class Ball {
public:
    Ball();
    ~Ball();

    void Initialize(uint32_t textureHandle);
    void Update();
    void Draw();

    void CheckPlayerCollision(Player& player); // �v���C���[�Ƃ̏Փ�
    int CheckPocketCollisions(); // �� �ǉ�

	void Respawn(); // �� �ǉ�

    std::vector<Vector2> GetBallsPos(); //�e�{�[���̍��W����

private:
    static const int kBallCount = 10;
    Vector2 pos_[kBallCount];
    Vector2 vel_[kBallCount];
    Sprite* sprite_[kBallCount];

    uint32_t ballTextureHandle_[kBallCount] = { 0u };

    // �� �f�o�b�O�����p ---------------------
    uint32_t debugCircleTex_ = 0u; // �Ԋ�(DebugCircle.png)�̃e�N�X�`��
    // ---------------------------------------
    Vector2 pocketPos_[6];   // �� ImGui�Œ�������|�P�b�g�ʒu

    bool isAlive_[kBallCount];  // �� �ǉ��F�{�[�����c���Ă��邩�ǂ���

    void MoveBalls();
    void CheckCollisions();
    

    int damage_[kBallCount]; // �e�{�[���̃_���[�W�l
};