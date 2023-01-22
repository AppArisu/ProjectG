#pragma once

class Shop
{
public:
    Shop() {}
    virtual ~Shop() {}

    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void RenderImGui() = 0;

    virtual void Shop_Talk() = 0;
    virtual void Shop_Buy() = 0;
    virtual void Shop_Sell() = 0;
};