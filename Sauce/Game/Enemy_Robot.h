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
    // ダメージ
    void OnDamaged() override;
    // 死亡
    void OnDead() override;

private:
    // 待機
    void TransitionIdleState();
    void UpdateIdleState(float elapsedTime);

    // 攻撃
    void TransitionAttackState();
    void UpdateAttackState(float elapsedTime);

    // 防御
    void TransitionDefenseState();
    void UpdateDefenseState(float elapsedTime);

    // 逃走
    void TransitionRunState();
    void UpdateRunState(float elapsedTime);

    // ダメージ
    void TransitionDamageState();
    void UpdateDamageState(float elapsedTime);

    // 死亡
    void TransitionDeathState();
    void UpdateDeathState(float elapsedTime);

private:
    // パラメーター
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