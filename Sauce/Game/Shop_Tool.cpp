#include<imgui.h>
#include "Shop_Tool.h"
#include "item_Tool.h"

// コンストラクタ
ShopTool::ShopTool()
{
    TransitionNoneState();

    items = std::make_unique<Item>("Data/Text/Tool.txt");
}

// 更新処理
void ShopTool::Update()
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

// なし
void ShopTool::TransitionNoneState()
{
    state = State::None;
}
void ShopTool::UpdateNoneState(float elapsedTime)
{
}

// 話す
void ShopTool::TransitionTalkState()
{
    state = State::Talk;
}
void ShopTool::UpdateTalkState(float elapsedTime)
{
}

// 買う
void ShopTool::TransitionBuyState()
{
    state = State::Buy;
}
void ShopTool::UpdateBuyState(float elapsedTime)
{
}

// 売る
void ShopTool::TransitionSellState()
{
    state = State::Sell;
}
void ShopTool::UpdateSellState(float elapsedTime)
{
}

// 終わり
void ShopTool::TransitionEndState()
{
    state = State::End;
}
void ShopTool::UpdateEndState(float elapsedTime)
{
}
