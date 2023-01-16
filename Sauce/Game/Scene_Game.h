#pragma once
#include "Scene.h"

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

    // シーン遷移
    void Change(float elapsedTime);
};