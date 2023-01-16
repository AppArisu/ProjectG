#include "Scene_Title.h"
#include "Scene_Game.h"
#include "Graphics/Graphic.h"
#include "Scene_Manager.h"
#include "Scene_Loading.h"
#include "Input.h"

// 初期化
void SceneTitle::Initialize()
{
}

// 終了化
void SceneTitle::Finalize()
{
}

// 更新処理
void SceneTitle::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    // なにかボタンを押したらローディングシーンへ切り替え
    const GamePadButton anyButton =
        GamePad::BTN_A
        | GamePad::BTN_B
        | GamePad::BTN_X
        | GamePad::BTN_Y
        ;
    if (gamePad.GetButtonDown() & anyButton)
    {
        Change(elapsedTime);
    }

    // エフェクト
    {
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
    FLOAT color[] = { 1.0f, 0.0f, 0.0f, 1.0f };	// RGBA(0.0～1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    // ImGui
    {
        ImGui::Separator();
        if (ImGui::TreeNode("UVScroll"))
        {
            ImGui::TreePop();
        }
        ImGui::Separator();
    }
}

// シーン遷移処理
void SceneTitle::Change(float elapsedTime)
{
    SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
}
