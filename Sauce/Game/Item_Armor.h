#pragma once
#include"Item.h"

class ItemArmor :public Item
{
public:
    int GetItemID() const { return armorId; }
    void SetItemID(int id) { this->armorId = id; }

public:
    enum ArmorID
    {
        Leather_Hat,        // ”ç‚Ì–XŽq
        Leather_Armor,    // ”ç‚ÌŠZ
        Iron_Helmet,        // “S‚ÌŠ•
        Iron_Armor,         // “S‚ÌŠZ

        ArmorMax
    };

private:
    int armorId = 0;
};