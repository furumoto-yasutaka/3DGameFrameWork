/*******************************************************************************
*
*	タイトル：	スクリプト系コンポーネント基底クラス	[ scriptComponent.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "scriptComponent.h"
#include "manager.h"

ScriptComponent::ScriptComponent(GameObject* AttachObject)
	: Component(AttachObject)
{
	m_ProcGroup = ProcGroup::Script;
}
