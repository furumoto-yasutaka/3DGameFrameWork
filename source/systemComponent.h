/*******************************************************************************
*
*	タイトル：	システム系コンポーネント基底クラス	[ systemComponent.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "component.h"

class SystemComponent : public Component
{
public:
	SystemComponent(GameObject* AttachObject);
};
