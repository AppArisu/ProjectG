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
    // �v���C���[
    std::unique_ptr<Player> player = nullptr;
    // �G�l�~�[
    EnemySlime* slime = nullptr;
    EnemyRobot* robot = nullptr;
    EnemyZombie* zombie = nullptr;
    // UI
    std::unique_ptr<UIPaused> paused = nullptr;

    bool SceneChangeflg = false;
};