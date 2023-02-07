/*******************************************************************************
*
*	タイトル：	メイン	[ main.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#define NOMINMAX

#pragma warning(push)
#pragma warning(disable:4005)

#include "dinput.h"
#include "mmsystem.h"
#include "math.h"

#include <dwrite.h>
#include <D2D1.h>
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <d3d11.h>
#include <d3dx9.h>
#include <d3dcompiler.h>
#include <d3dx11.h>

#pragma warning(pop)

#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "dwrite.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "bcrypt.lib")

using namespace std;

//---------------------------------------
// CRTによるメモリリークチェック用
//---------------------------------------
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

//---------------------------------------
// マクロ定義
//---------------------------------------
#define WINDOW_DEFAULT_WINDOWMODE_RATE_WIDTH	(0.8f)	// ウィンドウモード時のスクリーンサイズ倍率(X)(初期値)
#define WINDOW_DEFAULT_WINDOWMODE_RATE_HEIGHT	(0.8f)	// ウィンドウモード時のスクリーンサイズ倍率(Y)(初期値)
#define WINDOW_DEFAULT_SIZE_WIDTH	(float)(GetSystemMetrics(SM_CXSCREEN) * WINDOW_DEFAULT_WINDOWMODE_RATE_WIDTH)	// 画面サイズ(X)
#define WINDOW_DEFAULT_SIZE_HEIGHT	(float)(GetSystemMetrics(SM_CYSCREEN) * WINDOW_DEFAULT_WINDOWMODE_RATE_HEIGHT)	// 画面サイズ(Y)

#define WINDOW_RESOLUTION_WIDTH			((float)(GetSystemMetrics(SM_CXSCREEN) * WINDOW_DEFAULT_WINDOWMODE_RATE_WIDTH))	// 画面解像度(X)
#define WINDOW_RESOLUTION_HEIGHT		((float)(GetSystemMetrics(SM_CYSCREEN) * WINDOW_DEFAULT_WINDOWMODE_RATE_HEIGHT))	// 画面解像度(Y)
#define WINDOW_RESOLUTION_RATE_WIDTH	(WINDOW_RESOLUTION_WIDTH / GetSystemMetrics(SM_CXSCREEN))
#define WINDOW_RESOLUTION_RATE_HEIGHT	(WINDOW_RESOLUTION_HEIGHT / GetSystemMetrics(SM_CYSCREEN))

// ウィンドウ取得
HWND GetWindow();

// ウィンドウサイズ取得
D3DXVECTOR2 GetWindowSize();

// ウィンドウ位置(左上隅)
D3DXVECTOR2 GetWindowPosition();

// この画面がアクティブかどうか
bool GetIsWindowActive();

// ウィンドウキャプション取得
const char* GetWindowName();
