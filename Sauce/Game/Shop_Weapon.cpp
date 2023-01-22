#include<imgui.h>
#include"Item_Weapon.h"
#include"Shop_Weapon.h"

// コンストラクタ
ShopWeapon::ShopWeapon()
{
    items = std::make_unique<Item>("Data/Text/Weapon.txt");
}

// 更新処理
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

// 描画処理
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

// 話す
void ShopWeapon::Shop_Talk()
{
}

// 買う
void ShopWeapon::Shop_Buy()
{
}

// 売る
void ShopWeapon::Shop_Sell()
{
}