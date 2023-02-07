/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション中範囲左回転ステートクラス	[ playerAnimationState_Roll_Left.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerAnimationState_Roll_Left.h"
#include "playerManager.h"
#include "gameObject.h"
#include "camera.h"

PlayerAnimationState_Roll_Left::~PlayerAnimationState_Roll_Left()
{
	// アニメーションの終了を合図にアクションステートを変更する
	m_Manager->RequestNextActionState(PlayerManager::ActionStateId::None);
}

void PlayerAnimationState_Roll_Left::MainAnimation()
{
	MainScaleChange();
	MainRodRotate({ 0.0f, -1.0f, 0.0f });

	if (m_IsEndRotate && m_IsEndScaling)
	{
		m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::None_Extend);
		m_IsEndRotate = false;
		m_IsEndScaling = false;
	}
}
void PlayerAnimationState_Roll_Left::PreEndAnimation()
{
	PreEndScaleChange();
	PreEndRodRotate();

	if (m_IsEndRotate && m_IsEndScaling)
	{
		End();
	}
}
