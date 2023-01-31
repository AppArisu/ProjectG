#pragma once
#include<memory>
#include "Scene.h"

#include "Player.h"
#include "Enemy.h"
#include "Enemy_Slime.h"
#include "Enemy_Zombie.h"
#include "Enemy_Robot.h"
#include "UI_Paused.h"

// 戦闘シーン
class SceneBattle :public Scene
{
public:
    SceneBattle() {}
    ~SceneBattle()override {}

    // 初期化
    void Initialize() override;

    // 終了化
    void Finalize() override;

    // 更新処理
    void Update(float elapsedTime) override;
    void ProcessInput() override;

    // 描画処理
    void Render() override;
    void RenderImGui() override;

    // シーン遷移
    void Change(float elapsedTime);

    // エネミー呼び出し
    void CallEnemy(Enemy* enemy);

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

    // 道具
    void TransitionToolsState();
    void UpdateToolsState(float elapsedTime);

    // 逃げる
    void TransitionRunState();
    void UpdateRunState(float elapsedTime);

    // 終了
    void TransitionEndState();
    void UpdateEndState(float elapsedTime);

    enum BState
    {
        Idle,
        Attack,
        Defense,
        Tools,
        Run,
        End
    };

private:
    // プレイヤー
    std::unique_ptr<Player> player = nullptr;
    // エネミー
    EnemySlime* slime = nullptr;
    EnemyRobot* robot = nullptr;
    EnemyZombie* zombie = nullptr;
    // UI
    std::unique_ptr<UIPaused> paused = nullptr;

    bool SceneChangeflg = false;

    BState state = BState::Idle;
};