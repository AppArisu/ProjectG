#include "Scene_Game.h"
#include "Scene_Title.h"
#include "Scene_Shop.h"
#include "Scene_Battle.h"
#include "../Graphics/Graphic.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "../Input.h"

// 初期化
void SceneGame::Initialize()
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
void SceneGame::Finalize()
{
    Write->Finalize();
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    switch (state)
    {
    case State::Town:
        break;
    case State::Shop:
        Change(elapsedTime, new SceneShop);
        break;
    case State::Battle:
        Change(elapsedTime, new SceneBattle);
        break;
    case State::Quit:
        break;
    }

    StateSelect(Town, Quit);
    
}

// 描画処理
void SceneGame::Render()
{
    Graphic& graphics = Graphic::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // 画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f, 1.0f, 0.0f, 1.0f };	// RGBA(0.0～1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    {
        ImGui::Begin("SelectNum");
        ImGui::InputInt("NUm", &state);
        ImGui::End();
    }

    SpriteRender();

    FontRender();
}

// 画像描画
void SceneGame::SpriteRender()
{
}

// 文字描画
void SceneGame::FontRender()
{
    // 文字描画
    Write->DrawString("Game", DirectX::XMFLOAT2(90, 90), D2D1_DRAW_TEXT_OPTIONS_NONE);

    switch (state)
    {
    case State::Town:
        Write->DrawString("Town Now!", DirectX::XMFLOAT2(300, 300), D2D1_DRAW_TEXT_OPTIONS_NONE);
        break;
    case State::Shop:
        Write->DrawString("Go Shop!", DirectX::XMFLOAT2(300, 300), D2D1_DRAW_TEXT_OPTIONS_NONE);
        break;
    case State::Battle:
        Write->DrawString("Go Battle!", DirectX::XMFLOAT2(300, 300), D2D1_DRAW_TEXT_OPTIONS_NONE);
        break;
    case State::Quit:
        Write->DrawString("Quit!", DirectX::XMFLOAT2(300, 300), D2D1_DRAW_TEXT_OPTIONS_NONE);
        break;
    }
}

void SceneGame::StateSelect(State state01, State state02)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    if (state < state01)
    {
        state = state02;
    }
    if (state > state02)
    {
        state = state01;
    }

    if (!IsSelect())
    {
        if (gamePad.GetButtonDown() & GamePad::BTN_UP)
        {
            ++state;
            SetSelect(true);
        }
        if (gamePad.GetButtonDown() & GamePad::BTN_DOWN)
        {
            --state;
            SetSelect(true);
        }
        SetSelect(false);
    }
}

// シーン遷移処理
void SceneGame::Change(float elapsedTime, Scene* nextScene)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    if (gamePad.GetButtonDown() & GamePad::BTN_LEFT)
    {
        SceneManager::Instance().ChangeScene(new SceneLoading(nextScene));
    }
}