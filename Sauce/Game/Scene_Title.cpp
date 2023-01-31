#include "Scene_Title.h"
#include "Scene_Game.h"
#include "../Graphics/Graphic.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "../Input.h"

// 初期化
void SceneTitle::Initialize()
{
    // テクスチャ読み込み
    texture = std::make_unique<Texture>("Data/Sprite/Title.png");
    // マスクテクスチャ読み込み
    maskTexture = std::make_unique<Texture>("Data/Sprite/Texture/dissolve01.png");
    dissolveThreshold = 1.0f;
    dissolveFlg = false;

    // スプライト
    sprite = std::make_unique<Sprite>();
    sprite->SetShaderResourceView(texture->GetShaderResourceView(), texture->GetWidth(), texture->GetHeight());
}

// 終了化
void SceneTitle::Finalize()
{
}

// 更新処理
void SceneTitle::Update(float elapsedTime)
{
    ProcessInput();

    if (SceneChangeflg)
    {
        Change(elapsedTime);
    }

    // エフェクト
    {
        // ディゾブル
        sprite->Update(0.0f, 0.0f,
            Graphic::Instance().GetScreenWidth(), Graphic::Instance().GetScreenHeight(),
            0.0f, 0.0f,
            static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()),
            0.0f,
            1.0f, 1.0f, 1.0f, 1.0f);
    }
}

void SceneTitle::ProcessInput()
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    const GamePadButton anyButton =
        GamePad::BTN_A
        | GamePad::BTN_B
        | GamePad::BTN_X
        | GamePad::BTN_Y
        ;

    if (gamePad.GetButtonDown() & anyButton)
    {
        SceneChangeflg = true;
    }
}

// 描画処理
void SceneTitle::Render()
{
    Graphic& graphics = Graphic::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();
    
    // 画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA(0.0～1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    // スプライト
    {
        RenderContext rc;
        rc.deviceContext = dc;

        SpriteShader* spShader = graphics.GetSprite(static_cast<int>(SpriteTypeID::Mask));

        spShader->Begin(rc);

        rc.uvScrollData = uvScrollData;
        rc.maskData.maskTexture = maskTexture->GetShaderResourceView().Get();
        rc.maskData.dissolveThreshold = dissolveThreshold;

        spShader->Draw(rc, sprite.get());

        spShader->End(rc);
    }

    // ImGui
    RenderImGui();
}

void SceneTitle::RenderImGui()
{
#if _DEBUG
    ImGui::Begin("Parameter");
    if (ImGui::TreeNode("UVScroll"))
    {
        ImGui::SliderFloat2("Scroll Value", &uvScrollData.uvScrollValue.x, -10.0f, 10.0f);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Mask"))
    {
        ImGui::SliderFloat("Dissolve Threshold", &dissolveThreshold, 0.0f, 1.0f);
        ImGui::Checkbox("Dissolve Flg", &dissolveFlg);
        ImGui::TreePop();
    }
    ImGui::End();
#endif
}

// シーン遷移処理
void SceneTitle::Change(float elapsedTime)
{
    if (dissolveThreshold > 0.0f)
    {
        dissolveThreshold -= elapsedTime;
    }
    else
    {
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
    }
}