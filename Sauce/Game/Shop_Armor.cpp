#include <imgui.h>
#include "Shop_Armor.h"
#include "Item_Armor.h"

// コンストラクタ
ShopArmor::ShopArmor()
{
    items = std::make_unique<Item>("Data/Text/Armor.txt");
}

// 更新処理
void ShopArmor::Update()
{
    switch (state)
    {
    case ShopArmor::None:
        break;
    case ShopArmor::Talk:
        break;
    case ShopArmor::Buy:
        break;
    case ShopArmor::Sell:
        break;
    case ShopArmor::End:
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

// 話す
void ShopArmor::Shop_Talk()
{
}

// 買う
void ShopArmor::Shop_Buy()
{
}

// 売る
void ShopArmor::Shop_Sell()
{
}
