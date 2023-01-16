#pragma once
#include<Windows.h>

#include"HighResolutionTimer.h"
#include"Graphics/Graphic.h"
#include"Input.h"

class Framework
{
public:
    Framework(HWND hWnd);
    ~Framework();
private:
    void Update(float elapsedTime);
    void Render(float elapsedTime);

    void CalculateFrameStats();
public:
    int Run();

    LRESULT CALLBACK HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
    const HWND				hWnd;
    HighResolutionTimer		timer;
    Graphic				graphic;
    Input					input;
    //Audio					audio;
};