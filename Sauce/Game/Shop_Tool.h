#pragma once
#include<memory>
#include "Shop.h"
#include "Item.h"

class ShopTool :public Shop
{
public:
    ShopTool();
    ~ShopTool()override {}

    // インスタンス取得
    static ShopTool& Instance()
    {
        static ShopTool instance;
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