#include <imgui.h>
#include "Shop_Armor.h"
#include "Item_Armor.h"

// コンストラクタ
ShopArmor::ShopArmor()
{
    TransitionNoneState();

    items = std::make_unique<Item>("Data/Text/Armor.txt");
}

// 更新処理
void ShopArmor::Update()
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
void ShopArmor::Render()
{
    RenderImGui();
}

void ShopArmor::RenderImGui()
{
    using enum ItemArmor::ArmorID;
    ImGui::Begin("Item");
    if (ImGui::TreeNode("Armor"))
    {
        for (int i = 0; i < ArmorMax; i++)
        {
            ImGui::Text(items->itemParam(i)->Name);
        }
        ImGui::TreePop();
    }
    ImGui::End();
}

// なし
void ShopArmor::TransitionNoneState()
{
    state = State::None;
}
void ShopArmor::UpdateNoneState(float elapsedTime)
{
}

// 話す
void ShopArmor::TransitionTalkState()
{
    state = State::Talk;
}
void ShopArmor::UpdateTalkState(float elapsedTime)
{
}

// 買う
void ShopArmor::TransitionBuyState()
{
    state = State::Buy;
}
void ShopArmor::UpdateBuyState(float elapsedTime)
{
}

// 売る
void ShopArmor::TransitionSellState()
{
    state = State::Sell;
}
void ShopArmor::UpdateSellState(float elapsedTime)
{
}

// 終わり
void ShopArmor::TransitionEndState()
{
    state = State::End;
}
void ShopArmor::UpdateEndState(float elapsedTime)
{
}
