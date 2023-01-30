#pragma once
#include "UI_Screen.h"

class UIQuit :public UIScreen
{
public:
    UIQuit(Scene* scene);
    ~UIQuit() override {}

    void Update() override;
    void Render() override;
};