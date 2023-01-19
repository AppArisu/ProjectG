#include<imgui.h>
#include"Enemy_Robot.h"

// コンストラクタ
EnemyRobot::EnemyRobot()
{
    TransitionIdleState();

    EnemyRobot::SetHP(Pram().HP);
    EnemyRobot::SetMaxHP(Pram().MaxHP);
    EnemyRobot::SetAttack(Pram().Attack);
    EnemyRobot::SetDefense(Pram().Defense);
    EnemyRobot::SetSpeed(Pram().Speed);
}

// 更新処理
void EnemyRobot::Update(float elapsedTime)
{
    // ステートごとの処理
    switch (state)
    {
    case EnemyRobot::State::Idle:// 待機
        UpdateIdleState(elapsedTime);
        break;
    case EnemyRobot::State::Attack:// 攻撃
        UpdateAttackState(elapsedTime);
        break;
    case EnemyRobot::State::Defense:// 防御
        UpdateDeathState(elapsedTime);
        break;
    case EnemyRobot::State::Run:// 逃走
        UpdateRunState(elapsedTime);
        break;
    case EnemyRobot::State::Damage:// ダメージ
        UpdateDamageState(elapsedTime);
        break;
    case EnemyRobot::State::Death:// 死亡
        UpdateDeathState(elapsedTime);
        break;
    }
}

// 描画処理
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

// ダメージ
void EnemyRobot::OnDamaged()
{
    TransitionDamageState();
}

// 死亡
void EnemyRobot::OnDead()
{
    TransitionDeathState();
}

// 待機
void EnemyRobot::TransitionIdleState()
{
    state = State::Idle;
}
void EnemyRobot::UpdateIdleState(float elapsedTime)
{
}

// 攻撃
void EnemyRobot::TransitionAttackState()
{
    state = State::Attack;
}
void EnemyRobot::UpdateAttackState(float elapsedTime)
{
}

// 防御
void EnemyRobot::TransitionDefenseState()
{
    state = State::Defense;
}
void EnemyRobot::UpdateDefenseState(float elapsedTime)
{
}

// 逃走
void EnemyRobot::TransitionRunState()
{
    state = State::Run;
}
void EnemyRobot::UpdateRunState(float elapsedTime)
{
}

// ダメージ
void EnemyRobot::TransitionDamageState()
{
    state = State::Damage;
}
void EnemyRobot::UpdateDamageState(float elapsedTime)
{
}

// 死亡
void EnemyRobot::TransitionDeathState()
{
    state = State::Death;
}
void EnemyRobot::UpdateDeathState(float elapsedTime)
{
}
