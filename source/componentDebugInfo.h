/*******************************************************************************
*
*	タイトル：	コンポーネントデバッグ情報管理基底クラス	[ componentDebugInfo.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

class ComponentDebugInfo
{
public:
	virtual void Draw() {}
};
