/*******************************************************************************
*
*	�^�C�g���F	�C���X�y�N�^�[�E�B���h�E�N���X	[ debugWindow.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "debugWindow.h"
#include "gameObject.h"
#include "math.h"
#include "debugWindow_Hierarchy.h"
#include "componentDebugInfo.h"

#include <list>

class DebugWindow_Inspector : public DebugWindow
{
public:
	DebugWindow_Inspector(string Name, bool IsActive = true)
		: DebugWindow(Name, IsActive) {}

	void Draw() override
	{
		ImGui::SetNextWindowSize(m_WindowSize, ImGuiCond_Once);

		// ���W�Œ�ݒ�ŃE�B���h�E��\��
		ImGui::Begin(m_WindowName.c_str(), ((bool*)0), ImGuiWindowFlags_NoMove);

		GameObject* selectedObj = DebugWindow_Hierarchy::GetSelectedObject();

		DrawObjectInfo(selectedObj);

		ImGui::End();
	}

	// �q�G�����L�[�E�B���h�E�őI����ԂɂȂ��Ă���I�u�W�F�N�g��\��
	void DrawObjectInfo(GameObject* obj)
	{
		D3DXVECTOR3 r = Math::QuaternionToEulerAngle(obj->m_LocalRotation);
		r = {
			Math::RadianToDegree(r.x),
			Math::RadianToDegree(r.y),
			Math::RadianToDegree(r.z),
		};

		float pos[3] = { obj->m_LocalPosition.x, obj->m_LocalPosition.y, obj->m_LocalPosition.z };
		float rot[3] = { r.x, r.y, r.z };
		float scl[3] = { obj->m_LocalScale.x, obj->m_LocalScale.y, obj->m_LocalScale.z };

		ImGui::Text("IsActive : %s", obj->GetActive() ? "true" : "false");
		ImGui::Text("IsStatic : %s", obj->GetStatic() ? "true" : "false");
		ImGui::DragFloat3("Position", pos, 0.0f, 0.0f, 0.0f, "%.3f", ImGuiSliderFlags_NoInput);
		ImGui::DragFloat3("Rotation", rot, 0.0f, 0.0f, 0.0f, "%.3f", ImGuiSliderFlags_NoInput);
		ImGui::DragFloat3("Scale", scl, 0.0f, 0.0f, 0.0f, "%.3f", ImGuiSliderFlags_NoInput);

		for (Component* c : obj->GetComponentAll())
		{
			ComponentDebugInfo* info = c->GetComponentDebugInfo();
			if (info)
			{
				info->Draw();
			}
		}
	}
};
