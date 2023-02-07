/*******************************************************************************
*
*	�^�C�g���F	2D�`��R���|�[�l���g���N���X	[ draw2dComponent.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "component.h"

class Draw2DComponent : public Component
{
protected:
	int m_DrawPriority = 0;		// �`��D��x

public:
	Draw2DComponent(GameObject* AttachObject);

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	int GetDrawPriority() { return m_DrawPriority; }
	void SetDrawPriority(int Priority);
	/////////////////////////////
};
