#pragma once
#include "Scene.h"
#include "Shop_Weapon.h"
#include "Shop_Armor.h"
#include  "Shop_Recovery.h"
#include "Shop_Tool.h"

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

    // �`�揈��
    void Render() override;

    void RenderImGui() override;

    // �V�[���J��
    void Change(float elapsedTime);

private:
    // �V���b�v
    std::unique_ptr<ShopWeapon> weapon = nullptr;
    std::unique_ptr<ShopArmor> armor = nullptr;
    std::unique_ptr<ShopRecovery> recovery = nullptr;
    std::unique_ptr<ShopTool> tool = nullptr;

};