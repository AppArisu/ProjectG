#pragma once
#include "Scene.h"

// ���̃V�[��
class SceneMeta :public Scene
{
public:
    SceneMeta() {}
    ~SceneMeta()override {}

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
};