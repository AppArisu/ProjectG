#pragma once
#include<memory>
#include "Scene.h"

#include "Player.h"
#include "Enemy.h"
#include "Enemy_Slime.h"
#include "Enemy_Zombie.h"
#include "Enemy_Robot.h"
#include "UI_Paused.h"

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
    void ProcessInput() override;

    // �`�揈��
    void Render() override;
    void RenderImGui() override;

    // �V�[���J��
    void Change(float elapsedTime);

    // �G�l�~�[�Ăяo��
    void CallEnemy(Enemy* enemy);

private:
    // �ҋ@
    void TransitionIdleState();
    void UpdateIdleState(float elapsedTime);

    // �U��
    void TransitionAttackState();
    void UpdateAttackState(float elapsedTime);

    // �h��
    void TransitionDefenseState();
    void UpdateDefenseState(float elapsedTime);

    // ����
    void TransitionToolsState();
    void UpdateToolsState(float elapsedTime);

    // ������
    void TransitionRunState();
    void UpdateRunState(float elapsedTime);

    // �I��
    void TransitionEndState();
    void UpdateEndState(float elapsedTime);

    enum BState
    {
        Idle,
        Attack,
        Defense,
        Tools,
        Run,
        End
    };

private:
    // �v���C���[
    std::unique_ptr<Player> player = nullptr;
    // �G�l�~�[
    EnemySlime* slime = nullptr;
    EnemyRobot* robot = nullptr;
    EnemyZombie* zombie = nullptr;
    // UI
    std::unique_ptr<UIPaused> paused = nullptr;

    bool SceneChangeflg = false;

    BState state = BState::Idle;
};