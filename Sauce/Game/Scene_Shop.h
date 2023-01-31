#pragma once
#include "Scene.h"
#include "Shop_Weapon.h"
#include "Shop_Armor.h"
#include  "Shop_Recovery.h"
#include "Shop_Tool.h"
#include "UI_Paused.h"

// �V���b�v�V�[��
class SceneShop :public Scene
{
public:
    SceneShop() {}
    ~SceneShop()override {}

    // ������
    void Initialize() override;

    // �I����
    void Finalize() override;

    // �X�V����
    void Update(float elapsedTime) override;
    void ProcessInput() override;

    // �`�揈��
    void Render() override;
    void RenderImGui() override;

    // �V�[���J��
    void Change(float elapsedTime);

private:
    // �Ȃ�
    void TransitionNoneState();
    void UpdateNoneState(float elapsedTime);

    // ����
    void TransitionWeaponState();
    void UpdateWeaponState(float elapsedTime);

    // �h��
    void TransitionArmorState();
    void UpdateArmorState(float elapsedTime);

    // ��
    void TransitionRecoveryState();
    void UpdateRecoveryState(float elapsedTime);

    // ����
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
    // �V���b�v
    std::unique_ptr<ShopWeapon> weapon = nullptr;
    std::unique_ptr<ShopArmor> armor = nullptr;
    std::unique_ptr<ShopRecovery> recovery = nullptr;
    std::unique_ptr<ShopTool> tool = nullptr;

    bool SceneChangeflg = false;

    // UI
    std::unique_ptr<UIPaused> paused = nullptr;

    State state = State::None;
};