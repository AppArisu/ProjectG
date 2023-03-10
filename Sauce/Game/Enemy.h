#pragma once
#include"Character.h"

class Enemy :public Character
{
public:
    Enemy() {};
    ~Enemy()override {}

    // 更新処理
    void Update(float elapsedTime) override {};
    // 描画処理
    void Render(float elapsedTime) override {};

    // 破壊
    void Destroy();

protected:
    // ダメージ
    void OnDamaged() override {};
    // 死亡
    void OnDead() override {};

};