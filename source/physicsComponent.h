/*******************************************************************************
*
*	タイトル：	物理演算系コンポーネント基底クラス	[ physicsComponent.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "component.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(GameObject* AttachObject);
};
