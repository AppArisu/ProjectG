#pragma once
#include "Scene.h"
#include "../Graphics/Font.h"

// �V���b�v�V�[��
class SceneShop :public Scene
{
public:
    SceneShop() {}
    ~SceneShop()override {}

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

private:
    // �t�H���g
    DirectWrite* Write = nullptr;
};