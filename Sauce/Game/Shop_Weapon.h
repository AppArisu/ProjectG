#pragma once
#include<memory>
#include "Shop.h"
#include "Item.h"

class ShopWeapon :public Shop
{
public:
    ShopWeapon();
    ~ShopWeapon()override {}

    // インスタンス取得
    static ShopWeapon& Instance()
    {
        static ShopWeapon instance;
        return instance;
    }

    void Update() override;
    void Render() override;
    void RenderImGui() override;

    void Shop_Talk() override;
    void Shop_Buy() override;
    void Shop_Sell() override;

protected:
    enum State
    {
        None,
        Talk,
        Buy,
        Sell,
        End
    };

private:
    std::unique_ptr<Item> items = nullptr;

    State state = State::None;

    int select = 0;
};