#pragma once
#include "Scene.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Font.h"

#include "Player.h"
#include "Enemy.h"
#include "Enemy_Slime.h"
#include "Enemy_Zombie.h"
#include "Enemy_Robot.h"

enum State
{
    Town,
    Shop,
    Battle,
    Quit
};

// タイトルシーン
class SceneGame :public Scene
{
public:
    SceneGame() {}
    ~SceneGame()override {}

    // 初期化
    void Initialize() override;

    // 終了化
    void Finalize() override;

    // 更新処理
    void Update(float elapsedTime) override;

    // 描画処理
    void Render() override;

    // 描画
    void ImGuiRender();

    // 文字描画
    void FontRender();

    // シーン遷移
    void Change(float elapsedTime, Scene* nextScene);

    // 
    void StateSelect(State state01, State state02);

    // 準備完了しているか
    bool IsSelect() const { return select; }

    // 準備完了設定
    void SetSelect(bool setSelect) { select = setSelect; }

    // エネミー呼び出し
    void CallEnemy(Enemy* enemy);

private:
    int state = State::Town;

    bool select = false;

    std::unique_ptr<Sprite> sprite;

    // プレイヤー、エネミー
    std::unique_ptr<Player> player = nullptr;
    EnemySlime* slime = nullptr;
    EnemyRobot* robot = nullptr;
    EnemyZombie* zombie = nullptr;
};