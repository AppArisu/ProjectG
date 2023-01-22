#pragma once
#include "Scene.h"
#include "Shop_Weapon.h"
#include "Shop_Armor.h"
#include  "Shop_Recovery.h"
#include "Shop_Tool.h"

// ショップシーン
class SceneShop :public Scene
{
public:
    SceneShop() {}
    ~SceneShop()override {}

    // 初期化
    void Initialize() override;

    // 終了化
    void Finalize() override;

    // 更新処理
    void Update(float elapsedTime) override;

    // 描画処理
    void Render() override;

    void RenderImGui() override;

    // シーン遷移
    void Change(float elapsedTime);

private:
    // ショップ
    std::unique_ptr<ShopWeapon> weapon = nullptr;
    std::unique_ptr<ShopArmor> armor = nullptr;
    std::unique_ptr<ShopRecovery> recovery = nullptr;
    std::unique_ptr<ShopTool> tool = nullptr;

};