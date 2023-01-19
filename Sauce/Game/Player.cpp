#include<imgui.h>
#include "Player.h"

// �R���X�g���N�^
Player::Player()
{
    TransitionIdleState();

    Player::SetHP(Pram().HP);
    Player::SetMaxHP(Pram().MaxHP);
    Player::SetAttack(Pram().Attack);
    Player::SetDefense(Pram().Defense);
    Player::SetSpeed(Pram().Speed);
}

// �X�V����
void Player::Update(float elapsedTime)
{
    // �X�e�[�g���Ƃ̏���
    switch (state)
    {
    case Player::State::Idle:// �ҋ@
        UpdateIdleState(elapsedTime);
        break;
    case Player::State::Move:// �ړ�
        UpdateMoveState(elapsedTime);
        break;
    case Player::State::Attack:// �U��
        UpdateAttackState(elapsedTime);
        break;
    case Player::State::Defense:// �h��
        UpdateDeathState(elapsedTime);
        break;
    case Player::State::Tool:// ����
        UpdateToolState(elapsedTime);
        break;
    case Player::State::Run:// ����
        UpdateRunState(elapsedTime);
        break;
    case Player::State::Damage:// �_���[�W
        UpdateDamageState(elapsedTime);
        break;
    case Player::State::Death:// ���S
        UpdateDeathState(elapsedTime);
        break;
    }
}

// �`�揈��
void Player::Render(float elapsedTime)
{
    RenderImGui();
}

// ImGui�`��
void Player::RenderImGui()
{
    ImGui::Begin("Player");
    if (ImGui::TreeNode("Parameter"))
    {
        int pram[] = 
        { 
            Player::GetHP(),
            Player::GetMaxHP(),
            Player::GetAttack(),
            Player::GetDefense(),
            Player::GetSpeed() 
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
void Player::OnDamaged()
{
    TransitionDamageState();
}

// ���S
void Player::OnDead()
{
    TransitionDeathState();
}

// �ҋ@
void Player::TransitionIdleState()
{
    state = State::Idle;
}
void Player::UpdateIdleState(float elapsedTime)
{
}

// �ړ�
void Player::TransitionMoveState()
{
    state = State::Move;
}
void Player::UpdateMoveState(float elapsedTime)
{
}

// �U��
void Player::TransitionAttackState()
{
    state = State::Attack;
}
void Player::UpdateAttackState(float elapsedTime)
{
}

// �h��
void Player::TransitionDefenseState()
{
    state = State::Defense;
}
void Player::UpdateDefenseState(float elapsedTime)
{
}

// ����
void Player::TransitionToolState()
{
    state = State::Tool;
}
void Player::UpdateToolState(float elapsedTime)
{
}

// ����
void Player::TransitionRunState()
{
    state = State::Run;
}
void Player::UpdateRunState(float elapsedTime)
{
}

// �_���[�W
void Player::TransitionDamageState()
{
    state = State::Damage;
}
void Player::UpdateDamageState(float elapsedTime)
{
}

// ���S
void Player::TransitionDeathState()
{
    state = State::Death;
}
void Player::UpdateDeathState(float elapsedTime)
{
}
