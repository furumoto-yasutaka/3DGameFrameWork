/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�A�j���[�V�����_�o���X�e�[�g�N���X	[ playerAnimationState_RodScaling_Extend.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "playerAnimationState_RodScaling_Extend.h"
#include "gameObject.h"
#include "playerManager.h"

PlayerAnimationState_RodScaling_Extend::~PlayerAnimationState_RodScaling_Extend()
{
	// �A�j���[�V�����̏I�������}�ɃA�N�V�����X�e�[�g��ύX����
	m_Manager->RequestNextActionState(PlayerManager::ActionStateId::None);
}

void PlayerAnimationState_RodScaling_Extend::MainAnimation()
{
	m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::None_Extend);
}
void PlayerAnimationState_RodScaling_Extend::PreEndAnimation()
{
	// �_���w��̍��W�܂Ŋ�����Ԃňړ�����
	GameObject* rod = m_Manager->GetModelParts(PlayerManager::ModelPartsId::Rod);
	float amount;

	if (m_EXTEND_LENGTH - m_ExtendedLength <= m_EXTEND_THRESHOLD)
	{
		amount = m_EXTEND_LENGTH - m_ExtendedLength;

		End();
	}
	else
	{
		amount = (m_EXTEND_LENGTH - m_ExtendedLength) * m_EXTEND_INTERPOLATION_SPEED;
	}

	m_ExtendedLength += amount;
	rod->m_LocalPosition.z -= amount;
}
