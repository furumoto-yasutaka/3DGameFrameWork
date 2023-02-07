/*******************************************************************************
*
*	タイトル：	テスト用コンポーネント	[ testScript.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "testScript.h"
#include "gameObject.h"
#include "input.h"
#include "manager.h"
#include "scene.h"
#include "thirdPersonCamera.h"

void TestScript::Init()
{
	//m_AttachObject->m_LocalPosition = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
}

void TestScript::Update()
{
	/*D3DXMATRIX m;
	D3DXVECTOR3 zero = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 target = Math::Normalize(D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	D3DXVECTOR3 front = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMatrixLookAtLH(&m, &zero, &target, &front);

	D3DXQuaternionRotationMatrix(&m_AttachObject->m_LocalRotation, &m);*/

	//float speed = 0.01f;

	//if (Input::GetKeyboardPress(DIK_UPARROW))
	//{
	//	m_AttachObject->m_LocalPosition += m_AttachObject->GetUp() * speed;
	//}
	//if (Input::GetKeyboardPress(DIK_DOWNARROW))
	//{
	//	m_AttachObject->m_LocalPosition -= m_AttachObject->GetUp() * speed;
	//}
	//if (Input::GetKeyboardPress(DIK_LEFTARROW))
	//{
	//	m_AttachObject->m_LocalPosition -= m_AttachObject->GetRight() * speed;
	//}
	//if (Input::GetKeyboardPress(DIK_RIGHTARROW))
	//{
	//	m_AttachObject->m_LocalPosition += m_AttachObject->GetRight() * speed;
	//}

	//if (Input::GetKeyboardPress(DIK_R))
	//{
	//	m_AttachObject->m_LocalRotation *= Math::AxisRotation_Degree(D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.5f);
	//}
	//if (Input::GetKeyboardPress(DIK_T))
	//{
	//	m_AttachObject->m_LocalRotation *= Math::AxisRotation_Degree(D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.5f);
	//}
	//if (Input::GetKeyboardPress(DIK_Y))
	//{
	//	m_AttachObject->m_LocalRotation *= Math::AxisRotation_Degree(D3DXVECTOR3(1.0f, 0.0f, 1.0f), 0.5f);
	//}

	m_AttachObject->m_LocalRotation *= Math::AxisRotation_Degree(D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.5f);
}
