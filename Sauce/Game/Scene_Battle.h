#pragma once
#include "Scene.h"
#include "../Graphics/Font.h"

// �퓬�V�[��
class SceneBattle :public Scene
{
public:
    SceneBattle() {}
    ~SceneBattle()override {}

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