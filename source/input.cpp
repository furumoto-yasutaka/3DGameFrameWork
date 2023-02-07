/*******************************************************************************
*
*	タイトル：	キー入力用静的クラス	[ input.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "input.h"

void Input::Init(HINSTANCE hInstance)
{
	//ShowCursor(false);

	HRESULT hr;
	HWND hWnd = GetWindow();

	// DirectInputオブジェクトの作成
	hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
							IID_IDirectInput8, (void**)&m_DInput, NULL);
	if (FAILED(hr))
	{
		MessageBox(hWnd,
			TEXT("DirectInputオブジェクトの作成に失敗しました"),
			TEXT("input:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	InitKeyboard(hWnd);
	InitMouse(hWnd);
	InitGamePad();
}

void Input::Uninit()
{
	UninitKeyboard();
	UninitMouse();
	UninitGamePad();

	if (m_DInput)
	{
		m_DInput->Release();
		m_DInput = NULL;
	}
}

void Input::Update()
{
	UpdateKeyboard();
	UpdateMouse();
	UpdateGamePad();
}


void Input::InitKeyboard(HWND hWnd)
{
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = m_DInput->CreateDevice(GUID_SysKeyboard, &m_DIDevKeyboard, NULL);
	if (FAILED(hr) || m_DIDevKeyboard == NULL)
	{
		MessageBox(hWnd,
			TEXT("キーボードが見つかりませんでした"),
			TEXT("input:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// データフォーマットを設定
	hr = m_DIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(hWnd,
			TEXT("キーボードのデータフォーマットを設定できませんでした"),
			TEXT("input:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = m_DIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(hWnd,
			TEXT("キーボードの協調モード設定に失敗しました"),
			TEXT("input:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	hr = m_DIDevKeyboard->Acquire();
}
void Input::InitMouse(HWND hWnd)
{
	HRESULT hr;

	// デバイス作成
	hr = m_DInput->CreateDevice(GUID_SysMouse, &m_DIDevMouse, NULL);
	if (FAILED(hr) || m_DIDevMouse == NULL)
	{
		MessageBox(hWnd,
			TEXT("マウスが見つかりませんでした"),
			TEXT("input:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// データフォーマット設定
	hr = m_DIDevMouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr))
	{
		MessageBox(hWnd,
			TEXT("マウスのデータフォーマットを設定できませんでした"),
			TEXT("input:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// 他のアプリと協調モードに設定
	hr = m_DIDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(hWnd,
			TEXT("マウスの協調モード設定に失敗しました"),
			TEXT("input:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// デバイスの設定
	DIPROPDWORD prop;
	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = DIPROPAXISMODE_REL;		// マウスの移動値　相対値

	hr = m_DIDevMouse->SetProperty(DIPROP_AXISMODE, &prop.diph);
	if (FAILED(hr))
	{
		MessageBox(hWnd,
			TEXT("マウスの設定に失敗しました"),
			TEXT("input:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// アクセス権を得る
	m_DIDevMouse->Acquire();
}
void Input::InitGamePad()
{
	XInputEnable(true);
}


void Input::UninitKeyboard()
{
	m_DIDevKeyboard->Unacquire();
	m_DIDevKeyboard->Release();
	m_DIDevKeyboard = NULL;
}
void Input::UninitMouse()
{
	m_DIDevMouse->Unacquire();
	m_DIDevMouse->Release();
	m_DIDevMouse = NULL;
}
void Input::UninitGamePad()
{
	//バイブレーション停止
	for (DWORD i = 0; i < m_GAME_PAD_MAX; i++)
	{
		XInputSetState(i, &m_GamePadVibration[i]);
	}

	XInputEnable(false);
}


void Input::UpdateKeyboard()
{
	// 前回のデータを保存
	memcpy(m_OldKeyState, m_KeyState, m_NUM_KEY_MAX);

	HRESULT hr;
	// デバイスからデータを取得
	hr = m_DIDevKeyboard->GetDeviceState(sizeof(m_KeyState), m_KeyState);
	if (FAILED(hr))
	{
		//MessageBox(GetWindow(),
		//	TEXT("キーボードからの情報取得に失敗しました\n再度アクセスを試みます"),
		//	TEXT("input:Error"),
		//	MB_OK | MB_ICONERROR);
		// キーボードへのアクセス権の取得を再度試みる
		m_DIDevKeyboard->Acquire();
	}
}
void Input::UpdateMouse()
{
	// 前回の値保存
	m_OldMouseState = m_MouseState;

	HRESULT hr;
	// データ取得
	hr = m_DIDevMouse->GetDeviceState(sizeof(m_MouseState), &m_MouseState);
	if (FAILED(hr))
	{
		//MessageBox(GetWindow(),
		//	TEXT("マウスからの情報取得に失敗しました\n再度アクセスを試みます"),
		//	TEXT("input:Error"),
		//	MB_OK | MB_ICONERROR);
		// マウスへのアクセス権の取得を再度試みる
		hr = m_DIDevMouse->Acquire();
	}
}
void Input::UpdateGamePad()
{
	for (DWORD i = 0; i < m_GAME_PAD_MAX; i++)
	{
		XInputSetState(i, &m_GamePadVibration[i]);

		m_OldGamePadState[i] = m_GamePadState[i];

		//正常：ERROR_SUCCESS　0
		//接続無し：ERROR_DEVICE_NOT_CONNECTED 1167
		DWORD result;
		result = XInputGetState(i, &m_GamePadState[i]);

		//Lスティックのデッドゾーン設定
		if (fabs(m_GamePadState[i].Gamepad.sThumbLX) < m_STICK_DEADZONE &&
			fabs(m_GamePadState[i].Gamepad.sThumbLY) < m_STICK_DEADZONE)
		{
			m_GamePadState[i].Gamepad.sThumbLX = 0;
			m_GamePadState[i].Gamepad.sThumbLY = 0;
		}
		//Rスティックのデッドゾーン設定
		if (fabs(m_GamePadState[i].Gamepad.sThumbRX) < m_STICK_DEADZONE &&
			fabs(m_GamePadState[i].Gamepad.sThumbRY) < m_STICK_DEADZONE)
		{
			m_GamePadState[i].Gamepad.sThumbRX = 0;
			m_GamePadState[i].Gamepad.sThumbRY = 0;
		}

		if (m_GamePadState[i].Gamepad.bLeftTrigger > m_TRIGGER_DEADZONE)
		{
			m_GamePadState[i].Gamepad.wButtons |= XINPUT_GAMEPAD_LEFT_TRIGGER;
		}
		if (m_GamePadState[i].Gamepad.bRightTrigger > m_TRIGGER_DEADZONE)
		{
			m_GamePadState[i].Gamepad.wButtons |= XINPUT_GAMEPAD_RIGHT_TRIGGER;
		}
	}
}

//-------------------------------------------------------------------------------------- キーボード

/*******************************************************************************
*	キーボード　キーが押された瞬間
*******************************************************************************/
bool Input::GetKeyboardTrigger(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80);
}
/*******************************************************************************
*	キーボード　キーが押されているか
*******************************************************************************/
bool Input::GetKeyboardPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}
/*******************************************************************************
*	キーボード　キーが離れた瞬間
*******************************************************************************/
bool Input::GetKeyboardRelease(BYTE KeyCode)
{
	return !(m_KeyState[KeyCode] & 0x80) && (m_OldKeyState[KeyCode] & 0x80);
}



