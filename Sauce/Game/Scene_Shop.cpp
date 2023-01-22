#include "Scene_Shop.h"
#include "Scene_Game.h"
#include "../Graphics/Graphic.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "../Input.h"

// ������
void SceneShop::Initialize()
{
    // �V���b�v
    weapon = std::make_unique<ShopWeapon>();
    armor = std::make_unique<ShopArmor>();
    recovery = std::make_unique<ShopRecovery>();
    tool = std::make_unique<ShopTool>();
}

// �I����
void SceneShop::Finalize()
{
}

// �X�V����
void SceneShop::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    if (gamePad.GetButtonDown() & GamePad::BTN_A)
    {
        Change(elapsedTime);
    }

    // �G�t�F�N�g
    {
    }
}

// �`�揈��
void SceneShop::Render()
{
    Graphic& graphics = Graphic::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
    FLOAT color[] = { 0.0f, 1.0f, 1.0f, 1.0f };	// RGBA(0.0�`1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    RenderImGui();
}

void SceneShop::RenderImGui()
{
#if _DEBUG
    weapon->Render();
    armor->Render();
    recovery->Render();
    tool->Render();
#endif
}

// �V�[���J�ڏ���
void SceneShop::Change(float elapsedTime)
{
    SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
}
