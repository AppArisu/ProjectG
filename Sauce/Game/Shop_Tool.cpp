#include<imgui.h>
#include "Shop_Tool.h"
#include "item_Tool.h"

// コンストラクタ
ShopTool::ShopTool()
{
    items = std::make_unique<Item>("Data/Text/Tool.txt");
}

// 更新処理
void ShopTool::Update()
{
    switch (state)
    {
    case ShopTool::None:
        break;
    case ShopTool::Talk:
        break;
    case ShopTool::Buy:
        break;
    case ShopTool::Sell:
        break;
    case ShopTool::End:
        break;
    }
}

// 描画処理
void ShopTool::Render()
{
    RenderImGui();
}

void ShopTool::RenderImGui()
{
    using enum ItemTool::ToolID;

    ImGui::Begin("Item");
    if (ImGui::TreeNode("Tool"))
    {
        for (int i = 0; i < ToolMax; i++)
        {
            ImGui::Text(items->itemParam(i)->Name);
        }
        ImGui::TreePop();
    }
    ImGui::End();
}

// 話す
void ShopTool::Shop_Talk()
{
}

// 買う
void ShopTool::Shop_Buy()
{
}

// 売る
void ShopTool::Shop_Sell()
{
}