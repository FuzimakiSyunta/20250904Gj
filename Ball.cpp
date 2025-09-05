#include "Ball.h"
#include <cmath>
#include"input/Input.h"

Ball::Ball() {
    for (int i = 0; i < kBallCount; i++) {
        sprite_[i] = nullptr;
        vel_[i] = { 0.0f, 0.0f };
    }
}

Ball::~Ball() {
    for (int i = 0; i < kBallCount; i++)
        delete sprite_[i];
}

void Ball::Initialize(uint32_t /*textureHandle*/) {
    textureHandle_ = TextureManager::Load("ball.png");
    debugCircleTex_ = TextureManager::Load("DebugCircle.png"); // ★ 赤丸画像ロード

    int index = 0;
    const float startX = 700.0f;
    const float startY = 460.0f;
    const float ballSize = 11.0f;
    const float gap = 40.0f;

    int rowCounts[4] = { 1,2,3,4 };
    for (int col = 0; col < 5; col++) {
        int count = rowCounts[col];
        for (int row = 0; row < count; row++) {
            float offsetY = (row - (count - 1) / 2.0f) * gap;
            float x = startX + col * gap;
            float y = startY + offsetY;

            pos_[index] = { x, y };
            sprite_[index] = Sprite::Create(textureHandle_, pos_[index]);
            isAlive_[index] = true;   // ★ 生存フラグをON
            index++;
        }
    }

   // vel_[0] = { -10.0f, 0.0f }; // デモ用：1個だけ動かす
}

void Ball::Update() {
    MoveBalls();
    CheckCollisions();
    CheckPocketCollisions(); // ★ 追加

}

void Ball::Draw() {
    // ボール描画
    for (int i = 0; i < kBallCount; i++) {
        if (isAlive_[i] && sprite_[i]) {
            sprite_[i]->SetPosition(pos_[i]);
            sprite_[i]->Draw();
        }
    }

    // デバッグ用：ポケット位置に赤丸を描画
    Vector2 pockets[6] = {
        {202,250},   // 左上
        {1000,250},  // 右上
        {202,632},   // 左下
        {1000,632},  // 右下
        {600,250},   // 上中央
        {600,632}    // 下中央
    };

    for (int j = 0; j < 6; j++) {
        Sprite* debug = Sprite::Create(debugCircleTex_, pockets[j]);
        debug->Draw();
        
    }
}


void Ball::MoveBalls() {
    const float radius = 16.0f;

    // 壁の位置（任意に設定可能）
    //左
    const float leftMax = 210.0f;
    //右
    const float rightMax = 1000.0f;
    //上
    const float topMax = 270.0f;
    //下
    const float bottomMax = 650.0f;

    // 壁の反射係数
    const float xBounce = -1.0f; // 左右
    const float yBounce = -1.0f; // 上下

    for (int i = 0; i < kBallCount; i++) {
        pos_[i].x += vel_[i].x;
        pos_[i].y += vel_[i].y;

        // 左壁
        if (pos_[i].x < leftMax + radius) {
            pos_[i].x = leftMax + radius;
            vel_[i].x *= xBounce;
        }
        // 右壁
        else if (pos_[i].x > rightMax - radius) {
            pos_[i].x = rightMax - radius;
            vel_[i].x *= xBounce;
        }

        // 上壁
        if (pos_[i].y < topMax + radius) {
            pos_[i].y = topMax + radius;
            vel_[i].y *= yBounce;
        }
        // 下壁
        else if (pos_[i].y > bottomMax - radius) {
            pos_[i].y = bottomMax - radius;
            vel_[i].y *= yBounce;
        }
    }
}

