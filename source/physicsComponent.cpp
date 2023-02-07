/*******************************************************************************
*
*	タイトル：	物理演算系コンポーネント基底クラス	[ physicsComponent.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "physicsComponent.h"
#include "manager.h"

PhysicsComponent::PhysicsComponent(GameObject* AttachObject)
	: Component(AttachObject)
{
	m_ProcGroup = ProcGroup::Physics;
}
