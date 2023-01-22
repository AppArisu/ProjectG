#include "Scene_Game.h"
#include "Scene_Title.h"
#include "Scene_Shop.h"
#include "Scene_Battle.h"
#include "../Graphics/Graphic.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "../Input.h"
#include "EnemyManager.h"

// 初期化
void SceneGame::Initialize()
{
    // スプライト
    sprite = std::make_unique<Sprite>("Data/Sprite/Town.png");

    // プレイヤー
    player = std::make_unique<Player>();

    // エネミー
    CallEnemy(slime);
    CallEnemy(robot);
    CallEnemy(zombie);

}

// 終了化
void SceneGame::Finalize()
{
    EnemyManager::Instance().Clear();
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

    const GamePadButton anyButton =
        GamePad::BTN_A
        | GamePad::BTN_B
        | GamePad::BTN_X
        | GamePad::BTN_Y
        ;
    if (gamePad.GetButtonDown() & anyButton)
    {
        state = State::Shop;
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

    ImGuiRender();

    //FontRender();
}

// 画像描画
void SceneGame::ImGuiRender()
{
    player->Render(1);

    slime->Render(1);
    robot->Render(2);
    zombie->Render(3);
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

// エネミー呼び出し
void SceneGame::CallEnemy(Enemy* enemy)
{
    EnemyManager& enemyManager = EnemyManager::Instance();

    if (enemy == slime)
    {
        slime = new EnemySlime;
    }
    if (enemy == robot)
    {
        robot = new EnemyRobot;
    }
    if (enemy == zombie)
    {
        zombie = new EnemyZombie;
    }
    enemyManager.Register(enemy);
}

// シーン遷移処理
void SceneGame::Change(float elapsedTime, Scene* nextScene)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    SceneManager::Instance().ChangeScene(new SceneLoading(nextScene));
}