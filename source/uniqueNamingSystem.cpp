/*******************************************************************************
*
*	�^�C�g���F	��Ӗ��̐����p�ÓI�N���X	[ uniqueNamingSystem.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
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
*	�����̌��E���ɒB�����ꍇ�̃G���[����
*******************************************************************************/
void UniqueNamingSystem::CreateLimitError()
{
	string str = string("�����ł̐��������E�ɒB���܂���\n") + "�������F" + to_string(m_MAX_NAME_COUNT);
	MessageBox(GetWindow(),
		TEXT(str.c_str()),
		TEXT("uniqueNamingSystem:Error"),
		MB_OK | MB_ICONERROR);
}