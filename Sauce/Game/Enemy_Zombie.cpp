#include<imgui.h>
#include"Enemy_Zombie.h"

// �R���X�g���N�^
EnemyZombie::EnemyZombie()
{
    TransitionIdleState();

    EnemyZombie::SetHP(Pram().HP);
    EnemyZombie::SetMaxHP(Pram().MaxHP);
    EnemyZombie::SetAttack(Pram().Attack);
    EnemyZombie::SetDefense(Pram().Defense);
    EnemyZombie::SetSpeed(Pram().Speed);
}

// �X�V����
void EnemyZombie::Update(float elapsedTime)
{
    // �X�e�[�g���Ƃ̏���
    switch (state)
    {
    case EnemyZombie::State::Idle:// �ҋ@
        UpdateIdleState(elapsedTime);
        break;
    case EnemyZombie::State::Attack:// �U��
        UpdateAttackState(elapsedTime);
        break;
    case EnemyZombie::State::Defense:// �h��
        UpdateDeathState(elapsedTime);
        break;
    case EnemyZombie::State::Run:// ����
        UpdateRunState(elapsedTime);
        break;
    case EnemyZombie::State::Damage:// �_���[�W
        UpdateDamageState(elapsedTime);
        break;
    case EnemyZombie::State::Death:// ���S
        UpdateDeathState(elapsedTime);
        break;
    }
}

// �`�揈��
void EnemyZombie::Render(float elapsedTime)
{
    RenderImGui();
}

// ImGui
void EnemyZombie::RenderImGui()
{
    ImGui::Begin("Robot");
    if (ImGui::TreeNode("Parameter"))
    {
        int pram[] =
        {
            EnemyZombie::GetHP(),
            EnemyZombie::GetMaxHP(),
            EnemyZombie::GetAttack(),
            EnemyZombie::GetDefense(),
            EnemyZombie::GetSpeed()
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
void EnemyZombie::OnDamaged()
{
    TransitionDamageState();
}

// ���S
void EnemyZombie::OnDead()
{
    TransitionDeathState();
}

// �ҋ@
void EnemyZombie::TransitionIdleState()
{
    state = State::Idle;
}
void EnemyZombie::UpdateIdleState(float elapsedTime)
{
}

// �U��
void EnemyZombie::TransitionAttackState()
{
    state = State::Attack;
}
void EnemyZombie::UpdateAttackState(float elapsedTime)
{
}

// �h��
void EnemyZombie::TransitionDefenseState()
{
    state = State::Defense;
}
void EnemyZombie::UpdateDefenseState(float elapsedTime)
{
}

// ����
void EnemyZombie::TransitionRunState()
{
    state = State::Run;
}
void EnemyZombie::UpdateRunState(float elapsedTime)
{
}

// �_���[�W
void EnemyZombie::TransitionDamageState()
{
    state = State::Damage;
}
void EnemyZombie::UpdateDamageState(float elapsedTime)
{
}

// ���S
void EnemyZombie::TransitionDeathState()
{
    state = State::Death;
}
void EnemyZombie::UpdateDeathState(float elapsedTime)
{
}
