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
    // ������
    Write->Initialize();

    // �e�N�X�`���ǂݍ���
    texture = std::make_unique<Texture>("Data/Sprite/Title.png");
    // �}�X�N�e�N�X�`���ǂݍ���
    maskTexture = std::make_unique<Texture>("Data/Sprite/Texture/dissolve01.png");
    dissolveThreshold = 1.0f;
    dissolveFlg = false;

    // �X�v���C�g
    sprite = std::make_unique<Sprite>();
    sprite->SetShaderResourceView(texture->GetShaderResourceView(), texture->GetWidth(), texture->GetHeight());
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
        dissolveFlg = true;
    }
    if (dissolveFlg)
    {
        Change(elapsedTime);
    }

    // �G�t�F�N�g
    {
        // �f�B�]�u��
        sprite->Update(0.0f, 0.0f,
            Graphic::Instance().GetScreenWidth(), Graphic::Instance().GetScreenHeight(),
            0.0f, 0.0f,
            static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()),
            0.0f,
            1.0f, 1.0f, 1.0f, 1.0f);
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

    // �X�v���C�g
    {
        RenderContext rc;
        rc.deviceContext = dc;

        SpriteShader* spShader = graphics.GetSprite(static_cast<int>(SpriteTypeID::Mask));

        spShader->Begin(rc);

        rc.uvScrollData = uvScrollData;
        rc.maskData.maskTexture = maskTexture->GetShaderResourceView().Get();
        rc.maskData.dissolveThreshold = dissolveThreshold;

        spShader->Draw(rc, sprite.get());

        spShader->End(rc);
    }

    // ImGui
    ImGuiRender();
}

void SceneTitle::ImGuiRender()
{
    ImGui::Begin("Parameter");
    if (ImGui::TreeNode("UVScroll"))
    {
        ImGui::SliderFloat2("Scroll Value", &uvScrollData.uvScrollValue.x, -10.0f, 10.0f);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Mask"))
    {
        ImGui::SliderFloat("Dissolve Threshold", &dissolveThreshold, 0.0f, 1.0f);
        ImGui::Checkbox("Dissolve Flg", &dissolveFlg);
        ImGui::TreePop();
    }
    ImGui::End();
}

// �V�[���J�ڏ���
void SceneTitle::Change(float elapsedTime)
{
    if (dissolveThreshold > 0.0f)
    {
        dissolveThreshold -= elapsedTime;
    }
    else
    {
        SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
    }
}