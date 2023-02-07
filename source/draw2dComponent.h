/*******************************************************************************
*
*	タイトル：	2D描画コンポーネント基底クラス	[ draw2dComponent.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "component.h"

class Draw2DComponent : public Component
{
protected:
	int m_DrawPriority = 0;		// 描画優先度

public:
	Draw2DComponent(GameObject* AttachObject);

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	int GetDrawPriority() { return m_DrawPriority; }
	void SetDrawPriority(int Priority);
	/////////////////////////////
};
