/*******************************************************************************
*
*	�^�C�g���F	3D�`��R���|�[�l���g���N���X	[ draw3dComponent.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "draw3dComponent.h"
#include "manager.h"

Draw3DComponent::Draw3DComponent(GameObject* AttachObject)
	: Component(AttachObject)
{
	m_ProcGroup = ProcGroup::Draw3D;
}
