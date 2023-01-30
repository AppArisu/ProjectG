#include "UI_Quit.h"

UIQuit::UIQuit(Scene* scene)
    :UIScreen(scene)
{
    uiScene->SetGameState(GameState::Quit);
}

void UIQuit::Update()
{
}

void UIQuit::Render()
{
}
