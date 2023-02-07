/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�A�j���[�V�������͈͍���]�X�e�[�g�N���X	[ playerAnimationState_ShortRoll_Left.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "playerAnimationState_ShortRoll_Left.h"
#include "playerManager.h"
#include "gameObject.h"
#include "camera.h"
#include "collisionContactRecorder_PlayerAttack.h"

void PlayerAnimationState_ShortRoll_Left::MainAnimation()
{
	MainScaleChange();

	MainRodRotate({ 0.0f, -1.0f, 0.0f });
}
void PlayerAnimationState_ShortRoll_Left::PreEndAnimation()
{
	if (!m_IsEndScaling)
	{
		PreEndScaleChange();
	}

	if (!m_IsEndRotate)
	{
		PreEndRodRotate(true, { 0.0f, -1.0f, 0.0f });
	}

	if (m_IsEndRotate && m_IsEndScaling)
	{
		End();
	}
}
