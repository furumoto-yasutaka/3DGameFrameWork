/*******************************************************************************
*
*	タイトル：	一意名称生成用静的クラス	[ uniqueNamingSystem.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "uniqueNamingSystem.h"

void UniqueNamingSystem::Init()
{

}

void UniqueNamingSystem::Uninit()
{

}

/*******************************************************************************
*	生成の限界数に達した場合のエラー処理
*******************************************************************************/
void UniqueNamingSystem::CreateLimitError()
{
	string str = string("同名での生成が限界に達しました\n") + "生成数：" + to_string(m_MAX_NAME_COUNT);
	MessageBox(GetWindow(),
		TEXT(str.c_str()),
		TEXT("uniqueNamingSystem:Error"),
		MB_OK | MB_ICONERROR);
}
