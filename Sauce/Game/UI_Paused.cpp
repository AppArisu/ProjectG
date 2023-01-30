#include "UI_Paused.h"
#include "../Input.h"

UIPaused::UIPaused(Scene* scene)
    :UIScreen(scene)
{
    uiScene->SetGameState(GameState::Paused);
}

void UIPaused::Update()
{
    if (GetKeyState(VK_BACK) & 0x8000)
    {
        Closed();
        uiScene->SetGameState(GameState::Play);
    }
}

void UIPaused::Render()
{
    UIScreen::Render();
}
