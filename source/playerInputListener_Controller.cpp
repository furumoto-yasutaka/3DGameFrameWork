/*******************************************************************************
*
*	タイトル：	プレイヤー入力受付スクリプト	[ playerInputListener_Controller.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerInputListener_Controller.h"
#include "input.h"

float PlayerInputListener_Controller::InputMove_Z()
{
	return Input::GetGamePadStickLeftY();
}

float PlayerInputListener_Controller::InputMove_X()
{
	return Input::GetGamePadStickLeftX();
}

bool PlayerInputListener_Controller::InputJump()
{
	return Input::GetGamePadButtonTrigger(XINPUT_GAMEPAD_A);
}

bool PlayerInputListener_Controller::InputAvoid()
{
	return Input::GetGamePadButtonTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER);
}

optional<float> PlayerInputListener_Controller::InputRoll_L()
{
	optional<float> value = Input::GetGamePadLeftTrigger();
	return value > 0.0f ? value : nullopt;
}

optional<float> PlayerInputListener_Controller::InputRoll_R()
{
	optional<float> value = Input::GetGamePadRightTrigger();
	return value > 0.0f ? value : nullopt;
}

bool PlayerInputListener_Controller::InputKnock()
{
	return (Input::GetGamePadButtonRelease(XINPUT_GAMEPAD_LEFT_TRIGGER) ||
		Input::GetGamePadButtonRelease(XINPUT_GAMEPAD_RIGHT_TRIGGER));
}

bool PlayerInputListener_Controller::InputKnockChargeWait()
{
	return (Input::GetGamePadButtonTrigger(XINPUT_GAMEPAD_LEFT_TRIGGER) ||
		Input::GetGamePadButtonTrigger(XINPUT_GAMEPAD_RIGHT_TRIGGER));
}

bool PlayerInputListener_Controller::InputRodScaling()
{
	return Input::GetGamePadButtonTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER);
}

bool PlayerInputListener_Controller::InputRodOpen()
{
	return Input::GetGamePadButtonTrigger(XINPUT_GAMEPAD_X);
}
