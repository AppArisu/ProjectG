#pragma once
#include <memory>
#include "Scene.h"
#include "../Graphics/Sprite.h"


class UIScreen
{
public:
    UIScreen(Scene* scene);
    virtual ~UIScreen() {};

    virtual void Update() {};
    virtual void ProcessInput() {};
    virtual void Render();

    enum UIState
    {
        Active,
        Closing
    };

    void Closed() { mState = Closing; }

    auto GetUIState()const { return this->mState; }
    void SetUIState(UIState state) { mState = state; }

protected:
    // シーン
    Scene* uiScene = nullptr;
    // ステート
    UIState mState = UIState::Closing;

    std::unique_ptr<Sprite> sprite;
};