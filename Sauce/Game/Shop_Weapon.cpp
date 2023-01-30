#include<imgui.h>
#include"Item_Weapon.h"
#include"Shop_Weapon.h"

// コンストラクタ
ShopWeapon::ShopWeapon()
{
    TransitionNoneState();

    items = std::make_unique<Item>("Data/Text/Weapon.txt");
}

// 更新処理
void ShopWeapon::Update()
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

// なし
void ShopWeapon::TransitionNoneState()
{
    state = State::None;
}
void ShopWeapon::UpdateNoneState(float elapsedTime)
{
}

// 話す
void ShopWeapon::TransitionTalkState()
{
    state = State::Talk;
}
void ShopWeapon::UpdateTalkState(float elapsedTime)
{
}

// 買う
void ShopWeapon::TransitionBuyState()
{
    state = State::Buy;
}
void ShopWeapon::UpdateBuyState(float elapsedTime)
{
}

// 売る
void ShopWeapon::TransitionSellState()
{
    state = State::Sell;
}
void ShopWeapon::UpdateSellState(float elapsedTime)
{
}

// 終わり
void ShopWeapon::TransitionEndState()
{
    state = State::End;
}
void ShopWeapon::UpdateEndState(float elapsedTime)
{
}
