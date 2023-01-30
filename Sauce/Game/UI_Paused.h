#pragma once
#include "UI_Screen.h"

class UIPaused :public UIScreen
{
public:
    UIPaused(Scene* scene);
    ~UIPaused() override {}

    void Update() override;
    void Render() override;
};