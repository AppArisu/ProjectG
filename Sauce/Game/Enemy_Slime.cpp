#include<imgui.h>
#include"Enemy_Slime.h"

// �R���X�g���N�^
EnemySlime::EnemySlime()
{
    TransitionIdleState();

    EnemySlime::SetHP(Pram().HP);
    EnemySlime::SetMaxHP(Pram().MaxHP);
    EnemySlime::SetAttack(Pram().Attack);
    EnemySlime::SetDefense(Pram().Defense);
    EnemySlime::SetSpeed(Pram().Speed);
}

// �X�V����
void EnemySlime::Update(float elapsedTime)
{
    // �X�e�[�g���Ƃ̏���
    switch (state)
    {
    case EnemySlime::State::Idle:// �ҋ@
        UpdateIdleState(elapsedTime);
        break;
    case EnemySlime::State::Attack:// �U��
        UpdateAttackState(elapsedTime);
        break;
    case EnemySlime::State::Defense:// �h��
        UpdateDeathState(elapsedTime);
        break;
    case EnemySlime::State::Run:// ����
        UpdateRunState(elapsedTime);
        break;
    case EnemySlime::State::Damage:// �_���[�W
        UpdateDamageState(elapsedTime);
        break;
    case EnemySlime::State::Death:// ���S
        UpdateDeathState(elapsedTime);
        break;
    }
}

// �`�揈��
void EnemySlime::Render(float elapsedTime)
{
    RenderImGui();
}

// ImGui
void EnemySlime::RenderImGui()
{
    ImGui::Begin("Slime");
    if (ImGui::TreeNode("Parameter"))
    {
        int pram[] =
        {
            EnemySlime::GetHP(),
            EnemySlime::GetMaxHP(),
            EnemySlime::GetAttack(),
            EnemySlime::GetDefense(),
            EnemySlime::GetSpeed()
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
void EnemySlime::OnDamaged()
{
    TransitionDamageState();
}

// ���S
void EnemySlime::OnDead()
{
    TransitionDeathState();
}

// �ҋ@
void EnemySlime::TransitionIdleState()
{
    state = State::Idle;
}
void EnemySlime::UpdateIdleState(float elapsedTime)
{
}

// �U��
void EnemySlime::TransitionAttackState()
{
    state = State::Attack;
}
void EnemySlime::UpdateAttackState(float elapsedTime)
{
}

// �h��
void EnemySlime::TransitionDefenseState()
{
    state = State::Defense;
}
void EnemySlime::UpdateDefenseState(float elapsedTime)
{
}

// ����
void EnemySlime::TransitionRunState()
{
    state = State::Run;
}
void EnemySlime::UpdateRunState(float elapsedTime)
{
}

// �_���[�W
void EnemySlime::TransitionDamageState()
{
    state = State::Damage;
}
void EnemySlime::UpdateDamageState(float elapsedTime)
{
}

// ���S
void EnemySlime::TransitionDeathState()
{
    state = State::Death;
}
void EnemySlime::UpdateDeathState(float elapsedTime)
{
}
