/*******************************************************************************
*
*	タイトル：	メイン	[ main.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include <time.h>
#include "imgui_impl_win32.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

const char* g_CLASS_NAME = "AppClass";			// ウィンドウクラス名
const char* g_WINDOW_NAME = "Framework";	// ウィンドウキャプション
HWND g_Window;									// ウィンドウハンドル
//bool g_IsFullScreen = false;					// フルスクリーンフラグ
//bool g_IsSleep = false;							// ゲーム停止フラグ
//bool g_IsWireFrame = false;						// ワイヤフレーム表示フラグ
//bool g_IsMoveCursor = true;
#ifdef _DEBUG
int g_CountFPS;				// FPS値
char g_DebugStr[2048];		// ウィンドウキャプションにつなげて表示する情報
#endif

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ランダムシードの初期化
	srand((unsigned int)time(NULL));

	// ウィンドウクラス作成
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		g_CLASS_NAME,
		NULL
	};

	// ウィンドウ作成の為、ウィンドウクラスを登録
	RegisterClassEx(&wcex);

	// ウィンドウ作成
	g_Window = CreateWindowEx(0,
		g_CLASS_NAME,
		g_WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		(int)(GetSystemMetrics(SM_CXSCREEN) * ((1.0f - WINDOW_DEFAULT_WINDOWMODE_RATE_WIDTH) * 0.5f)),			// ウィンドウ位置(X)
		(int)(GetSystemMetrics(SM_CYSCREEN) * ((1.0f - WINDOW_DEFAULT_WINDOWMODE_RATE_HEIGHT) * 0.33f)),		// ウィンドウ位置(Y)
		(int)(WINDOW_DEFAULT_SIZE_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),										// ウィンドウサイズ(X)
		(int)(WINDOW_DEFAULT_SIZE_HEIGHT + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),	// ウィンドウサイズ(Y)
		NULL,
		NULL,
		hInstance,
		NULL);

	//ShowCursor(g_IsMoveCursor);

	// ゲームを初期化
	Manager::Init(hInstance);

	// ウィンドウを表示
	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);

	// タイマーの解像度を指定(ミリ秒)
	timeBeginPeriod(1);

	// 計測用変数初期化
	DWORD dwExecLastTime = timeGetTime();
	DWORD dwCurrentTime = 0;
#ifdef _DEBUG
	strcpy(g_DebugStr, g_WINDOW_NAME);
	DWORD dwFPSLastTime = dwExecLastTime;
	int dwFrameCount = 0;
#endif

	MSG msg;
	while (1)
	{
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else //if (!g_IsSleep)
		{
			// 経過時間を更新
			dwCurrentTime = timeGetTime();

			// 1/60秒が経過したら更新・描画を実行する
			if ((dwCurrentTime - dwExecLastTime) >= (1000.0f / 60))
			{
				dwExecLastTime = dwCurrentTime;
#ifdef _DEBUG
				dwFrameCount++;
#endif
				//if (!g_IsMoveCursor)
				//{
				//	D3DXVECTOR2 pos = GetWindowPosition();
				//	D3DXVECTOR2 size = GetWindowSize();
				//	SetCursorPos((int)(pos.x + size.x * 0.5f), (int)(pos.y + size.y * 0.5f));
				//}
				// 更新
				Manager::Update();
				// 描画
				Manager::Draw();
			}
#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する	
			if ((dwCurrentTime - dwFPSLastTime) >= 1000.0f)
			{
				g_CountFPS = dwFrameCount;
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
				wsprintf(g_DebugStr, g_WINDOW_NAME);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(g_Window, g_DebugStr);
			}
#endif
		}
	}

	timeEndPeriod(1);

	UnregisterClass(g_CLASS_NAME, wcex.hInstance);

	Manager::Uninit();
	_CrtDumpMemoryLeaks();
	return (int)msg.wParam;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			// 終了
			DestroyWindow(hWnd);
			break; 
		default: break;
		}
		break;
	default: break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/*******************************************************************************
*	ウィンドウ取得
*******************************************************************************/
HWND GetWindow()
{
	return g_Window;
}

/*******************************************************************************
*	ウィンドウサイズ取得
*******************************************************************************/
D3DXVECTOR2 GetWindowSize()
{
	RECT r;
	GetWindowRect(g_Window, &r);
	D3DXVECTOR2 s = { (float)(r.right - r.left - (GetSystemMetrics(SM_CXDLGFRAME) * 2)),
				(float)(r.bottom - r.top - (GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION))) };
	return s;
}

/*******************************************************************************
*	ウィンドウ位置(左上隅)
*******************************************************************************/
D3DXVECTOR2 GetWindowPosition()
{
	RECT r;
	GetWindowRect(g_Window, &r);
	D3DXVECTOR2 p = { (float)(r.left) + (GetSystemMetrics(SM_CXDLGFRAME)),
					(float)(r.top) + (GetSystemMetrics(SM_CYDLGFRAME) + GetSystemMetrics(SM_CYCAPTION)) };
	return p;
}

/*******************************************************************************
*	この画面がアクティブかどうか
*******************************************************************************/
bool GetIsWindowActive()
{
	HWND hWnd = GetActiveWindow();
	return g_Window == hWnd;
}

/*******************************************************************************
*	ウィンドウキャプション取得
*******************************************************************************/
const char* GetWindowName()
{
	return g_WINDOW_NAME;
}
