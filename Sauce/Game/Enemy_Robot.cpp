#include<imgui.h>
#include"Enemy_Robot.h"

// �R���X�g���N�^
EnemyRobot::EnemyRobot()
{
    TransitionIdleState();

    EnemyRobot::SetHP(Pram().HP);
    EnemyRobot::SetMaxHP(Pram().MaxHP);
    EnemyRobot::SetAttack(Pram().Attack);
    EnemyRobot::SetDefense(Pram().Defense);
    EnemyRobot::SetSpeed(Pram().Speed);
}

// �X�V����
void EnemyRobot::Update(float elapsedTime)
{
    // �X�e�[�g���Ƃ̏���
    switch (state)
    {
    case EnemyRobot::State::Idle:// �ҋ@
        UpdateIdleState(elapsedTime);
        break;
    case EnemyRobot::State::Attack:// �U��
        UpdateAttackState(elapsedTime);
        break;
    case EnemyRobot::State::Defense:// �h��
        UpdateDeathState(elapsedTime);
        break;
    case EnemyRobot::State::Run:// ����
        UpdateRunState(elapsedTime);
        break;
    case EnemyRobot::State::Damage:// �_���[�W
        UpdateDamageState(elapsedTime);
        break;
    case EnemyRobot::State::Death:// ���S
        UpdateDeathState(elapsedTime);
        break;
    }
}

// �`�揈��
void EnemyRobot::Render(float elapsedTime)
{
    RenderImGui();
}

// ImGui
void EnemyRobot::RenderImGui()
{
    ImGui::Begin("Robot");
    if (ImGui::TreeNode("Parameter"))
    {
        int pram[] =
        {
            EnemyRobot::GetHP(),
            EnemyRobot::GetMaxHP(),
            EnemyRobot::GetAttack(),
            EnemyRobot::GetDefense(),
            EnemyRobot::GetSpeed()
        };

        ImGui::InputInt("HP", &pram[0]);
        ImGui::InputInt("MaxHP", &pram[1]);
        ImGui::InputInt("Attack", &pram[2]);
        ImGui::InputInt("Defense", &pram[3]);
        ImGui::InputInt("Speed", &pram[4]);
        ImGui::TreePop();
    }
    ImGui::End();
}

// �_���[�W
void EnemyRobot::OnDamaged()
{
    TransitionDamageState();
}

// ���S
void EnemyRobot::OnDead()
{
    TransitionDeathState();
}

// �ҋ@
void EnemyRobot::TransitionIdleState()
{
    state = State::Idle;
}
void EnemyRobot::UpdateIdleState(float elapsedTime)
{
}

// �U��
void EnemyRobot::TransitionAttackState()
{
    state = State::Attack;
}
void EnemyRobot::UpdateAttackState(float elapsedTime)
{
}

// �h��
void EnemyRobot::TransitionDefenseState()
{
    state = State::Defense;
}
void EnemyRobot::UpdateDefenseState(float elapsedTime)
{
}

// ����
void EnemyRobot::TransitionRunState()
{
    state = State::Run;
}
void EnemyRobot::UpdateRunState(float elapsedTime)
{
}

// �_���[�W
void EnemyRobot::TransitionDamageState()
{
    state = State::Damage;
}
void EnemyRobot::UpdateDamageState(float elapsedTime)
{
}

// ���S
void EnemyRobot::TransitionDeathState()
{
    state = State::Death;
}
void EnemyRobot::UpdateDeathState(float elapsedTime)
{
}
