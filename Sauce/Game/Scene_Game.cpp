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
    // プレイヤー
    player = std::make_unique<Player>();

    // スプライト
    sprite = std::make_unique<Sprite>("Data/Sprite/Town.png");
}

// 終了化
void SceneGame::Finalize()
{
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
    ProcessInput();

    if (GetState() == GameState::Play)
    {

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
        case State::End:
            break;
        }

        StateSelect(Town, End);

        if (SceneChangeflg)
        {
            state = State::Shop;
        }
    }
}

void SceneGame::ProcessInput()
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    if (GetState() == Play)
    {
        if (gamePad.GetButtonDown() & GamePad::BTN_A ||
            GetKeyState(VK_RETURN) & 0x8000)
        {
            SceneChangeflg = true;
        }
        if (GetKeyState(VK_TAB) & 0x8000)
        {
            // ポーズに移行
            SetState(Paused);
        }
    }

    if (GetState() == Paused)
    {
        if (GetKeyState(VK_BACK) & 0x8000)
        {
            // プレイに移行
            SetState(Play);
        }
    }
}

// 描画処理
void SceneGame::Render()
{
    Graphic& graphics = Graphic::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // 画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f, 1.0f, 0.0f, 1.0f };	// RGBA(0.0〜1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    // スプライト
    {
        float screenWidth = static_cast<float>(graphics.GetScreenWidth());
        float screenHeight = static_cast<float>(graphics.GetScreenHeight());
        float textureWidth = static_cast<float>(sprite->GetTextureWidth());
        float textureHeight = static_cast<float>(sprite->GetTextureHeight());

        sprite->Render(dc,0.0f, 0.0f,
            screenWidth, screenHeight,
            0.0f, 0.0f,
            textureWidth, textureHeight,
            0.0f,
            1.0f, 1.0f, 1.0f, 1.0f);
    }

    if (GetState() == Play)
    {
        RenderImGui();
    }

    //FontRender();
}

void SceneGame::RenderImGui()
{
#if _DEBUG
    player->Render(1);
#endif
}

// 文字描画
void SceneGame::FontRender()
{
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

    SceneManager::Instance().ChangeScene(new SceneLoading(nextScene));
}