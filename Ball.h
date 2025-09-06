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

    void CheckPlayerCollision(Player& player); // プレイヤーとの衝突

private:
    static const int kBallCount = 10;
    Vector2 pos_[kBallCount];
    Vector2 vel_[kBallCount];
    Sprite* sprite_[kBallCount];
    uint32_t textureHandle_ = 0u;

    // ★ デバッグ可視化用 ---------------------
    uint32_t debugCircleTex_ = 0u; // 赤丸(DebugCircle.png)のテクスチャ
    // ---------------------------------------
    Vector2 pocketPos_[6];   // ← ImGuiで調整するポケット位置

    bool isAlive_[kBallCount];  // ★ 追加：ボールが残っているかどうか

    void MoveBalls();
    void CheckCollisions();
    void CheckPocketCollisions(); // ★ 追加
};