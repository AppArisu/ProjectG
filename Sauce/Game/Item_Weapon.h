#pragma once
#include"Item.h"

class ItemWeapon :public Item
{
public:
    int GetItemID() const { return weaponId; }
    void SetItemID(int id) { this->weaponId = id; }

public:
    enum WeaponID
    {
        Sword_Wood,     // –Ø‚ÌŒ•
        Sword_Stone,     // Î‚ÌŒ•
        Sword_Iron,       // “S‚ÌŒ•

        WeaponMax
    };

private:
    int weaponId = 0;
};