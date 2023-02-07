/*******************************************************************************
*
*	タイトル：	モデル描画コンポーネント	[ modelRenderer.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "modelRenderer.h"
#include "renderer.h"
#include "modelContainer.h"
#include "gameObject.h"
#include "input.h"

void ModelRenderer::Init(const char* ModelName, string VertexShaderName, string PixelShaderName)
{
	m_ModelName = ModelName;
	m_VertexShaderName = VertexShaderName + ".cso";
	m_PixelShaderName = PixelShaderName + ".cso";

	// モデル取得
	m_Model = ModelContainer::GetModel_InName(m_ModelName);

	// シェーダー設定
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, m_VertexShaderName.c_str());
	Renderer::CreatePixelShader(&m_PixelShader, m_PixelShaderName.c_str());
}

void ModelRenderer::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void ModelRenderer::Update()
{

}

void ModelRenderer::Draw()
{
	// モデルがロードされているか確認
	if (!m_Model->GetIsLoaded())
	{
		static int flag = 0;
		if (flag != 0) { return; }
		string str = string("モデルが読み込まれていません\nタグがついていない可能性があります\n") + m_ModelName;
		flag = MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("meshRenderer:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	D3DXMATRIX m = m_AttachObject->GetWorldMatrix();
	Renderer::SetWorldMatrix(&m);

	// モデル描画
	m_Model->Draw();
}

/*******************************************************************************
*	モデル変更
*******************************************************************************/
void ModelRenderer::SetModel(string ModelName)
{
	m_ModelName = ModelName;

	m_Model = ModelContainer::GetModel_InName(m_ModelName);
}
