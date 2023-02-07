/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション小範囲右回転ステートクラス	[ playerAnimationState_ShortRoll_Right.cpp ]
*
*	作成者：	古本 泰隆
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
