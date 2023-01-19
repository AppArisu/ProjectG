#pragma once
#include"Enemy.h"

class EnemyRobot :public Enemy
{
public:
    EnemyRobot();
    ~EnemyRobot()override {}

    void Update(float elapsedTime);
    void Render(float elapsedTime);

    // ImGui
    void RenderImGui();

protected:
    // �_���[�W
    void OnDamaged() override;
    // ���S
    void OnDead() override;

private:
    // �ҋ@
    void TransitionIdleState();
    void UpdateIdleState(float elapsedTime);

    // �U��
    void TransitionAttackState();
    void UpdateAttackState(float elapsedTime);

    // �h��
    void TransitionDefenseState();
    void UpdateDefenseState(float elapsedTime);

    // ����
    void TransitionRunState();
    void UpdateRunState(float elapsedTime);

    // �_���[�W
    void TransitionDamageState();
    void UpdateDamageState(float elapsedTime);

    // ���S
    void TransitionDeathState();
    void UpdateDeathState(float elapsedTime);

private:
    // �p�����[�^�[
    struct Pram
    {
        int HP = 50;
        int MaxHP = 50;
        int Attack = 20;
        int Defense = 20;
        int Speed = 5;
    };

    enum class State
    {
        Idle,
        Attack,
        Defense,
        Run,
        Damage,
        Death
    };

private:
    State state = State::Idle;

};