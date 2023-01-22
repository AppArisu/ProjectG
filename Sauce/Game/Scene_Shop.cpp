#include "Scene_Shop.h"
#include "Scene_Game.h"
#include "../Graphics/Graphic.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "../Input.h"

// 初期化
void SceneShop::Initialize()
{
    // フォントデータを宣言
    FontData* data = new FontData();
    // フォントデータを改変
    data->fontSize = 50;
    data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
    // DirectWrite用コンポーネントを作成
    Write = new DirectWrite(data);
    // 初期化
    Write->Initialize();

    // ショップ
    weapon = std::make_unique<ShopWeapon>();
    armor = std::make_unique<ShopArmor>();
    recovery = std::make_unique<ShopRecovery>();
    tool = std::make_unique<ShopTool>();
}

// 終了化
void SceneShop::Finalize()
{
    Write->Finalize();
}

// 更新処理
void SceneShop::Update(float elapsedTime)
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
void SceneShop::Render()
{
    Graphic& graphics = Graphic::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // 画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f, 1.0f, 1.0f, 1.0f };	// RGBA(0.0～1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    // ImGui
    {
        weapon->Render();
        armor->Render();
        recovery->Render();
        tool->Render();
    }

    // 文字描画
    Write->DrawString("Shop", DirectX::XMFLOAT2(90, 90), D2D1_DRAW_TEXT_OPTIONS_NONE);
}

// シーン遷移処理
void SceneShop::Change(float elapsedTime)
{
    SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
}
