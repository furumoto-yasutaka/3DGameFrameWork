/*******************************************************************************
*
*	�^�C�g���F	�X�N���v�g�n�R���|�[�l���g���N���X	[ scriptComponent.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "scriptComponent.h"
#include "manager.h"

ScriptComponent::ScriptComponent(GameObject* AttachObject)
	: Component(AttachObject)
{
	m_ProcGroup = ProcGroup::Script;
}
