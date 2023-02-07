/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�����X�e�[�g�N���X	[ playerActionState_None.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_None : public PlayerActionStateBase
{
private:
	// �U������X�e�[�g�ɑJ�ڂ���{�[�_�[
	static inline const float m_TURN_OCCUR_ANGLE = Math::m_PI * 0.51f;

public:
	PlayerActionState_None(PlayerManager* Manager);

	void Update() override;
	void LateUpdate() override;

	void CheckTurnOccur();	// �U������𔭐������邩���f
};
