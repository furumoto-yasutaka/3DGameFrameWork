/*******************************************************************************
*
*	タイトル：	システム系コンポーネント基底クラス	[ systemComponent.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "systemComponent.h"
#include "manager.h"

SystemComponent::SystemComponent(GameObject* AttachObject)
	: Component(AttachObject)
{
	m_ProcGroup = ProcGroup::System;
}
