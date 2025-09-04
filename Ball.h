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

    void CheckPlayerCollision(Player& player); // ÉvÉåÉCÉÑÅ[Ç∆ÇÃè’ìÀ

private:
    static const int kBallCount = 10;
    Vector2 pos_[kBallCount];
    Vector2 vel_[kBallCount];
    Sprite* sprite_[kBallCount];
    uint32_t textureHandle_ = 0u;

    void MoveBalls();
    void CheckCollisions();
};