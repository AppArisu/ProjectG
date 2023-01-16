#include "Scene_Title.h"
#include "Scene_Game.h"
#include "Graphics/Graphic.h"
#include "Scene_Manager.h"
#include "Scene_Loading.h"
#include "Input.h"

// ������
void SceneTitle::Initialize()
{
}

// �I����
void SceneTitle::Finalize()
{
}

// �X�V����
void SceneTitle::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    // �Ȃɂ��{�^�����������烍�[�f�B���O�V�[���֐؂�ւ�
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

    // �G�t�F�N�g
    {
    }
}

// �`�揈��
void SceneTitle::Render()
{
    Graphic& graphics = Graphic::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();
    
    // ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
    FLOAT color[] = { 1.0f, 0.0f, 0.0f, 1.0f };	// RGBA(0.0�`1.0)
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

// �V�[���J�ڏ���
void SceneTitle::Change(float elapsedTime)
{
    SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
}
