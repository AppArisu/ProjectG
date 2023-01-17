#pragma once
#include "Scene.h"
#include"../Graphics/Sprite.h"
#include"../Graphics/Texture.h"
#include"../Graphics/Font.h"

// �^�C�g���V�[��
class SceneTitle :public Scene
{
public:
    SceneTitle() {}
    ~SceneTitle()override {}

    // ������
    void Initialize() override;

    // �I����
    void Finalize() override;

    // �X�V����
    void Update(float elapsedTime) override;

    // �`�揈��
    void Render() override;

    // �V�[���J��
    void Change(float elapsedTime);

    void ImGuiRender();

private:
    // �t�H���g
    DirectWrite* Write = nullptr;

    std::unique_ptr<Sprite> sprite;
    std::unique_ptr<Texture> texture;

    // UV�X�N���[���f�[�^
    UVScrollData uvScrollData;

    // �}�X�N�摜
    std::unique_ptr<Texture> maskTexture;
    float dissolveThreshold = 0.0f;
    bool dissolveFlg = false;

};