#include "Scene_Battle.h"
#include "Scene_Game.h"
#include "../Graphics/Graphic.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "../Input.h"

// 初期化
void SceneBattle::Initialize()
{
    // フォントデータを宣言
    FontData* data = new FontData();
    // フォントデータを改変
    data->fontSize = 50;
    data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
    // DirectWrite用コンポーネントを作成
    Write = new DirectWrite(data);
    // フォントを変更
    //Write->SetFont(data);
    // 初期化
    Write->Initialize();
}

// 終了化
void SceneBattle::Finalize()
{
    Write->Finalize();
}

// 更新処理
void SceneBattle::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    if (gamePad.GetButtonDown() & GamePad::BTN_A)
    {
        Change(elapsedTime);
    }

    // エフェクト
    {
    }
}

// 描画処理
void SceneBattle::Render()
{
    Graphic& graphics = Graphic::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // 画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f, 0.0f, 1.0f, 1.0f };	// RGBA(0.0～1.0)
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

    // 文字描画
    Write->DrawString("Battle", DirectX::XMFLOAT2(90, 90), D2D1_DRAW_TEXT_OPTIONS_NONE);
}

// シーン遷移処理
void SceneBattle::Change(float elapsedTime)
{
    SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
}
