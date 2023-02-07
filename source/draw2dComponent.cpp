/*******************************************************************************
*
*	�^�C�g���F	2D�`��R���|�[�l���g���N���X	[ draw2dComponent.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
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
*	�`��D��x�̐ݒ�
*******************************************************************************/
void Draw2DComponent::SetDrawPriority(int Priority)
{
	m_DrawPriority = Priority;
	Manager::GetScene()->SortDraw2DComponentList();
}
