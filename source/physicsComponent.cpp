/*******************************************************************************
*
*	�^�C�g���F	�������Z�n�R���|�[�l���g���N���X	[ physicsComponent.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "physicsComponent.h"
#include "manager.h"

PhysicsComponent::PhysicsComponent(GameObject* AttachObject)
	: Component(AttachObject)
{
	m_ProcGroup = ProcGroup::Physics;
}
