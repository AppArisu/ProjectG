#include <memory>
#include <sstream>

#include"Framework.h"
#include"Graphics/Graphic.h"
#include"Input.h"
#include"Game/Scene_Manager.h"
#include"Game/Scene_Meta.h"

// 垂直同期間隔設定
static const int syncInterval = 1;

// コンストラクタ
Framework::Framework(HWND hWnd):
    hWnd(hWnd),
    graphic(hWnd),
    input(hWnd)
{
    // シーン初期化
    SceneManager::Instance().ChangeScene(new SceneMeta);
}

// デストラクタ
Framework::~Framework()
{
    // シーン終了化
    SceneManager::Instance().Clear();
}

// 更新処理
void Framework::Update(float elapsedTime)
{
    // 入力処理 
    input.Update();

    // シーン更新処理
    SceneManager::Instance().Update(elapsedTime);
}

// 描画処理
void Framework::Render(float elapsedTime)
{
    // 別スレッド中にデバイスコンテキストが使われていた場合に
    // 同時アクセスしないように排他制御する
    std::lock_guard<std::mutex> lock(graphic.GetMutex());
    ID3D11DeviceContext* dc = graphic.GetDeviceContext();

    // IMGUIフレーム開始処理
    graphic.GetImGuiRenderer()->NewFrame();

    // シーン描画処理
    SceneManager::Instance().Render();

    // IMGUI描画
    graphic.GetImGuiRenderer()->Render(dc);

    // バックバッファに描画した画を画面に表示する。
    graphic.GetSwapChain()->Present(syncInterval, 0);
}

// フレームレート計算処理
void Framework::CalculateFrameStats()
{
    static int frames = 0;
    static float time_tlapsed = 0.0f;

    frames++;

    if ((timer.TimeStamp() - time_tlapsed) >= 1.0f)
    {
        float fps = static_cast<float>(frames); // fps = frameCnt / 1
        float mspf = 1000.0f / fps;
        std::ostringstream outs;
        outs.precision(6);
        outs << "FPS : " << fps << " / " << "Frame Time : " << mspf << " (ms)";
        SetWindowTextA(hWnd, outs.str().c_str());

        frames = 0;
        time_tlapsed += 1.0f;
    }
}

// アプリケーションループ
int Framework::Run()
{
    //メッセージループ
    MSG msg = {};

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            timer.Tick();
            CalculateFrameStats();

            float elapsedTime = syncInterval == 0
                ? timer.TimeInterval()
                : syncInterval / 60.0f
                ;
            Update(elapsedTime);
            Render(elapsedTime);
        }
    }
    return static_cast<int>(msg.wParam);
}

// メッセージハンドラー
LRESULT Framework::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (Graphic::Instance().GetImGuiRenderer()->HandleMessage(
        hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc;
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CREATE:
        break;
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) PostMessage(hWnd, WM_CLOSE, 0, 0);
        break;
    case WM_ENTERSIZEMOVE:
        // WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
        timer.Stop();
        break;
    case WM_EXITSIZEMOVE:
        // WM_EXITSIZEMOVE is sent when the user releases the resize bars.
        // Here we reset everything based on the new window dimensions.
        timer.Start();
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}
