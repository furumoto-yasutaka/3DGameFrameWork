/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�A�j���[�V�������͈͉E��]�X�e�[�g�N���X	[ playerAnimationState_ShortRoll_Right.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "playerAnimationState_ShortRoll_Right.h"
#include "playerManager.h"
#include "gameObject.h"
#include "camera.h"
#include "collisionContactRecorder_PlayerAttack.h"

void PlayerAnimationState_ShortRoll_Right::MainAnimation()
{
	MainScaleChange();

	MainRodRotate({ 0.0f, 1.0f, 0.0f });
}
void PlayerAnimationState_ShortRoll_Right::PreEndAnimation()
{
	if (!m_IsEndScaling)
	{
		PreEndScaleChange();
	}

	if (!m_IsEndRotate)
	{
		PreEndRodRotate(false, { 0.0f, 1.0f, 0.0f });
	}

	if (m_IsEndRotate && m_IsEndScaling)
	{
		End();
	}
}
