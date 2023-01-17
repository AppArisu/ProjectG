#include "Scene_Title.h"
#include "Scene_Game.h"
#include "../Graphics/Graphic.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "../Input.h"

// ������
void SceneTitle::Initialize()
{
    // �t�H���g�f�[�^��錾
    FontData* data = new FontData();
    // �t�H���g�f�[�^������
    data->fontSize = 50;
    data->fontWeight = DWRITE_FONT_WEIGHT_BOLD;
    // DirectWrite�p�R���|�[�l���g���쐬
    Write = new DirectWrite(data);
    // �t�H���g��ύX
    //Write->SetFont(data);
    // ������
    Write->Initialize();
}

// �I����
void SceneTitle::Finalize()
{
    Write->Finalize();
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
    }

    // �����`��
    Write->DrawString("Title", DirectX::XMFLOAT2(90, 90), D2D1_DRAW_TEXT_OPTIONS_NONE);
}

// �V�[���J�ڏ���
void SceneTitle::Change(float elapsedTime)
{
    SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
}
