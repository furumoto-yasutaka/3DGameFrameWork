/*******************************************************************************
*
*	タイトル：	プレイヤー入力受付スクリプト	[ playerInputListener_MouseKeyboard.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerInputListener_MouseKeyboard.h"
#include "input.h"
#include "time.h"

float PlayerInputListener_MouseKeyboard::InputMove_Z()
{
	bool forward = Input::GetKeyboardPress(DIK_W);
	bool back = Input::GetKeyboardPress(DIK_S);

	return (forward ? 1.0f : 0.0f + back ? -1.0f : 0.0f);
}

float PlayerInputListener_MouseKeyboard::InputMove_X()
{
	bool left = Input::GetKeyboardPress(DIK_A);
	bool right = Input::GetKeyboardPress(DIK_D);

	return (left ? -1.0f : 0.0f + right ? 1.0f : 0.0f);
}

bool PlayerInputListener_MouseKeyboard::InputJump()
{
	return Input::GetKeyboardTrigger(DIK_SPACE);
}

bool PlayerInputListener_MouseKeyboard::InputAvoid()
{
	return Input::GetKeyboardTrigger(DIK_LSHIFT);
}

optional<float> PlayerInputListener_MouseKeyboard::InputRoll_L()
{
	return Input::GetMousePress(Input::MouseButton::Left) ? 1.0f : (optional<float>)nullopt;
}

optional<float> PlayerInputListener_MouseKeyboard::InputRoll_R()
{
	return Input::GetMousePress(Input::MouseButton::Right) ? 1.0f : (optional<float>)nullopt;
}

bool PlayerInputListener_MouseKeyboard::InputKnock()
{
	return Input::GetMouseRelease(Input::MouseButton::Left) ||
		Input::GetMouseRelease(Input::MouseButton::Right);
}

bool PlayerInputListener_MouseKeyboard::InputKnockChargeWait()
{
	return Input::GetMouseTrigger(Input::MouseButton::Left) ||
		Input::GetMouseTrigger(Input::MouseButton::Right);
}

bool PlayerInputListener_MouseKeyboard::InputRodScaling()
{
	return Input::GetKeyboardTrigger(DIK_E);
}

bool PlayerInputListener_MouseKeyboard::InputRodOpen()
{
	return Input::GetKeyboardTrigger(DIK_F);
}
