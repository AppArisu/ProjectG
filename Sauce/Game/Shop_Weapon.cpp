#include<imgui.h>
#include"Item_Weapon.h"
#include"Shop_Weapon.h"

// �R���X�g���N�^
ShopWeapon::ShopWeapon()
{
    items = std::make_unique<Item>("Data/Text/Weapon.txt");
}

// �X�V����
void ShopWeapon::Update()
{
    switch (state)
    {
    case ShopWeapon::None:
        break;
    case ShopWeapon::Talk:
        break;
    case ShopWeapon::Buy:
        break;
    case ShopWeapon::Sell:
        break;
    case ShopWeapon::End:
        break;
    }
}

// �`�揈��
void ShopWeapon::Render()
{
    RenderImGui();
}

void ShopWeapon::RenderImGui()
{
    using enum ItemWeapon::WeaponID;

    ImGui::Begin("Item");
    if (ImGui::TreeNode("Weapon"))
    {
        for (int i = 0; i < WeaponMax; i++)
        {
            ImGui::Text(items->itemParam(i)->Name);
        }
        ImGui::TreePop();
    }
    ImGui::End();
}

// �b��
void ShopWeapon::Shop_Talk()
{
}

// ����
void ShopWeapon::Shop_Buy()
{
}

// ����
void ShopWeapon::Shop_Sell()
{
}