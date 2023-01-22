#pragma once
#include"Item.h"

class ItemTool :public Item
{
public:
    int GetItemID() const { return toolId; }
    void SetItemID(int id) { this->toolId = id; }

public:
    enum ToolID
    {
        Stone,

        ToolMax
    };

private:
    int toolId = 0;
};