#pragma once
#include"Character.h"

class Enemy :public Character
{
public:
    Enemy() {};
    ~Enemy()override {}

    // �X�V����
    void Update(float elapsedTime) override {};
    // �`�揈��
    void Render(float elapsedTime) override {};

    // �j��
    void Destroy();

protected:
    // �_���[�W
    void OnDamaged() override {};
    // ���S
    void OnDead() override {};

};