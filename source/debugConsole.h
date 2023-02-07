/*******************************************************************************
*
*	�^�C�g���F	�f�o�b�O��ʗp�ÓI�N���X	[ debugConsole.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"

class DebugConsole
{
private:
	static inline FILE*		m_Out;
	static inline HANDLE	m_Console;		// �R���\�[���n���h��
	static inline COORD		m_CursorPos;	// �J�[�\�����W

public:
	static void Init();
	static void Uninit();
	static void Update();
};
