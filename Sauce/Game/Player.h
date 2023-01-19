#pragma once
#include "Character.h"

class Player :public Character
{
public:
    // コンストラクタ
    Player();
    // デストラクタ
    ~Player() override {}

    // インスタンス取得
    static Player& Instance()
    {
        static Player instance;
        return instance;
    }

    // 更新処理
    void Update(float elapsedTime)override;
    // 描画処理
    void Render(float elapsedTime)override;
    
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

    // 移動
    void TransitionMoveState();
    void UpdateMoveState(float elapsedTime);

    // 攻撃
    void TransitionAttackState();
    void UpdateAttackState(float elapsedTime);

    // 防御
    void TransitionDefenseState();
    void UpdateDefenseState(float elapsedTime);

    // 道具
    void TransitionToolState();
    void UpdateToolState(float elapsedTime);

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
        int HP = 100;
        int MaxHP = 100;
        int Attack = 30;
        int Defense = 20;
        int Speed = 10;
    };

    // ステート
    enum class State
    {
        Idle,
        Move,
        Attack,
        Defense,
        Tool,
        Run,
        Damage,
        Death
    };

private:
    State state = State::Idle;

};