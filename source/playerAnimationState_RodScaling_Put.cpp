/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�A�j���[�V�����_�[�߃X�e�[�g�N���X	[ playerAnimationState_RodScaling_Put.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "playerAnimationState_RodScaling_Put.h"
#include "gameObject.h"
#include "playerManager.h"

PlayerAnimationState_RodScaling_Put::~PlayerAnimationState_RodScaling_Put()
{
	// �A�j���[�V�����̏I�������}�ɃA�N�V�����X�e�[�g��ύX����
	m_Manager->RequestNextActionState(PlayerManager::ActionStateId::None);
}

void PlayerAnimationState_RodScaling_Put::MainAnimation()
{
	m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::None);
}
void PlayerAnimationState_RodScaling_Put::PreEndAnimation()
{
	// �_���w��̍��W�܂Ŋ�����Ԃňړ�����
	GameObject* rod = m_Manager->GetModelParts(PlayerManager::ModelPartsId::Rod);
	float amount;

	if (m_PUT_LENGTH - m_PutLength <= m_PUT_THRESHOLD)
	{
		amount = m_PUT_LENGTH - m_PutLength;

		End();
	}
	else
	{
		amount = (m_PUT_LENGTH - m_PutLength) * m_PUT_INTERPOLATION_SPEED;
	}

	m_PutLength += amount;
	rod->m_LocalPosition.z += amount;
}
