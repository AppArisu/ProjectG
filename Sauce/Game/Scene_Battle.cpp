#include "Scene_Battle.h"
#include "Scene_Game.h"
#include "../Graphics/Graphic.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "../Input.h"
#include "EnemyManager.h"

// ������
void SceneBattle::Initialize()
{
    TransitionIdleState();

    // �v���C���[
    player = std::make_unique<Player>();

    // �G�l�~�[
    CallEnemy(slime);
    CallEnemy(robot);
    CallEnemy(zombie);
}

// �I����
void SceneBattle::Finalize()
{
    EnemyManager::Instance().Clear();
}

// �X�V����
void SceneBattle::Update(float elapsedTime)
{
    ProcessInput();

    if (GetGameState() == GameState::Play)
    {
        switch (state)
        {
        case SceneBattle::Idle:
            UpdateIdleState(elapsedTime);
            break;
        case SceneBattle::Attack:
            UpdateAttackState(elapsedTime);
            break;
        case SceneBattle::Defense:
            UpdateDefenseState(elapsedTime);
            break;
        case SceneBattle::Tools:
            UpdateToolsState(elapsedTime);
            break;
        case SceneBattle::Run:
            UpdateRunState(elapsedTime);
            break;
        case SceneBattle::End:
            UpdateEndState(elapsedTime);
            break;
        }
    }
}

// �L�[�Ǘ�
void SceneBattle::ProcessInput()
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    if (GetGameState() == Play)
    {
        if (gamePad.GetButtonDown() & GamePad::BTN_A ||
            GetKeyState(VK_RETURN) & 0x800)
        {
            SceneChangeflg = true;
        }
        if (GetKeyState(VK_TAB) & 0x800)
        {
            // �|�[�Y�Ɉڍs
            paused = std::make_unique<UIPaused>(this);
        }
    }

    if (GetGameState() == Paused)
    {
        paused->Update();
    }
}

// �`�揈��
void SceneBattle::Render()
{
    Graphic& graphics = Graphic::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
    FLOAT color[] = { 0.0f, 0.0f, 1.0f, 1.0f };	// RGBA(0.0�`1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    if (GetGameState() == Paused)
    {
        paused->Render();
        RenderImGui();
    }
}

void SceneBattle::RenderImGui()
{
#if _DEBUG
    player->Render(1);

    slime->Render(1);
    robot->Render(2);
    zombie->Render(3);
#endif
}

// �G�l�~�[�Ăяo��
void SceneBattle::CallEnemy(Enemy* enemy)
{
    EnemyManager& enemyManager = EnemyManager::Instance();

    if (enemy == slime)
    {
        slime = new EnemySlime;
    }
    if (enemy == robot)
    {
        robot = new EnemyRobot;
    }
    if (enemy == zombie)
    {
        zombie = new EnemyZombie;
    }
    enemyManager.Register(enemy);
}

// �ҋ@
void SceneBattle::TransitionIdleState()
{
    state = BState::Idle;
}
void SceneBattle::UpdateIdleState(float elapsedTime)
{
    if (SceneChangeflg)
    {
        Change(elapsedTime);
    }

    if (GetAsyncKeyState('1') & 0x8000)
    {
        TransitionAttackState();
    }
    if (GetAsyncKeyState('2') & 0x8000)
    {
        TransitionDefenseState();
    }
    if (GetAsyncKeyState('3') & 0x8000)
    {
        TransitionToolsState();
    }
    if (GetAsyncKeyState('4') & 0x8000)
    {
        TransitionRunState();
    }

    if (player->GetHP() <= 0 || slime->GetHP() <= 0)
    {
        TransitionEndState();
    }
}

// �U��
void SceneBattle::TransitionAttackState()
{
    state = BState::Attack;
}
void SceneBattle::UpdateAttackState(float elapsedTime)
{
    slime->SetHP(slime->GetHP() - player->GetAttack());
    player->SetHP(player->GetHP() - slime->GetAttack());

    TransitionIdleState();
}

// �h��
void SceneBattle::TransitionDefenseState()
{
    state = BState::Defense;
}
void SceneBattle::UpdateDefenseState(float elapsedTime)
{
    slime->SetHP(slime->GetHP() - player->GetAttack());
    player->SetHP(player->GetHP() - (slime->GetAttack() - player->GetDefense()));

    TransitionIdleState();
}

// ����
void SceneBattle::TransitionToolsState()
{
    state = BState::Tools;
}
void SceneBattle::UpdateToolsState(float elapsedTime)
{
    TransitionIdleState();
}

// ������
void SceneBattle::TransitionRunState()
{
    state = BState::Run;
}
void SceneBattle::UpdateRunState(float elapsedTime)
{
    TransitionIdleState();
}

// �I��
void SceneBattle::TransitionEndState()
{
    state = BState::End;
}
void SceneBattle::UpdateEndState(float elapsedTime)
{
    Change(elapsedTime);
}

// �V�[���J�ڏ���
void SceneBattle::Change(float elapsedTime)
{
    SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
}
