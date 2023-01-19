#include<imgui.h>
#include"Enemy_Zombie.h"

// コンストラクタ
EnemyZombie::EnemyZombie()
{
    TransitionIdleState();

    EnemyZombie::SetHP(Pram().HP);
    EnemyZombie::SetMaxHP(Pram().MaxHP);
    EnemyZombie::SetAttack(Pram().Attack);
    EnemyZombie::SetDefense(Pram().Defense);
    EnemyZombie::SetSpeed(Pram().Speed);
}

// 更新処理
void EnemyZombie::Update(float elapsedTime)
{
    // ステートごとの処理
    switch (state)
    {
    case EnemyZombie::State::Idle:// 待機
        UpdateIdleState(elapsedTime);
        break;
    case EnemyZombie::State::Attack:// 攻撃
        UpdateAttackState(elapsedTime);
        break;
    case EnemyZombie::State::Defense:// 防御
        UpdateDeathState(elapsedTime);
        break;
    case EnemyZombie::State::Run:// 逃走
        UpdateRunState(elapsedTime);
        break;
    case EnemyZombie::State::Damage:// ダメージ
        UpdateDamageState(elapsedTime);
        break;
    case EnemyZombie::State::Death:// 死亡
        UpdateDeathState(elapsedTime);
        break;
    }
}

// 描画処理
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

// ダメージ
void EnemyZombie::OnDamaged()
{
    TransitionDamageState();
}

// 死亡
void EnemyZombie::OnDead()
{
    TransitionDeathState();
}

// 待機
void EnemyZombie::TransitionIdleState()
{
    state = State::Idle;
}
void EnemyZombie::UpdateIdleState(float elapsedTime)
{
}

// 攻撃
void EnemyZombie::TransitionAttackState()
{
    state = State::Attack;
}
void EnemyZombie::UpdateAttackState(float elapsedTime)
{
}

// 防御
void EnemyZombie::TransitionDefenseState()
{
    state = State::Defense;
}
void EnemyZombie::UpdateDefenseState(float elapsedTime)
{
}

// 逃走
void EnemyZombie::TransitionRunState()
{
    state = State::Run;
}
void EnemyZombie::UpdateRunState(float elapsedTime)
{
}

// ダメージ
void EnemyZombie::TransitionDamageState()
{
    state = State::Damage;
}
void EnemyZombie::UpdateDamageState(float elapsedTime)
{
}

// 死亡
void EnemyZombie::TransitionDeathState()
{
    state = State::Death;
}
void EnemyZombie::UpdateDeathState(float elapsedTime)
{
}
