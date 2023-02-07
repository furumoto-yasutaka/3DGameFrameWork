/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション棒出しステートクラス	[ playerAnimationState_RodScaling_Extend.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerAnimationState_RodScaling_Extend.h"
#include "gameObject.h"
#include "playerManager.h"

PlayerAnimationState_RodScaling_Extend::~PlayerAnimationState_RodScaling_Extend()
{
	// アニメーションの終了を合図にアクションステートを変更する
	m_Manager->RequestNextActionState(PlayerManager::ActionStateId::None);
}

void PlayerAnimationState_RodScaling_Extend::MainAnimation()
{
	m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::None_Extend);
}
void PlayerAnimationState_RodScaling_Extend::PreEndAnimation()
{
	// 棒を指定の座標まで割合補間で移動する
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
