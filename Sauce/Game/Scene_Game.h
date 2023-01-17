#pragma once
#include "Scene.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Font.h"

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

    // 画像描画
    void SpriteRender();

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

    // フォント
    DirectWrite* Write = nullptr;

    Sprite* sprite = nullptr;
};