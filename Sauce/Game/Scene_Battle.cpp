#include "Scene_Battle.h"
#include "Scene_Game.h"
#include "../Graphics/Graphic.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "../Input.h"
#include "EnemyManager.h"

// 初期化
void SceneBattle::Initialize()
{
    // プレイヤー
    player = std::make_unique<Player>();

    // エネミー
    CallEnemy(slime);
    CallEnemy(robot);
    CallEnemy(zombie);

}

// 終了化
void SceneBattle::Finalize()
{
    EnemyManager::Instance().Clear();
}

// 更新処理
void SceneBattle::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    if (gamePad.GetButtonDown() & GamePad::BTN_A)
    {
        Change(elapsedTime);
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

    RenderImGui();
}

void SceneBattle::RenderImGui()
{
#if _DEBUG
    player->Render(1);

    slime->Render(1);
    robot->Render(2);
    zombie->Render(3);
#endif
}

// エネミー呼び出し
void SceneBattle::CallEnemy(Enemy* enemy)
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
void SceneBattle::Change(float elapsedTime)
{
    SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
}
