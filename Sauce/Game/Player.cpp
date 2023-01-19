#include<imgui.h>
#include "Player.h"

// コンストラクタ
Player::Player()
{
    TransitionIdleState();

    Player::SetHP(Pram().HP);
    Player::SetMaxHP(Pram().MaxHP);
    Player::SetAttack(Pram().Attack);
    Player::SetDefense(Pram().Defense);
    Player::SetSpeed(Pram().Speed);
}

// 更新処理
void Player::Update(float elapsedTime)
{
    // ステートごとの処理
    switch (state)
    {
    case Player::State::Idle:// 待機
        UpdateIdleState(elapsedTime);
        break;
    case Player::State::Move:// 移動
        UpdateMoveState(elapsedTime);
        break;
    case Player::State::Attack:// 攻撃
        UpdateAttackState(elapsedTime);
        break;
    case Player::State::Defense:// 防御
        UpdateDeathState(elapsedTime);
        break;
    case Player::State::Tool:// 道具
        UpdateToolState(elapsedTime);
        break;
    case Player::State::Run:// 逃走
        UpdateRunState(elapsedTime);
        break;
    case Player::State::Damage:// ダメージ
        UpdateDamageState(elapsedTime);
        break;
    case Player::State::Death:// 死亡
        UpdateDeathState(elapsedTime);
        break;
    }
}

// 描画処理
void Player::Render(float elapsedTime)
{
    RenderImGui();
}

// ImGui描画
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

// ダメージ
void Player::OnDamaged()
{
    TransitionDamageState();
}

// 死亡
void Player::OnDead()
{
    TransitionDeathState();
}

// 待機
void Player::TransitionIdleState()
{
    state = State::Idle;
}
void Player::UpdateIdleState(float elapsedTime)
{
}

// 移動
void Player::TransitionMoveState()
{
    state = State::Move;
}
void Player::UpdateMoveState(float elapsedTime)
{
}

// 攻撃
void Player::TransitionAttackState()
{
    state = State::Attack;
}
void Player::UpdateAttackState(float elapsedTime)
{
}

// 防御
void Player::TransitionDefenseState()
{
    state = State::Defense;
}
void Player::UpdateDefenseState(float elapsedTime)
{
}

// 道具
void Player::TransitionToolState()
{
    state = State::Tool;
}
void Player::UpdateToolState(float elapsedTime)
{
}

// 逃走
void Player::TransitionRunState()
{
    state = State::Run;
}
void Player::UpdateRunState(float elapsedTime)
{
}

// ダメージ
void Player::TransitionDamageState()
{
    state = State::Damage;
}
void Player::UpdateDamageState(float elapsedTime)
{
}

// 死亡
void Player::TransitionDeathState()
{
    state = State::Death;
}
void Player::UpdateDeathState(float elapsedTime)
{
}
