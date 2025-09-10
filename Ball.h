#include "Sprite.h"
#include "TextureManager.h"
#include "Vector2.h"
#include <vector>
#include"Player.h"

class Field;
class Ball {
public:
    Ball();
    ~Ball();

    void Initialize(uint32_t textureHandle);
    void Update();
    void Draw();

    bool CheckCollisions();
    bool CheckPlayerCollision(Player& player); // プレイヤーとの衝突
    bool CheckPocketCollisions(); // ★ 追加

	void Respawn(); // ★ 追加
    bool AreAllBallsStopped() const;
    std::vector<Vector2> GetBallsPos(); //各ボールの座標を代入

    void SetField(Field* field) { field_ = field; }

    void SetAudio(Audio* audio) { audio_ = audio; } // ★ Audioを受け取る


private:
    static const int kBallCount = 10;
    Vector2 pos_[kBallCount];
    Vector2 vel_[kBallCount];
    Sprite* sprite_[kBallCount];

    uint32_t ballTextureHandle_[kBallCount] = { 0u };

    uint32_t ballCollideHandle_ = 0;  // ★ 効果音のハンドル

    Audio* audio_ = nullptr;        // Audioインスタンス

    // ★ デバッグ可視化用 ---------------------
    uint32_t debugCircleTex_ = 0u; // 赤丸(DebugCircle.png)のテクスチャ
    // ---------------------------------------
    Vector2 pocketPos_[6];   // ← ImGuiで調整するポケット位置

    bool isAlive_[kBallCount];  // ★ 追加：ボールが残っているかどうか

    void MoveBalls();
 
    
    Player* player_=nullptr;
    int damage_[kBallCount]; // 各ボールのダメージ値
    Input* input_ = nullptr;

    Field* field_ = nullptr;
    uint32_t playSound_;

    bool collided = false;
	bool hit = false;
	bool fallInPocket = false;
};