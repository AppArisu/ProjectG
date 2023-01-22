#pragma once
#include "Scene.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Font.h"

#include "Player.h"
#include "Enemy.h"
#include "Enemy_Slime.h"
#include "Enemy_Zombie.h"
#include "Enemy_Robot.h"

enum State
{
    Town,
    Shop,
    Battle,
    Quit
};

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

    // �`�揈��
    void Render() override;

    // �`��
    void ImGuiRender();

    // �����`��
    void FontRender();

    // �V�[���J��
    void Change(float elapsedTime, Scene* nextScene);

    // 
    void StateSelect(State state01, State state02);

    // �����������Ă��邩
    bool IsSelect() const { return select; }

    // ���������ݒ�
    void SetSelect(bool setSelect) { select = setSelect; }

    // �G�l�~�[�Ăяo��
    void CallEnemy(Enemy* enemy);

private:
    int state = State::Town;

    bool select = false;

    std::unique_ptr<Sprite> sprite;

    // �v���C���[�A�G�l�~�[
    std::unique_ptr<Player> player = nullptr;
    EnemySlime* slime = nullptr;
    EnemyRobot* robot = nullptr;
    EnemyZombie* zombie = nullptr;
};