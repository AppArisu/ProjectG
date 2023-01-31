#include "Scene_Game.h"
#include "Scene_Title.h"
#include "Scene_Shop.h"
#include "Scene_Battle.h"
#include "../Graphics/Graphic.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "../Input.h"

// ������
void SceneGame::Initialize()
{
    // �v���C���[
    player = std::make_unique<Player>();

    // �X�v���C�g
    sprite = std::make_unique<Sprite>("Data/Sprite/Town.png");
}

// �I����
void SceneGame::Finalize()
{
}

// �X�V����
void SceneGame::Update(float elapsedTime)
{
    ProcessInput();

    if (GetGameState() == GameState::Play)
    {
        switch (state)
        {
        case SceneGame::Town:
            UpdateTwonState(elapsedTime);
            break;
        case SceneGame::Shop:
            UpdateShopState(elapsedTime);
            break;
        case SceneGame::Battle:
            UpdateBattleState(elapsedTime);
            break;
        case SceneGame::End:
            UpdateEndState(elapsedTime);
            break;
        }
    }
}

void SceneGame::ProcessInput()
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
            // �|�[�Y�Ɉڍs
            paused = std::make_unique<UIPaused>(this);
        }
    }

    if (GetGameState() == Paused)
    {
        if (GetKeyState(VK_BACK) & 0x8000)
        {
            // �v���C�Ɉڍs
            paused->Update();
        }
    }
}

// �`�揈��
void SceneGame::Render()
{
    Graphic& graphics = Graphic::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
    FLOAT color[] = { 0.0f, 1.0f, 0.0f, 1.0f };	// RGBA(0.0�`1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    // �X�v���C�g
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

    if (GetGameState() == Paused)
    {
        paused->Render();
        RenderImGui();
    }
}

void SceneGame::RenderImGui()
{
#if _DEBUG
    player->Render(1);
#endif
}

// �����`��
void SceneGame::FontRender()
{
}

// �^�E��
void SceneGame::TransitionTwonState()
{
    state = Town;
}
void SceneGame::UpdateTwonState(float elapsedTime)
{
    if (SceneChangeflg)
    {
        TransitionShopState();
    }
}

// �V���b�v
void SceneGame::TransitionShopState()
{
    state = Shop;
}
void SceneGame::UpdateShopState(float elapsedTime)
{
    Change(new SceneShop);
}

// �o�g��
void SceneGame::TransitionBattleState()
{
    state = Battle;
}
void SceneGame::UpdateBattleState(float elapsedTime)
{
    Change(new SceneBattle);
}

// �I��
void SceneGame::TransitionEndState()
{
    state = End;
}
void SceneGame::UpdateEndState(float elapsedTime)
{
}

// �V�[���J�ڏ���
void SceneGame::Change(Scene* nextScene)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    SceneManager::Instance().ChangeScene(new SceneLoading(nextScene));
}