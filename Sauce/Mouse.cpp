#include "Mouse.h"

static FLOAT zero = 0.0f;

enum state
{
	Set,
	Get
};

static const int KeyMap[] =
{
	VK_LBUTTON,		// 左ボタン
	VK_MBUTTON,		// 中ボタン
	VK_RBUTTON,		// 右ボタン
};

// コンストラクタ
Mouse::Mouse(HWND hWnd) : hWnd(hWnd)
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	screenWidth = rc.right - rc.left;
	screenHeight = rc.bottom - rc.top;
}

// 更新処理
void Mouse::Update()
{
	// スイッチ情報
	MouseButton newButtonState = zero;

	for (int i = 0; i < ARRAYSIZE(KeyMap); ++i)
	{
		if (::GetAsyncKeyState(KeyMap[i]) & 0x8000)
		{
			newButtonState |= (1 << i);
		}
	}

	// ホイール
	wheel[state::Get] = wheel[state::Set];
	wheel[state::Set] = 0;

	// ボタン情報更新
	buttonState[state::Get] = buttonState[state::Set];	// スイッチ履歴
	buttonState[state::Set] = newButtonState;

	buttonDown = ~buttonState[state::Get] & newButtonState;	// 押した瞬間
	buttonUp = ~newButtonState & buttonState[state::Get];	// 離した瞬間

	// カーソル位置の取得
	POINT cursor;
	::GetCursorPos(&cursor);
	::ScreenToClient(hWnd, &cursor);

	// 画面のサイズを取得する。
	RECT rc;
	GetClientRect(hWnd, &rc);
	UINT screenW = rc.right - rc.left;
	UINT screenH = rc.bottom - rc.top;
	UINT viewportW = screenWidth;
	UINT viewportH = screenHeight;

	// 画面補正
	positionX[state::Get] = positionX[state::Set];
	positionY[state::Get] = positionY[state::Set];
	positionX[state::Set] = (LONG)(cursor.x / static_cast<float>(viewportW) * static_cast<float>(screenW));
	positionY[state::Set] = (LONG)(cursor.y / static_cast<float>(viewportH) * static_cast<float>(screenH));
}