//-------------------------------------------------------------------------------------- マウス

/*******************************************************************************
*	マウス　ボタンが押された瞬間
*******************************************************************************/
bool Input::GetMouseTrigger(MouseButton Button)
{
	return (m_MouseState.rgbButtons[(int)Button] & 0x80) && !(m_OldMouseState.rgbButtons[(int)Button] & 0x80);
}
/*******************************************************************************
*	マウス　ボタンが押されているか
*******************************************************************************/
bool Input::GetMousePress(MouseButton Button)
{
	return (m_MouseState.rgbButtons[(int)Button] & 0x80);
}
/*******************************************************************************
*	マウス　ボタンが離れた瞬間
*******************************************************************************/
bool Input::GetMouseRelease(MouseButton Button)
{
	return !(m_MouseState.rgbButtons[(int)Button] & 0x80) && (m_OldMouseState.rgbButtons[(int)Button] & 0x80);
}

/*******************************************************************************
*	マウス　左右の移動量
*******************************************************************************/
long Input::GetMouseMoveX()
{
	return m_MouseState.lX;
}
/*******************************************************************************
*	マウス　上下の移動量
*******************************************************************************/
long Input::GetMouseMoveY()
{
	return m_MouseState.lY;
}
/*******************************************************************************
*	マウス　マウスホイール
*******************************************************************************/
long Input::GetMouseMoveZ()
{
	return m_MouseState.lZ;
}

