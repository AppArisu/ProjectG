#pragma once
#include<memory>
#include "Scene.h"
#include "../Graphics/Sprite.h"

#include "Player.h"
#include "UI_Paused.h"

// �^�C�g���V�[��
class SceneGame :public Scene
{
public:
    SceneGame() {}
    ~SceneGame()override {}

    // ������
    void Initialize() override;

    // �I����
    void Finalize() override;

    // �X�V����
    void Update(float elapsedTime) override;
    void ProcessInput() override;

    // �`�揈��
    void Render() override;

    // �`��
    void RenderImGui()override;

    // �����`��
    void FontRender();

    // �V�[���J��
    void Change(Scene* nextScene);

private:
    // �^�E��
    void TransitionTwonState();
    void UpdateTwonState(float elapsedTime);

    // �V���b�v
    void TransitionShopState();
    void UpdateShopState(float elapsedTime);

    // �o�g��
    void TransitionBattleState();
    void UpdateBattleState(float elapsedTime);

    // �I��
    void TransitionEndState();
    void UpdateEndState(float elapsedTime);

    enum GState
    {
        Town,
        Shop,
        Battle,
        End
    };

private:
    GState state = GState::Town;

    bool SceneChangeflg = false;

    std::unique_ptr<Sprite> sprite;

    // �v���C���[
    std::unique_ptr<Player> player = nullptr;

    // UI
    std::unique_ptr<UIPaused> paused = nullptr;
};