#pragma once
#include"Character.h"

class Enemy :public Character
{
public:
    Enemy() {};
    ~Enemy()override {}

    // XVˆ—
    void Update(float elapsedTime) override {};
    // •`‰æˆ—
    void Render(float elapsedTime) override {};

    // ”j‰ó
    void Destroy();

protected:
    // ƒ_ƒ[ƒW
    void OnDamaged() override {};
    // €–S
    void OnDead() override {};

};