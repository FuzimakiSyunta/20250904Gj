#pragma once

#include "Sprite.h"
#include "TextureManager.h"

class Ball {
public:
    Ball();
    ~Ball();

    void Initialize(uint32_t textureHandle);
    void Update();
    void Draw();

private:
    static const int kBallCount = 10;
    Vector2 pos_[kBallCount];
    Vector2 vel_[kBallCount];
    Sprite* sprite_[kBallCount];
    uint32_t textureHandle_ = 0u;

    void MoveBalls();           // š ’e‚ÌˆÚ“®‚ğŠÖ”‰»
    void CheckCollisions();     // š Õ“Ë”»’è
};
