/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション棒納めステートクラス	[ playerAnimationState_RodScaling_Put.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerAnimationState_RodScaling_Put.h"
#include "gameObject.h"
#include "playerManager.h"

PlayerAnimationState_RodScaling_Put::~PlayerAnimationState_RodScaling_Put()
{
	// アニメーションの終了を合図にアクションステートを変更する
	m_Manager->RequestNextActionState(PlayerManager::ActionStateId::None);
}

void PlayerAnimationState_RodScaling_Put::MainAnimation()
{
	m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::None);
}
void PlayerAnimationState_RodScaling_Put::PreEndAnimation()
{
	// 棒を指定の座標まで割合補間で移動する
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
