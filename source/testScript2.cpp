/*******************************************************************************
*
*	タイトル：	テスト用コンポーネント	[ testScript2.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "testScript2.h"
#include "gameObject.h"
#include "input.h"
#include "manager.h"
#include "scene.h"
#include "thirdPersonCamera.h"

void TestScript2::Init()
{

}

void TestScript2::Update()
{
	//float speed = 0.01f;

	//if (Input::GetKeyboardPress(DIK_I))
	//{
	//	m_AttachObject->m_LocalPosition += m_AttachObject->GetUp() * speed;
	//}
	//if (Input::GetKeyboardPress(DIK_K))
	//{
	//	m_AttachObject->m_LocalPosition -= m_AttachObject->GetUp() * speed;
	//}
	//if (Input::GetKeyboardPress(DIK_J))
	//{
	//	m_AttachObject->m_LocalPosition -= m_AttachObject->GetRight() * speed;
	//}
	//if (Input::GetKeyboardPress(DIK_L))
	//{
	//	m_AttachObject->m_LocalPosition += m_AttachObject->GetRight() * speed;
	//}

	//if (Input::GetKeyboardPress(DIK_F))
	//{
	//	m_AttachObject->m_LocalRotation *= Math::AxisRotation_Degree(D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.5f);
	//}
	//if (Input::GetKeyboardPress(DIK_G))
	//{
	//	m_AttachObject->m_LocalRotation *= Math::AxisRotation_Degree(D3DXVECTOR3(0.0f, 1.0f, 0.0f), 0.5f);
	//}
	//if (Input::GetKeyboardPress(DIK_H))
	//{
	//	m_AttachObject->m_LocalRotation *= Math::AxisRotation_Degree(D3DXVECTOR3(1.0f, 0.0f, 1.0f), 0.5f);
	//}

	m_AttachObject->m_LocalRotation *= Math::AxisRotation_Degree(D3DXVECTOR3(1.0f, 0.0f, 0.0f), 0.8f);
}
