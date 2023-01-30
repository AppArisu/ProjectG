#include "Scene_Shop.h"
#include "Scene_Game.h"
#include "../Graphics/Graphic.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "../Input.h"

// 初期化
void SceneShop::Initialize()
{
    TransitionNoneState();
}

// 終了化
void SceneShop::Finalize()
{
}

// 更新処理
void SceneShop::Update(float elapsedTime)
{
    ProcessInput();

    if (GetGameState() == GameState::Play)
    {
        switch (state)
        {
        case SceneShop::State::None: // なし
            UpdateNoneState(elapsedTime);
            break;
        case SceneShop::State::Weapon: // 武器
            UpdateWeaponState(elapsedTime);
            break;
        case SceneShop::State::Armor: // 防具
            UpdateArmorState(elapsedTime);
            break;
        case SceneShop::State::Recovery: // 回復
            UpdateRecoveryState(elapsedTime);
            break;
        case SceneShop::State::Tool: // 道具
            UpdateToolState(elapsedTime);
            break;
        }
    }
}

void SceneShop::ProcessInput()
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    if (GetGameState() == Play)
    {
        if (gamePad.GetButtonDown() & GamePad::BTN_A ||
            GetKeyState(VK_RETURN) & 0x8000)
        {
            SceneChangeflg = true;
        }
        if (GetKeyState(VK_TAB) & 0x8000)
        {
            // ポーズに移行
            paused = std::make_unique<UIPaused>(this);
        }
    }

    if (GetGameState() == Paused)
    {
        if (GetKeyState(VK_BACK) & 0x8000)
        {
            // プレイに移行
            paused->Update();
        }
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

    if (GetGameState() == Paused)
    {
        paused->Render();
        RenderImGui();
    }
}

void SceneShop::RenderImGui()
{
#if _DEBUG

    switch (state)
    {
    case SceneShop::State::Weapon:
        weapon->Render();
        break;
    case SceneShop::State::Armor:
        armor->Render();
        break;
    case SceneShop::State::Recovery:
        recovery->Render();
        break;
    case SceneShop::State::Tool:
        tool->Render();
        break;
    }

    ImGui::Begin("State");
    if (ImGui::Button("None"))
    {
        TransitionNoneState();
    }
    if (ImGui::Button("Weapon"))
    {
        TransitionWeaponState();
    }
    if (ImGui::Button("Armor"))
    {
        TransitionArmorState();
    }
    if (ImGui::Button("Recovery"))
    {
        TransitionRecoveryState();
    }
    if (ImGui::Button("Tool"))
    {
        TransitionToolState();
    }
    ImGui::End();
#endif
}

// シーン遷移処理
void SceneShop::Change(float elapsedTime)
{
    SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
}

// なし
void SceneShop::TransitionNoneState()
{
    state = State::None;
}
void SceneShop::UpdateNoneState(float elapsedTime)
{
    if (SceneChangeflg)
    {
        Change(elapsedTime);
    }
}

// 武器
void SceneShop::TransitionWeaponState()
{
    state = State::Weapon;
    weapon = std::make_unique<ShopWeapon>();
}
void SceneShop::UpdateWeaponState(float elapsedTime)
{
    if (weapon->GetEndState())
    {
        weapon->Update();
    }
    else
    {
        TransitionNoneState();
    }
}

// 防具
void SceneShop::TransitionArmorState()
{
    state = State::Armor;
    armor = std::make_unique<ShopArmor>();
}
void SceneShop::UpdateArmorState(float elapsedTime)
{
    if (armor->GetEndState())
    {
        armor->Update();
    }
    else
    {
        TransitionNoneState();
    }
}

// 回復
void SceneShop::TransitionRecoveryState()
{
    state = State::Recovery;
    recovery = std::make_unique<ShopRecovery>();
}
void SceneShop::UpdateRecoveryState(float elapsedTime)
{
    if (recovery->GetEndState())
    {
        recovery->Update();
    }
    else
    {
        TransitionNoneState();
    }
}

// 道具
void SceneShop::TransitionToolState()
{
    state = State::Tool;
    tool = std::make_unique<ShopTool>();
}
void SceneShop::UpdateToolState(float elapsedTime)
{
    if (tool->GetEndState())
    {
        tool->Update();
    }
    else
    {
        TransitionNoneState();
    }
}
