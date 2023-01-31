#pragma once
#include "Scene.h"
#include "Shop_Weapon.h"
#include "Shop_Armor.h"
#include  "Shop_Recovery.h"
#include "Shop_Tool.h"
#include "UI_Paused.h"

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
    void ProcessInput() override;

    // 描画処理
    void Render() override;
    void RenderImGui() override;

    // シーン遷移
    void Change(float elapsedTime);

private:
    // なし
    void TransitionNoneState();
    void UpdateNoneState(float elapsedTime);

    // 武器
    void TransitionWeaponState();
    void UpdateWeaponState(float elapsedTime);

    // 防具
    void TransitionArmorState();
    void UpdateArmorState(float elapsedTime);

    // 回復
    void TransitionRecoveryState();
    void UpdateRecoveryState(float elapsedTime);

    // 道具
    void TransitionToolState();
    void UpdateToolState(float elapsedTime);

    enum class State
    {
        None,
        Weapon,
        Armor,
        Recovery,
        Tool
    };

private:
    // ショップ
    std::unique_ptr<ShopWeapon> weapon = nullptr;
    std::unique_ptr<ShopArmor> armor = nullptr;
    std::unique_ptr<ShopRecovery> recovery = nullptr;
    std::unique_ptr<ShopTool> tool = nullptr;

    bool SceneChangeflg = false;

    // UI
    std::unique_ptr<UIPaused> paused = nullptr;

    State state = State::None;
};