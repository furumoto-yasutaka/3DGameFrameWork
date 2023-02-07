/*******************************************************************************
*
*	タイトル：	キー入力用静的クラス	[ input.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"

#include <XInput.h>

#pragma comment (lib, "xinput.lib")

#define XINPUT_GAMEPAD_LEFT_TRIGGER    0x0400
#define XINPUT_GAMEPAD_RIGHT_TRIGGER   0x0800

class Input
{
public:
	// マウスボタンのキー
	enum class MouseButton
	{
		Left = 0,
		Right,
		Center,
	};

private:
	static inline LPDIRECTINPUT8		m_DInput;	// DirectInputオブジェクトポインタ

	///////////////////////////////
	//　↓↓　キーボード　↓↓　//
	static inline const unsigned int	m_NUM_KEY_MAX = 256;			// キーの種類数
	static inline LPDIRECTINPUTDEVICE8	m_DIDevKeyboard;				// DirectInputデバイスオブジェクトポインタ
	static inline BYTE					m_KeyState[m_NUM_KEY_MAX];		// キー入力情報
	static inline BYTE					m_OldKeyState[m_NUM_KEY_MAX];	// 前フレームのキー入力情報
	///////////////////////////////

	///////////////////////////
	//　↓↓　マウス　↓↓　//
	static inline LPDIRECTINPUTDEVICE8	m_DIDevMouse;		// DirectInputデバイスオブジェクトポインタ
	static inline DIMOUSESTATE2			m_MouseState;		// マウス入力情報
	static inline DIMOUSESTATE2			m_OldMouseState;	// 前フレームのマウス入力情報
	///////////////////////////

	///////////////////////////////////
	//　↓↓　コントローラー　↓↓　//
	static inline const float			m_STICK_DIV = 0.00003051757812f;
	static inline const float			m_TRIGGER_DIV = 0.003921568627f;
	static inline const unsigned int	m_GAME_PAD_MAX = 4;							// コントローラの最大数
	static inline const unsigned int	m_STICK_DEADZONE = 8200;					// スティックの無効ゾーン(各軸の25%)
	static inline const unsigned int	m_TRIGGER_DEADZONE = 64;					// トリガーの無効ゾーン(各軸の25%)
	static inline LPDIRECTINPUTDEVICE8	m_DIDevGamePad[m_GAME_PAD_MAX];				// DirectInputデバイスオブジェクトポインタ
	static inline XINPUT_STATE			m_GamePadState[m_GAME_PAD_MAX];				// コントローラー入力情報(トリガー以外)
	static inline XINPUT_STATE			m_OldGamePadState[m_GAME_PAD_MAX];			// 前フレームのコントローラー入力情報(トリガー以外)
	static inline XINPUT_VIBRATION		m_GamePadVibration[m_GAME_PAD_MAX];			// バイブレーション情報
	///////////////////////////////////
public:
	static void Init(HINSTANCE hInstance);
	static void Uninit();
	static void Update();

	///////////////////////////////
	//　↓↓　キーボード　↓↓　//
	static void InitKeyboard(HWND hWnd);
	static void UninitKeyboard();
	static void UpdateKeyboard();

	static bool GetKeyboardTrigger(BYTE KeyCode);	// キーが押された瞬間
	static bool GetKeyboardPress(BYTE KeyCode);		// キーが押されているか
	static bool GetKeyboardRelease(BYTE KeyCode);	// キーが離れた瞬間
	///////////////////////////////

	///////////////////////////
	//　↓↓　マウス　↓↓　//
	static void InitMouse(HWND hWnd);
	static void UninitMouse();
	static void UpdateMouse();

	static bool GetMouseTrigger(MouseButton Button);	// ボタンが押された瞬間
	static bool GetMousePress(MouseButton Button);		// ボタンが押されているか
	static bool GetMouseRelease(MouseButton Button);	// ボタンが離れた瞬間

	static long GetMouseMoveX();						// 左右の移動量
	static long GetMouseMoveY();						// 上下の移動量
	static long GetMouseMoveZ();						// マウスホイール

	static D3DXVECTOR2 GetMouseCursorClient();				// カーソル位置(クライアント座標)
	static D3DXVECTOR2 GetMouseCursorScreen();				// カーソル位置(スクリーン座標)
	///////////////////////////

	///////////////////////////////////
	//　↓↓　コントローラー　↓↓　//
	static void InitGamePad();
	static void UninitGamePad();
	static void UpdateGamePad();

	static bool GetGamePadButtonTrigger(DWORD button, int padNo = 0);	// ボタンが押された瞬間
	static bool GetGamePadButtonPress(DWORD button, int padNo = 0);		// ボタンが押されているか
	static bool GetGamePadButtonRelease(DWORD button, int padNo = 0);	// ボタンが離れた瞬間
	
	static float GetGamePadStickLeftX(int padNo = 0);					// 左スティック(左右)
	static float GetGamePadStickLeftY(int padNo = 0);					// 左スティック(上下)
	static float GetGamePadStickRightX(int padNo = 0);					// 右スティック(左右)
	static float GetGamePadStickRightY(int padNo = 0);					// 右スティック(上下)

	static float GetGamePadLeftTrigger(int padNo = 0);					// 左トリガー
	static float GetGamePadRightTrigger(int padNo = 0);					// 右トリガー
	
	static void SetGamePadLeftVibration(int speed, int padNo = 0);		// 左バイブレーション設定
	static void SetGamePadRightVibration(int speed, int padNo = 0);		// 右バイブレーション設定
	static void SetGamePadVibration(int speed, int padNo = 0);			// 両サイドバイブレーション設定
	static void StopGamePadVibration(int padNo = 0);					// バイブレーション停止
	///////////////////////////////////
};


// ▼キー一覧

//0x01	DIK_ESCAPE			Esc
//0x02	DIK_1				1
//0x03	DIK_2				2
//0x04	DIK_3				3
//0x05	DIK_4				4
//0x06	DIK_5				5
//0x07	DIK_6				6
//0x08	DIK_7				7
//0x09	DIK_8				8
//0x0A	DIK_9				9
//0x0B	DIK_0				0
//0x0C	DIK_MINUS			-
//0x0D	DIK_EQUALS			=
//0x0E	DIK_BACK			Back Space
//0x0F	DIK_TAB				Tab
//0x10	DIK_Q				Q
//0x11	DIK_W				W
//0x12	DIK_E				E
//0x13	DIK_R				R
//0x14	DIK_T				T
//0x15	DIK_Y				Y
//0x16	DIK_U				U
//0x17	DIK_I				I
//0x18	DIK_O				O
//0x19	DIK_P				P
//0x1A	DIK_LBRACKET		[
//0x1B	DIK_RBRACKET		]
//0x1C	DIK_RETURN			Enter
//0x1D	DIK_LContol			Ctrl(左)
//0x1E	DIK_A				A
//0x1F	DIK_S				S
//0x20	DIK_D				D
//0x21	DIK_F				F
//0x22	DIK_G				G
//0x23	DIK_H				H
//0x24	DIK_J				J
//0x25	DIK_K				K
//0x26	DIK_L				L
//0x27	DIK_SEMICOLON		;
//0x28	DIK_APOSTROPHE		'	
//0x29	DIK_GRAVE			`
//0x2A	DIK_LSHIFT			Shift(左)
//0x2B	DIK_BACKSLASH		\
//0x2C	DIK_Z				Z
//0x2D	DIK_X				X
//0x2E	DIK_C				C
//0x2F	DIK_V				V
//0x30	DIK_B				B
//0x31	DIK_N				N
//0x32	DIK_M				M
//0x33	DIK_COMMA			,
//0x34	DIK_PERIOD			.
//0x35	DIK_SLASH			/
//0x36	DIK_RSHIFT			Shift(右)
//0x37	DIK_MULTIPLY		* (Numpad)
//0x38	DIK_LMENU			Alt(左)
//0x39	DIK_SPACE			Space
//0x3A	DIK_CAPITAL			Caps Lock
//0x3B	DIK_F1				F1
//0x3C	DIK_F2				F2
//0x3D	DIK_F3				F3
//0x3E	DIK_F4				F4
//0x3F	DIK_F5				F5
//0x40	DIK_F6				F6
//0x41	DIK_F7				F7
//0x42	DIK_F8				F8
//0x43	DIK_F9				F9
//0x44	DIK_F10				F10
//0x45	DIK_NUMLOCK			Num Lock
//0x46	DIK_SCROLL			Scroll Lock
//0x47	DIK_NUMPAD7			7 (Numpad)
//0x48	DIK_NUMPAD8			8 (Numpad)
//0x49	DIK_NUMPAD9			9 (Numpad)
//0x4A	DIK_SUBTRACT		- (Numpad)
//0x4B	DIK_NUMPAD4			4 (Numpad)
//0x4C	DIK_NUMPAD5			5 (Numpad)
//0x4D	DIK_NUMPAD6			6 (Numpad)
//0x4E	DIK_ADD				+ (Numpad)
//0x4F	DIK_NUMPAD1			1 (Numpad)
//0x50	DIK_NUMPAD2			2 (Numpad)
//0x51	DIK_NUMPAD3			3 (Numpad)
//0x52	DIK_NUMPAD0			0 (Numpad)
//0x53	DIK_DECIMAL			. (Numpad)
//0x57	DIK_F11				F11
//0x58	DIK_F12				F12
//0x64	DIK_F13				F13	NEC PC - 98
//0x65	DIK_F14				F14	NEC PC - 98
//0x66	DIK_F15				F15	NEC PC - 98
//0x70	DIK_KANA			カナ	日本語キーボード
//0x79	DIK_CONVERT			変換	日本語キーボード
//0x7B	DIK_NOCONVERT		無変換	日本語キーボード
//0x7D	DIK_YEN				¥	日本語キーボード
//0x8D	DIK_NUMPADEQUALS	= NEC PC - 98
//0x90	DIK_CIRCUMFLEX		^ 日本語キーボード
//0x91	DIK_AT				@	NEC PC - 98
//0x92	DIK_COLON			:	NEC PC - 98
//0x93	DIK_UNDERLINE		_	NEC PC - 98
//0x94	DIK_KANJI			漢字	日本語キーボード
//0x95	DIK_STOP			Stop	NEC PC - 98
//0x96	DIK_AX				(Japan AX)
//0x97	DIK_UNLABELED		(J3100)
//0x9C	DIK_NUMPADENTER		Enter(Numpad)
//0x9D	DIK_RCONTROL		Ctrl(右)
//0xB3	DIK_NUMPADCOMMA		, (Numpad)NEC PC - 98
//0xB5	DIK_DIVIDE			/ (Numpad)
//0xB7	DIK_SYSRQ			Sys Rq
//0xB8	DIK_RMENU			Alt(右)
//0xC5	DIK_PAUSE			Pause
//0xC7	DIK_HOME			Home
//0xC8	DIK_UP				↑
//0xC9	DIK_PRIOR			Page Up
//0xCB	DIK_LEFT			←
//0xCD	DIK_RIGHT			→
//0xCF	DIK_END				End
//0xD0	DIK_DOWN			↓
//0xD1	DIK_NEXT			Page Down
//0xD2	DIK_INSERT			Insert
//0xD3	DIK_DELETE			Delete
//0xDB	DIK_LWIN			Windows(左)
//0xDC	DIK_RWIN			Windows(右)
//0xDD	DIK_APPS			Menu
//0xDE	DIK_POWER			Power
//0xDF	DIK_SLEEP			Windows


// XINPUT_GAMEPAD_DPAD_UP			十字キー上
// XINPUT_GAMEPAD_DPAD_DOWN			十字キー下
// XINPUT_GAMEPAD_DPAD_LEFT			十字キー左
// XINPUT_GAMEPAD_DPAD_RIGHT		十字キー右
// XINPUT_GAMEPAD_START
// XINPUT_GAMEPAD_BACK
// XINPUT_GAMEPAD_LEFT_THUMB		Lスティック押し込み
// XINPUT_GAMEPAD_RIGHT_THUMB		Rスティック押し込み
// XINPUT_GAMEPAD_LEFT_SHOULDER		Lボタン
// XINPUT_GAMEPAD_RIGHT_SHOULDER	Rボタン
// XINPUT_GAMEPAD_A
// XINPUT_GAMEPAD_B
// XINPUT_GAMEPAD_X
// XINPUT_GAMEPAD_Y

//スティックの範囲
// X軸 左-32768　右 32767
// Y軸 上 32767　下-32768

//トリガーの範囲
// 0 ～ 255

// バイブレーションの範囲
// 0 ～ 255
