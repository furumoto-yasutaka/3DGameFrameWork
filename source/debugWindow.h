/*******************************************************************************
*
*	�^�C�g���F	�f�o�b�O�E�B���h�E����N���X	[ debugWindow.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "debugManager.h"

class DebugWindow
{
protected:
	int m_WindowId;					// �E�B���h�EID
	string m_WindowName;			// �E�B���h�E��
	bool m_IsActive;				// �E�B���h�E���N�����Ă��邩
	ImVec2 m_WindowSize;			// �E�B���h�E�T�C�Y
	D3DXVECTOR4 m_WindowClearColor;	// �E�B���h�E�̐F

public:
	DebugWindow(string Name, bool IsActive = true)
	{
		// �E�B���h�E��o�^����ID���󂯎��
		m_WindowId = DebugManager::AddWindow(this);

		m_WindowName = Name;
		m_IsActive = IsActive;
		m_WindowSize = ImVec2(200.0f, 300.0f);
		m_WindowClearColor = D3DXVECTOR4(0.45f, 0.55f, 0.60f, 1.00f);
	}
	~DebugWindow()
	{
		DebugManager::DeleteWindow(this);
	}

	virtual void Draw() = 0;

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	string GetName() { return m_WindowName; }

	bool GetIsActive() { return m_IsActive; }
	void SetIsActive(bool IsActive) { m_IsActive = IsActive; }
	/////////////////////////////
};
