#pragma once
#include "Scene.h"
#include"../Graphics/Sprite.h"
#include"../Graphics/Texture.h"
#include"../Graphics/Font.h"

// タイトルシーン
class SceneTitle :public Scene
{
public:
    SceneTitle() {}
    ~SceneTitle()override {}

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

    void ImGuiRender();

private:
    // フォント
    DirectWrite* Write = nullptr;

    std::unique_ptr<Sprite> sprite;
    std::unique_ptr<Texture> texture;

    // UVスクロールデータ
    UVScrollData uvScrollData;

    // マスク画像
    std::unique_ptr<Texture> maskTexture;
    float dissolveThreshold = 0.0f;
    bool dissolveFlg = false;

};