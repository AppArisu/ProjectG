#include "UI_Screen.h"
#include "../Graphics/Graphic.h"

UIScreen::UIScreen(Scene* scene)
    :uiScene(scene), 
    mState(Active)
{
    sprite = std::make_unique<Sprite>("Data/Sprite/Texture/Fade.png");
}

void UIScreen::Render()
{
    Graphic& graphics = Graphic::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();

    float screenWidth = static_cast<float>(graphics.GetScreenWidth());
    float screenHeight = static_cast<float>(graphics.GetScreenHeight());
    float textureWidth = static_cast<float>(sprite->GetTextureWidth());
    float textureHeight = static_cast<float>(sprite->GetTextureHeight());

    sprite->Render(dc, 0.0f, 0.0f,
        screenWidth, screenHeight,
        0.0f, 0.0f,
        textureWidth, textureHeight,
        0.0f,
        1.0f, 1.0f, 1.0f, 0.3f);
}
