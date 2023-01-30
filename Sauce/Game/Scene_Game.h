#pragma once
#include<memory>
#include "Scene.h"
#include "../Graphics/Sprite.h"

#include "Player.h"
#include "UI_Paused.h"

enum State
{
    Town,
    Shop,
    Battle,
    End
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
    void ProcessInput() override;

    // 描画処理
    void Render() override;

    // 描画
    void RenderImGui()override;

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

private:
    int state = State::Town;

    bool select = false;
    bool SceneChangeflg = false;

    std::unique_ptr<Sprite> sprite;

    // プレイヤー
    std::unique_ptr<Player> player = nullptr;

    // UI
    std::unique_ptr<UIPaused> paused = nullptr;
};