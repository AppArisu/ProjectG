#include<imgui.h>
#include "Shop_Tool.h"
#include "item_Tool.h"

// �R���X�g���N�^
ShopTool::ShopTool()
{
    items = std::make_unique<Item>("Data/Text/Tool.txt");
}

// �X�V����
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

// �`�揈��
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

// �b��
void ShopTool::Shop_Talk()
{
}

// ����
void ShopTool::Shop_Buy()
{
}

// ����
void ShopTool::Shop_Sell()
{
}