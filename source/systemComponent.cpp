/*******************************************************************************
*
*	�^�C�g���F	�V�X�e���n�R���|�[�l���g���N���X	[ systemComponent.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "systemComponent.h"
#include "manager.h"

SystemComponent::SystemComponent(GameObject* AttachObject)
	: Component(AttachObject)
{
	m_ProcGroup = ProcGroup::System;
}
