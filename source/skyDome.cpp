/*******************************************************************************
*
*	タイトル：	スカイドーム静的クラス	[ skyDome.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "skyDome.h"
#include "renderer.h"
#include "modelContainer.h"
#include "manager.h"
#include "camera.h"
#include "gameObject.h"

string				SkyDome::m_ModelName = "SkyDome";
Model*				SkyDome::m_Model = NULL;
ID3D11VertexShader* SkyDome::m_VertexShader = NULL;
ID3D11PixelShader*	SkyDome::m_PixelShader = NULL;
ID3D11InputLayout*	SkyDome::m_VertexLayout = NULL;
float				SkyDome::m_Size;

void SkyDome::Init()
{
	// モデル取得
	m_Model = ModelContainer::GetModel_InName(m_ModelName);

	// シェーダー設定
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	// ドームのサイズ設定(最大描画距離 * 0.9)
	m_Size = 1000.0f * 0.9f;
}

void SkyDome::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void SkyDome::Draw()
{
	// モデルがロードされているか確認
	if (!m_Model->GetIsLoaded())
	{
		static int flag = 0;
		if (flag != 0) { return; }
		string str = string("モデルが読み込まれていません\nタグがついていない可能性があります\n") + m_ModelName;
		flag = MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("skyDome:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// 現在有効になっているカメラを取得
	Camera* camera = Manager::GetScene()->GetActiveCamera();
	if (!camera)
	{
		static int flag = 0;
		if (flag != 0) { return; }
		string str = string("カメラが取得できませんでした\nカメラがシーンに存在していない可能性があります\n");
		flag = MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("skyDome:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//------------------------
	// ワールドマトリクス設定
	//------------------------
	D3DXVECTOR3 s = D3DXVECTOR3(m_Size, m_Size, m_Size);
	D3DXVECTOR3 p = camera->GetAttachObject()->m_LocalPosition;	// カメラに追従させる
	p.y = -3.0f;

	D3DXMATRIX world, scale, trans;
	D3DXMatrixScaling(&scale, s.x, s.y, s.z);
	D3DXMatrixTranslation(&trans, p.x, p.y, p.z);
	world = scale * trans;

	Renderer::SetWorldMatrix(&world);

	// 描画
	m_Model->Draw();
}
