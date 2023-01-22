#include <imgui.h>
#include "Shop_Armor.h"
#include "Item_Armor.h"

// �R���X�g���N�^
ShopArmor::ShopArmor()
{
    items = std::make_unique<Item>("Data/Text/Armor.txt");
}

// �X�V����
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

// �`�揈��
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

// �b��
void ShopArmor::Shop_Talk()
{
}

// ����
void ShopArmor::Shop_Buy()
{
}

// ����
void ShopArmor::Shop_Sell()
{
}
