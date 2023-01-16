#include <memory>
#include <sstream>

#include"Framework.h"
#include"Graphics/Graphic.h"
#include"Input.h"
#include"Game/Scene_Manager.h"
#include"Game/Scene_Meta.h"

// ���������Ԋu�ݒ�
static const int syncInterval = 1;

// �R���X�g���N�^
Framework::Framework(HWND hWnd):
    hWnd(hWnd),
    graphic(hWnd),
    input(hWnd)
{
    // �V�[��������
    SceneManager::Instance().ChangeScene(new SceneMeta);
}

// �f�X�g���N�^
Framework::~Framework()
{
    // �V�[���I����
    SceneManager::Instance().Clear();
}

// �X�V����
void Framework::Update(float elapsedTime)
{
    // ���͏��� 
    input.Update();

    // �V�[���X�V����
    SceneManager::Instance().Update(elapsedTime);
}

// �`�揈��
void Framework::Render(float elapsedTime)
{
    // �ʃX���b�h���Ƀf�o�C�X�R���e�L�X�g���g���Ă����ꍇ��
    // �����A�N�Z�X���Ȃ��悤�ɔr�����䂷��
    std::lock_guard<std::mutex> lock(graphic.GetMutex());
    ID3D11DeviceContext* dc = graphic.GetDeviceContext();

    // �V�[���`�揈��
    SceneManager::Instance().Render();

    // �o�b�N�o�b�t�@�ɕ`�悵�������ʂɕ\������B
    graphic.GetSwapChain()->Present(syncInterval, 0);

}

// �t���[�����[�g�v�Z����
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

// �A�v���P�[�V�������[�v
int Framework::Run()
{
    //���b�Z�[�W���[�v
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

// ���b�Z�[�W�n���h���[
LRESULT Framework::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    //if (Graphics::Instance().GetImGuiRenderer()->HandleMessage(
    //    hWnd, msg, wParam, lParam))
    //    return true;

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