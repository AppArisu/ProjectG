#pragma once
#include"Item.h"

class ItemRecovery :public Item
{
public:
    int GetItemID() const { return recoveryId; }
    void SetItemID(int id) { this->recoveryId = id; }

public:
    enum RecoveryID
    {
        Herb_Cure,              // –ò‘
        Herb_AntiPoison,     // “ÅÁ‚µ‘
        Portion_Cure,          // ‰ñ•œ–ò
        Portion_AntiPoison, // “ÅÁ‚µ–ò

        RecoveryMax
    };

private:
    int recoveryId = 0;
};