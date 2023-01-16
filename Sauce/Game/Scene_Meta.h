#pragma once
#include "Scene.h"

// 仮のシーン
class SceneMeta :public Scene
{
public:
    SceneMeta() {}
    ~SceneMeta()override {}

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