/*******************************************************************************
*	マウス　カーソル位置(クライアント座標)
*******************************************************************************/
D3DXVECTOR2 Input::GetMouseCursorClient()
{
	POINT p;
	D3DXVECTOR2 windowSize = GetWindowSize();
	GetCursorPos(&p);
	ScreenToClient(GetWindow(), &p);
	D3DXVECTOR2 pos = { (float)p.x, (float)p.y };
	pos.x *= (float)WINDOW_RESOLUTION_WIDTH / windowSize.x;
	pos.y *= (float)WINDOW_RESOLUTION_HEIGHT / windowSize.y;
	return pos;
}

/*******************************************************************************
*	マウス　カーソル位置(スクリーン座標)
*******************************************************************************/
D3DXVECTOR2 Input::GetMouseCursorScreen()
{
	POINT p;
	GetCursorPos(&p);
	D3DXVECTOR2 pos = { (float)p.x, (float)p.y };
	return pos;
}



//-------------------------------------------------------------------------------------- コントローラー

/*******************************************************************************
*	コントローラー　ボタンが押された瞬間
*******************************************************************************/
bool Input::GetGamePadButtonTrigger(DWORD button, int padNo)
{
	return (button & m_GamePadState[padNo].Gamepad.wButtons) && !(button & m_OldGamePadState[padNo].Gamepad.wButtons);
}
/*******************************************************************************
*	コントローラー　ボタンが押されているか
*******************************************************************************/
bool Input::GetGamePadButtonPress(DWORD button, int padNo)
{
	return (button & m_GamePadState[padNo].Gamepad.wButtons);
}
/*******************************************************************************
*	コントローラー　ボタンが離れた瞬間
*******************************************************************************/
bool Input::GetGamePadButtonRelease(DWORD button, int padNo)
{
	return !(button & m_GamePadState[padNo].Gamepad.wButtons) && (button & m_OldGamePadState[padNo].Gamepad.wButtons);
}

/*******************************************************************************
*	コントローラー　左スティック(左右)
*******************************************************************************/
float Input::GetGamePadStickLeftX(int padNo)
{
	return m_GamePadState[padNo].Gamepad.sThumbLX * m_STICK_DIV;
}
/*******************************************************************************
*	コントローラー　左スティック(上下)
*******************************************************************************/
float Input::GetGamePadStickLeftY(int padNo)
{
	return m_GamePadState[padNo].Gamepad.sThumbLY * m_STICK_DIV;
}
/*******************************************************************************
*	コントローラー　右スティック(左右)
*******************************************************************************/
float Input::GetGamePadStickRightX(int padNo)
{
	return m_GamePadState[padNo].Gamepad.sThumbRX * m_STICK_DIV;
}
/*******************************************************************************
*	コントローラー　右スティック(上下)
*******************************************************************************/
float Input::GetGamePadStickRightY(int padNo)
{
	return m_GamePadState[padNo].Gamepad.sThumbRY * m_STICK_DIV;
}

/*******************************************************************************
*	コントローラー　左トリガー
*******************************************************************************/
float Input::GetGamePadLeftTrigger(int padNo)
{
	return m_GamePadState[padNo].Gamepad.bLeftTrigger * m_TRIGGER_DIV;
}
/*******************************************************************************
*	コントローラー　右トリガー
*******************************************************************************/
float Input::GetGamePadRightTrigger(int padNo)
{
	return m_GamePadState[padNo].Gamepad.bRightTrigger * m_TRIGGER_DIV;
}

/*******************************************************************************
*	コントローラー　左バイブレーション設定
*******************************************************************************/
void Input::SetGamePadLeftVibration(int speed, int padNo)
{
	speed %= 256;
	m_GamePadVibration[padNo].wLeftMotorSpeed = ((speed + 1) * 256) - 1;
}
/*******************************************************************************
*	コントローラー　右バイブレーション設定
*******************************************************************************/
void Input::SetGamePadRightVibration(int speed, int padNo)
{
	speed %= 256;
	m_GamePadVibration[padNo].wRightMotorSpeed = ((speed + 1) * 256) - 1;
}
/*******************************************************************************
*	コントローラー　両サイドバイブレーション設定
*******************************************************************************/
void Input::SetGamePadVibration(int speed, int padNo)
{
	speed %= 256;
	m_GamePadVibration[padNo].wLeftMotorSpeed = ((speed + 1) * 256) - 1;
	m_GamePadVibration[padNo].wRightMotorSpeed = ((speed + 1) * 256) - 1;
}
/*******************************************************************************
*	コントローラー　バイブレーション停止
*******************************************************************************/
void Input::StopGamePadVibration(int padNo)
{
	m_GamePadVibration[padNo].wLeftMotorSpeed = 0;
	m_GamePadVibration[padNo].wRightMotorSpeed = 0;
}