void Ball::CheckCollisions() {
    const float radius = 16.0f;
    const float minDist = radius * 2.0f;
    const float friction = 0.99f; // 摩擦係数（0.0～1.0） 1.0に近いほど滑る

    for (int i = 0; i < kBallCount; i++) {
        for (int j = i + 1; j < kBallCount; j++) {
            float dx = pos_[j].x - pos_[i].x;
            float dy = pos_[j].y - pos_[i].y;
            float distSq = dx * dx + dy * dy;

            if (distSq < minDist * minDist) {
                float dist = std::sqrt(distSq);
                if (dist < 0.0001f) dist = 0.0001f;
                float nx = dx / dist;
                float ny = dy / dist;

                float rvx = vel_[j].x - vel_[i].x;
                float rvy = vel_[j].y - vel_[i].y;
                float vn = rvx * nx + rvy * ny;

                if (vn < 0.0f) {
                    float impulse = -vn * 1.0f; // ここは控えめ
                    vel_[i].x -= impulse * nx;
                    vel_[i].y -= impulse * ny;
                    vel_[j].x += impulse * nx;
                    vel_[j].y += impulse * ny;
                }

                // めり込み解消
                float overlap = (minDist - dist) * 0.5f;
                pos_[i].x -= nx * overlap;
                pos_[i].y -= ny * overlap;
                pos_[j].x += nx * overlap;
                pos_[j].y += ny * overlap;
            }
        }

        // 摩擦で減速
        vel_[i].x *= friction;
        vel_[i].y *= friction;

        // 速度が小さすぎる場合は止める
        if (std::abs(vel_[i].x) < 0.01f) vel_[i].x = 0.0f;
        if (std::abs(vel_[i].y) < 0.01f) vel_[i].y = 0.0f;
    }
}

void Ball::CheckPlayerCollision(Player& player) {
    const float radius = 16.0f;
    const float restitution = 1.9f; // 反発係数
    Vector2 playerPos = player.GetPos();
    float playerRadius = player.GetRadius();

    for (int i = 0; i < kBallCount; i++) {
        float dx = pos_[i].x - playerPos.x;
        float dy = pos_[i].y - playerPos.y;
        float distSq = dx * dx + dy * dy;
        float minDist = radius + playerRadius;

        if (distSq < minDist * minDist) {
            float dist = std::sqrt(distSq);
            if (dist < 0.0001f) dist = 0.0001f;

            // 法線ベクトル
            float nx = dx / dist;
            float ny = dy / dist;

            // 相対速度
            float rvx = vel_[i].x - player.GetVel().x;
            float rvy = vel_[i].y - player.GetVel().y;
            float vn = rvx * nx + rvy * ny;

            if (vn < 0.0f) {
                // 衝突インパルス（ボールとプレイヤーで質量比をつけてもOK）
                float impulse = -vn * restitution;

                // ボールに反映
                vel_[i].x += impulse * nx;
                vel_[i].y += impulse * ny;

                // プレイヤーにも少しだけ影響を与える（重い扱い）
                float playerImpulseFactor = 0.2f; // ← プレイヤーの重さを調整
                player.SetVel(player.GetVel().x - impulse * playerImpulseFactor * nx,
                    player.GetVel().y - impulse * playerImpulseFactor * ny);
            }

            // めり込み解消（お互いに動かす）
            float overlap = (minDist - dist) * 0.5f;
            pos_[i].x += nx * overlap;
            pos_[i].y += ny * overlap;
            player.SetPos(playerPos.x - nx * overlap, playerPos.y - ny * overlap);
        }
    }
}

void Ball::CheckPocketCollisions() {
    Vector2 pockets[6] = {
        {202,250},   // 左上
        {1000,250},  // 右上
        {202,632},   // 左下
        {1010,632},  // 右下
        {600,280},   // 上中央
        {600,632}    // 下中央
    };

    float pocketRadius = 38.0f;

    for (int i = 0; i < kBallCount; i++) {
        if (!isAlive_[i]) continue;

        for (int j = 0; j < 6; j++) {
            float dx = pos_[i].x - pockets[j].x;
            float dy = pos_[i].y - pockets[j].y;
            float distSq = dx * dx + dy * dy;
            if (distSq < pocketRadius * pocketRadius) {
                isAlive_[i] = false;
                break;
            }
        }
    }
}
