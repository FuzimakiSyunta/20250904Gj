#include "Ball.h"
#include <cmath>
#include"input/Input.h"
Ball::Ball()
{
    for (int i = 0; i < kBallCount; i++) {
        sprite_[i] = nullptr;
        vel_[i] = { 0.0f, 0.0f };
    }
}

Ball::~Ball()
{
    for (int i = 0; i < kBallCount; i++) {
        delete sprite_[i];
    }
}

void Ball::Initialize(uint32_t /*textureHandle*/)
{
    textureHandle_ = TextureManager::Load("ball.png");

    int index = 0;
    const float startX = 300.0f;
    const float startY = 100.0f;
    const float ballSize = 32.0f;
    const float gap = 5.0f;

    int rowCounts[4] = { 4,3,2,1 };

    for (int row = 0; row < 4; row++) {
        int count = rowCounts[row];
        for (int col = 0; col < count; col++) {
            float offsetX = (col - count / 2.0f) * (ballSize + gap);
            float x = startX + offsetX;
            float y = startY + row * (ballSize + gap);

            pos_[index] = { x, y };
            sprite_[index] = Sprite::Create(textureHandle_, pos_[index]);
            index++;
        }
    }

    // デモ用：先頭の1個だけ動かす
    vel_[0] = { 2.0f, 1.5f };
}

void Ball::Update()
{
    // 移動処理を関数化
    MoveBalls();

    // 衝突判定
    CheckCollisions();

    // スプライト更新
    for (int i = 0; i < kBallCount; i++) {
        if (sprite_[i]) {
            sprite_[i]->SetPosition(pos_[i]);
        }
    }
}

void Ball::Draw()
{
    for (int i = 0; i < kBallCount; i++) {
        if (sprite_[i]) {
            sprite_[i]->Draw();
        }
    }
}

// ------------------------
// 弾の移動処理
// ------------------------
void Ball::MoveBalls()
{
    for (int i = 0; i < kBallCount; i++) {
        pos_[i].x += vel_[i].x;
        pos_[i].y += vel_[i].y;
    }
}

// ------------------------
// 弾同士の衝突判定（ビリヤード風）
// ------------------------
void Ball::CheckCollisions()
{
    const float radius = 16.0f; // 半径32pxの半分
    const float minDist = radius * 2.0f;

    for (int i = 0; i < kBallCount; i++) {
        for (int j = i + 1; j < kBallCount; j++) {
            float dx = pos_[j].x - pos_[i].x;
            float dy = pos_[j].y - pos_[i].y;
            float distSq = dx * dx + dy * dy;

            if (distSq < minDist * minDist) {
                float dist = std::sqrt(distSq);
                if (dist <= 0.0001f) dist = 0.0001f;

                float nx = dx / dist;
                float ny = dy / dist;

                float rvx = vel_[j].x - vel_[i].x;
                float rvy = vel_[j].y - vel_[i].y;
                float vn = rvx * nx + rvy * ny;

                if (vn < 0.0f) {
                    float impulse = -vn;
                    vel_[i].x -= impulse * nx;
                    vel_[i].y -= impulse * ny;
                    vel_[j].x += impulse * nx;
                    vel_[j].y += impulse * ny;
                }

                float overlap = (minDist - dist) * 0.5f;
                pos_[i].x -= nx * overlap;
                pos_[i].y -= ny * overlap;
                pos_[j].x += nx * overlap;
                pos_[j].y += ny * overlap;
            }
        }
    }
}
