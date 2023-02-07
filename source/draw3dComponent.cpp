/*******************************************************************************
*
*	タイトル：	3D描画コンポーネント基底クラス	[ draw3dComponent.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "draw3dComponent.h"
#include "manager.h"

Draw3DComponent::Draw3DComponent(GameObject* AttachObject)
	: Component(AttachObject)
{
	m_ProcGroup = ProcGroup::Draw3D;
}
