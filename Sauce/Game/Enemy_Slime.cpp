#include<imgui.h>
#include"Enemy_Slime.h"

// コンストラクタ
EnemySlime::EnemySlime()
{
    TransitionIdleState();

    EnemySlime::SetHP(Pram().HP);
    EnemySlime::SetMaxHP(Pram().MaxHP);
    EnemySlime::SetAttack(Pram().Attack);
    EnemySlime::SetDefense(Pram().Defense);
    EnemySlime::SetSpeed(Pram().Speed);
}

// 更新処理
void EnemySlime::Update(float elapsedTime)
{
    // ステートごとの処理
    switch (state)
    {
    case EnemySlime::State::Idle:// 待機
        UpdateIdleState(elapsedTime);
        break;
    case EnemySlime::State::Attack:// 攻撃
        UpdateAttackState(elapsedTime);
        break;
    case EnemySlime::State::Defense:// 防御
        UpdateDeathState(elapsedTime);
        break;
    case EnemySlime::State::Run:// 逃走
        UpdateRunState(elapsedTime);
        break;
    case EnemySlime::State::Damage:// ダメージ
        UpdateDamageState(elapsedTime);
        break;
    case EnemySlime::State::Death:// 死亡
        UpdateDeathState(elapsedTime);
        break;
    }
}

// 描画処理
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

// ダメージ
void EnemySlime::OnDamaged()
{
    TransitionDamageState();
}

// 死亡
void EnemySlime::OnDead()
{
    TransitionDeathState();
}

// 待機
void EnemySlime::TransitionIdleState()
{
    state = State::Idle;
}
void EnemySlime::UpdateIdleState(float elapsedTime)
{
}

// 攻撃
void EnemySlime::TransitionAttackState()
{
    state = State::Attack;
}
void EnemySlime::UpdateAttackState(float elapsedTime)
{
}

// 防御
void EnemySlime::TransitionDefenseState()
{
    state = State::Defense;
}
void EnemySlime::UpdateDefenseState(float elapsedTime)
{
}

// 逃走
void EnemySlime::TransitionRunState()
{
    state = State::Run;
}
void EnemySlime::UpdateRunState(float elapsedTime)
{
}

// ダメージ
void EnemySlime::TransitionDamageState()
{
    state = State::Damage;
}
void EnemySlime::UpdateDamageState(float elapsedTime)
{
}

// 死亡
void EnemySlime::TransitionDeathState()
{
    state = State::Death;
}
void EnemySlime::UpdateDeathState(float elapsedTime)
{
}
