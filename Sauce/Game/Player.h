#pragma once
#include "Character.h"

class Player :public Character
{
public:
    // �R���X�g���N�^
    Player();
    // �f�X�g���N�^
    ~Player() override {}

    // �C���X�^���X�擾
    static Player& Instance()
    {
        static Player instance;
        return instance;
    }

    // �X�V����
    void Update(float elapsedTime)override;
    // �`�揈��
    void Render(float elapsedTime)override;
    
    // ImGui
    void RenderImGui();

protected:
    // �_���[�W
    void OnDamaged() override;
    // ���S
    void OnDead() override;

private:
    // �ҋ@
    void TransitionIdleState();
    void UpdateIdleState(float elapsedTime);

    // �ړ�
    void TransitionMoveState();
    void UpdateMoveState(float elapsedTime);

    // �U��
    void TransitionAttackState();
    void UpdateAttackState(float elapsedTime);

    // �h��
    void TransitionDefenseState();
    void UpdateDefenseState(float elapsedTime);

    // ����
    void TransitionToolState();
    void UpdateToolState(float elapsedTime);

    // ����
    void TransitionRunState();
    void UpdateRunState(float elapsedTime);

    // �_���[�W
    void TransitionDamageState();
    void UpdateDamageState(float elapsedTime);

    // ���S
    void TransitionDeathState();
    void UpdateDeathState(float elapsedTime);

private:
    // �p�����[�^�[
    struct Pram
    {
        int HP = 100;
        int MaxHP = 100;
        int Attack = 30;
        int Defense = 20;
        int Speed = 10;
    };

    // �X�e�[�g
    enum class State
    {
        Idle,
        Move,
        Attack,
        Defense,
        Tool,
        Run,
        Damage,
        Death
    };

private:
    State state = State::Idle;

};