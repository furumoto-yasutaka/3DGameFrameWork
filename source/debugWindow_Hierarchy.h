/*******************************************************************************
*
*	�^�C�g���F	�q�G�����L�[�E�B���h�E�N���X	[ debugWindow.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "debugWindow.h"
#include "gameObject.h"
#include "math.h"

#include <list>
#include <vector>

class DebugWindow_Hierarchy : public DebugWindow
{
private:
	static inline vector<GameObject*> m_ObjList;
	static inline int m_DigitNum = 0;
public:
	static inline int m_SelectedObjectId = 0;

public:
	DebugWindow_Hierarchy(string Name, bool IsActive = true)
		: DebugWindow(Name, IsActive) {}

	void Draw() override
	{
		// ���X�g���N���A
		m_ObjList.clear();

		ImGui::SetNextWindowSize(m_WindowSize, ImGuiCond_Once);

		// ���W�Œ�ݒ�ŃE�B���h�E��\��
		ImGui::Begin(m_WindowName.c_str(), ((bool*)0), ImGuiWindowFlags_NoMove);

		list<GameObject*> objList = Manager::GetScene()->GetAllGameObject();
		CountDigit(objList.size());

		// �`�揈��
		for (GameObject* obj : objList)
		{
			if (!obj->GetParent())
			{
				if (!obj->GetChild(0))
				{// �q�������݂��Ȃ�
					DrawName(obj);
				}
				else
				{// �q�������݂���
					DrawTree(obj);
				}
			}
		}

		ImGui::End();
	}

	// �I�u�W�F�N�g������ő包�������߂�
	void CountDigit(int Num)
	{
		m_DigitNum = 0;

		while (Num != 0)
		{
			Num /= 10;
			m_DigitNum++;
		}
	}

	// �q�����I�u�W�F�N�g��\��
	void DrawTree(GameObject* Obj)
	{
		m_ObjList.push_back(Obj);

		ImGui::RadioButton(CreateNumStr(m_ObjList.size() - 1).c_str(), &m_SelectedObjectId, m_ObjList.size() - 1);
		ImGui::SameLine();

		if (ImGui::TreeNode(Obj->GetName().c_str()))
		{
			for (GameObject* child : Obj->GetChildList())
			{
				if (!child->GetChild(0))
				{// �q�������݂��Ȃ�
					DrawName(child);
				}
				else
				{// �q�������݂���
					DrawTree(child);
				}
			}

			ImGui::TreePop();
		}
		else
		{
			for (GameObject* child : Obj->GetChildList())
			{
				PushChild(child);
			}
		}
	}

	// �q�������Ȃ��I�u�W�F�N�g��\��
	void DrawName(GameObject* Obj)
	{
		m_ObjList.push_back(Obj);

		string str = CreateNumStr(m_ObjList.size() - 1) + "    " + Obj->GetName();
		ImGui::RadioButton(str.c_str(), &m_SelectedObjectId, m_ObjList.size() - 1);
	}

	// �\���Ώۂł͂Ȃ��q�I�u�W�F�N�g���i�[
	void PushChild(GameObject* Obj)
	{
		m_ObjList.push_back(Obj);

		for (GameObject* child : Obj->GetChildList())
		{
			PushChild(child);
		}
	}

	// �ő包�����琔�l�𐶐�
	string CreateNumStr(int Num)
	{
		string result = "";

		for (int i = 0; i < m_DigitNum; i++)
		{
			int n = Num % 10;

			switch (n)
			{
			case 0: result = "0" + result; break;
			case 1: result = "1" + result; break;
			case 2: result = "2" + result; break;
			case 3: result = "3" + result; break;
			case 4: result = "4" + result; break;
			case 5: result = "5" + result; break;
			case 6: result = "6" + result; break;
			case 7: result = "7" + result; break;
			case 8: result = "8" + result; break;
			case 9: result = "9" + result; break;
			}

			Num /= 10;
		}

		return result;
	}

	// �I����Ԃ̃I�u�W�F�N�g�̏����擾
	static inline GameObject* GetSelectedObject()
	{
		return m_ObjList[m_SelectedObjectId];
	}
};