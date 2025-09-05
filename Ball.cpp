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
            index++;
        }
    }

   // vel_[0] = { -10.0f, 0.0f }; // デモ用：1個だけ動かす
}

void Ball::Update() {
    MoveBalls();
    CheckCollisions();
}

void Ball::Draw() {
    for (int i = 0; i < kBallCount; i++)
        if (sprite_[i]) sprite_[i]->SetPosition(pos_[i]), sprite_[i]->Draw();
}

void Ball::MoveBalls() {
    const float radius = 16.0f;

    // 壁の位置（任意に設定可能）
    //左
    const float leftMax = 205.0f;
    //右
    const float rightMax = 1005.0f;
    //上
    const float topMax = 265.0f;
    //下
    const float bottomMax = 655.0f;

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
    const float ballRadius = 16.0f;
    const float ballMinDist = ballRadius * 2.0f;
    const float ballFriction = 0.99f; // 摩擦係数

    Vector2 playerPos = player.GetPos();
    float playerRadius = player.GetRadius();

    // === プレイヤーとの衝突処理 ===
    for (int i = 0; i < kBallCount; i++) {
        float dx = pos_[i].x - playerPos.x;
        float dy = pos_[i].y - playerPos.y;
        float distSq = dx * dx + dy * dy;
        float minDist = ballRadius + playerRadius;

        if (distSq < minDist * minDist) {
            float dist = std::sqrt(distSq);
            if (dist < 0.0001f) dist = 0.0001f;

            float nx = dx / dist;
            float ny = dy / dist;

            float rvx = vel_[i].x - player.GetVel().x;
            float rvy = vel_[i].y - player.GetVel().y;
            float vn = rvx * nx + rvy * ny;

            if (vn < 0.0f) {
                float impulse = -vn * 1.0f; // 反発係数1.0

                // ボールの速度
                vel_[i].x += impulse * nx;
                vel_[i].y += impulse * ny;

                // プレイヤーの速度（重めに設定）
                float playerImpulseFactor = 0.2f;
                player.SetVel(
                    player.GetVel().x - impulse * playerImpulseFactor * nx,
                    player.GetVel().y - impulse * playerImpulseFactor * ny
                );
            }

            // めり込み解消
            float overlap = (minDist - dist) * 0.5f;
            pos_[i].x += nx * overlap;
            pos_[i].y += ny * overlap;
            player.SetPos(playerPos.x - nx * overlap, playerPos.y - ny * overlap);
        }
    }

    // === ボール同士の衝突処理（完全弾性衝突） ===
    for (int i = 0; i < kBallCount; i++) {
        for (int j = i + 1; j < kBallCount; j++) {
            float dx = pos_[j].x - pos_[i].x;
            float dy = pos_[j].y - pos_[i].y;
            float distSq = dx * dx + dy * dy;

            if (distSq < ballMinDist * ballMinDist) {
                float dist = std::sqrt(distSq);
                if (dist < 0.0001f) dist = 0.0001f;

                float nx = dx / dist;
                float ny = dy / dist;

                // 相対速度
                float rvx = vel_[i].x - vel_[j].x;
                float rvy = vel_[i].y - vel_[j].y;
                float vn = rvx * nx + rvy * ny;

                if (vn < 0.0f) {
                    // === 等質量の完全弾性衝突 ===
                    vel_[i].x -= vn * nx;
                    vel_[i].y -= vn * ny;
                    vel_[j].x += vn * nx;
                    vel_[j].y += vn * ny;
                }

                // めり込み解消
                float overlap = (ballMinDist - dist) * 0.5f;
                pos_[i].x -= nx * overlap;
                pos_[i].y -= ny * overlap;
                pos_[j].x += nx * overlap;
                pos_[j].y += ny * overlap;
            }
        }

        // 摩擦による減速
        vel_[i].x *= ballFriction;
        vel_[i].y *= ballFriction;

        // 速度が十分小さい場合は停止
        if (std::abs(vel_[i].x) < 0.01f) vel_[i].x = 0.0f;
        if (std::abs(vel_[i].y) < 0.01f) vel_[i].y = 0.0f;
    }
}
