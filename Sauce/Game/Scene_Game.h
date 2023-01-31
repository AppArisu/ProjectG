#pragma once
#include<memory>
#include "Scene.h"
#include "../Graphics/Sprite.h"

#include "Player.h"
#include "UI_Paused.h"

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
    void Change(Scene* nextScene);

private:
    // タウン
    void TransitionTwonState();
    void UpdateTwonState(float elapsedTime);

    // ショップ
    void TransitionShopState();
    void UpdateShopState(float elapsedTime);

    // バトル
    void TransitionBattleState();
    void UpdateBattleState(float elapsedTime);

    // 終了
    void TransitionEndState();
    void UpdateEndState(float elapsedTime);

    enum GState
    {
        Town,
        Shop,
        Battle,
        End
    };

private:
    GState state = GState::Town;

    bool SceneChangeflg = false;

    std::unique_ptr<Sprite> sprite;

    // プレイヤー
    std::unique_ptr<Player> player = nullptr;

    // UI
    std::unique_ptr<UIPaused> paused = nullptr;
};