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
    // プレイヤー
    std::unique_ptr<Player> player = nullptr;
    // エネミー
    EnemySlime* slime = nullptr;
    EnemyRobot* robot = nullptr;
    EnemyZombie* zombie = nullptr;
    // UI
    std::unique_ptr<UIPaused> paused = nullptr;

    bool SceneChangeflg = false;
};