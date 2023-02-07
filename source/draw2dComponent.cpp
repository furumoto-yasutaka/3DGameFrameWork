/*******************************************************************************
*
*	タイトル：	2D描画コンポーネント基底クラス	[ draw2dComponent.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "draw2dComponent.h"
#include "manager.h"

Draw2DComponent::Draw2DComponent(GameObject* AttachObject)
	: Component(AttachObject)
{
	m_ProcGroup = ProcGroup::Draw2D;
	Manager::GetScene()->AddDraw2DComponentList(this);
}

/*******************************************************************************
*	描画優先度の設定
*******************************************************************************/
void Draw2DComponent::SetDrawPriority(int Priority)
{
	m_DrawPriority = Priority;
	Manager::GetScene()->SortDraw2DComponentList();
}
