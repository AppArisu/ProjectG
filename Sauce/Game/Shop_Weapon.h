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

private:
    // なし
    void TransitionNoneState() override;
    void UpdateNoneState(float elapsedTime) override;

    // 話す
    void TransitionTalkState() override;
    void UpdateTalkState(float elapsedTime) override;

    // 買う
    void TransitionBuyState() override;
    void UpdateBuyState(float elapsedTime) override;

    // 売る
    void TransitionSellState() override;
    void UpdateSellState(float elapsedTime) override;

    // 終わる
    void TransitionEndState() override;
    void UpdateEndState(float elapsedTime) override;

private:
    std::unique_ptr<Item> items = nullptr;

    int select = 0;
};