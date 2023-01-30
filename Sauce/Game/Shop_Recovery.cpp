#include<imgui.h>
#include"Shop_Recovery.h"
#include"Item_Recovery.h"

// �R���X�g���N�^
ShopRecovery::ShopRecovery()
{
    TransitionNoneState();

    items = std::make_unique<Item>("Data/Text/Recovery.txt");
}

// �X�V����
void ShopRecovery::Update()
{
    switch (state)
    {
    case Shop::None: // �Ȃ�
        UpdateNoneState(1);
        break;
    case Shop::Talk: // �b��
        UpdateNoneState(1);
        break;
    case Shop::Buy: // ����
        UpdateNoneState(1);
        break;
    case Shop::Sell: // ����
        UpdateNoneState(1);
        break;
    case Shop::End: // �I���
        UpdateNoneState(1);
        break;
    }
}

// �`�揈��
void ShopRecovery::Render()
{
    RenderImGui();
}

void ShopRecovery::RenderImGui()
{
    using enum ItemRecovery::RecoveryID;
    ImGui::Begin("Item");
    if (ImGui::TreeNode("Recovery"))
    {
        for (int i = 0; i < RecoveryMax; i++)
        {
            ImGui::Text(items->itemParam(i)->Name);
        }
        ImGui::TreePop();
    }
    ImGui::End();
}

// �Ȃ�
void ShopRecovery::TransitionNoneState()
{
    state = State::None;
}
void ShopRecovery::UpdateNoneState(float elapsedTime)
{
}

// �b��
void ShopRecovery::TransitionTalkState()
{
    state = State::Talk;
}
void ShopRecovery::UpdateTalkState(float elapsedTime)
{
}

// ����
void ShopRecovery::TransitionBuyState()
{
    state = State::Buy;
}
void ShopRecovery::UpdateBuyState(float elapsedTime)
{
}

// ����
void ShopRecovery::TransitionSellState()
{
    state = State::Sell;
}
void ShopRecovery::UpdateSellState(float elapsedTime)
{
}

// �I���
void ShopRecovery::TransitionEndState()
{
    state = State::End;
}
void ShopRecovery::UpdateEndState(float elapsedTime)
{
}
