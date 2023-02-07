/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション小範囲左回転ステートクラス	[ playerAnimationState_ShortRoll_Left.cpp ]
*
*	作成者：	古本 泰隆
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
