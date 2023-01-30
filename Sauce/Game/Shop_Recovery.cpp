#include<imgui.h>
#include"Shop_Recovery.h"
#include"Item_Recovery.h"

// コンストラクタ
ShopRecovery::ShopRecovery()
{
    TransitionNoneState();

    items = std::make_unique<Item>("Data/Text/Recovery.txt");
}

// 更新処理
void ShopRecovery::Update()
{
    switch (state)
    {
    case Shop::None: // なし
        UpdateNoneState(1);
        break;
    case Shop::Talk: // 話す
        UpdateNoneState(1);
        break;
    case Shop::Buy: // 買う
        UpdateNoneState(1);
        break;
    case Shop::Sell: // 売る
        UpdateNoneState(1);
        break;
    case Shop::End: // 終わり
        UpdateNoneState(1);
        break;
    }
}

// 描画処理
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

// なし
void ShopRecovery::TransitionNoneState()
{
    state = State::None;
}
void ShopRecovery::UpdateNoneState(float elapsedTime)
{
}

// 話す
void ShopRecovery::TransitionTalkState()
{
    state = State::Talk;
}
void ShopRecovery::UpdateTalkState(float elapsedTime)
{
}

// 買う
void ShopRecovery::TransitionBuyState()
{
    state = State::Buy;
}
void ShopRecovery::UpdateBuyState(float elapsedTime)
{
}

// 売る
void ShopRecovery::TransitionSellState()
{
    state = State::Sell;
}
void ShopRecovery::UpdateSellState(float elapsedTime)
{
}

// 終わり
void ShopRecovery::TransitionEndState()
{
    state = State::End;
}
void ShopRecovery::UpdateEndState(float elapsedTime)
{
}
