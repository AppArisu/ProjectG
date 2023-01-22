#include<imgui.h>
#include"Shop_Recovery.h"
#include"Item_Recovery.h"

// コンストラクタ
ShopRecovery::ShopRecovery()
{
    items = std::make_unique<Item>("Data/Text/Recovery.txt");
}

// 更新処理
void ShopRecovery::Update()
{
    switch (state)
    {
    case ShopRecovery::None:
        break;
    case ShopRecovery::Talk:
        break;
    case ShopRecovery::Buy:
        break;
    case ShopRecovery::Sell:
        break;
    case ShopRecovery::End:
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

// 話す
void ShopRecovery::Shop_Talk()
{
}

// 買う
void ShopRecovery::Shop_Buy()
{
}

// 売る
void ShopRecovery::Shop_Sell()
{
}