/*******************************************************************************
*
*	タイトル：	3D描画コンポーネント基底クラス	[ draw3dComponent.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "component.h"

class Draw3DComponent : public Component
{
public:
	Draw3DComponent(GameObject* AttachObject);
};
