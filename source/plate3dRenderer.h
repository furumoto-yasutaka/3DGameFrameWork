/*******************************************************************************
*
*	タイトル：	3D板ポリゴン描画コンポーネント	[ plate3dRenderer.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "draw3dComponent.h"
#include "renderer.h"

#include <string>

class Texture;
class TextureAnimation;

class Plate3DRenderer : public Draw3DComponent
{
public:
	// ピボット位置
	enum class AnchorPosition
	{
		Left_Top,		// 左上
		Center_Middle,	// 中央
	};

private:
	string				m_TextureName;			// テクスチャの名称(コンテナ上の名前)
	Texture*			m_Texture = NULL;		// テクスチャの詳細情報
	ID3D11Buffer*		m_VertexBuffer = NULL;	// 頂点バッファ
	ID3D11VertexShader* m_VertexShader = NULL;	// 頂点シェーダー
	ID3D11PixelShader*	m_PixelShader = NULL;	// ピクセルシェーダー
	ID3D11InputLayout*	m_VertexLayout = NULL;	// 入力レイアウト

	Renderer::TextureRenderMode	m_RenderMode = Renderer::TextureRenderMode::Static;	// 描画モード
	AnchorPosition				m_AnchorPosition = AnchorPosition::Center_Middle;	// ピボット位置
	bool						m_IsBillBoard = false;			// ビルボード設定
	bool						m_IsAlphaToCoverage = false;	// アルファトゥカパレッジ設定
	D3DXVECTOR2					m_Size;							// 描画サイズ
	D3DXVECTOR2					m_TexCoordBegin;				// テクスチャ座標(始点)
	D3DXVECTOR2					m_TexCoordDistance;				// テクスチャ座標(終点)
	D3DXCOLOR					m_TexColor;						// テクスチャカラー
	TextureAnimation*			m_Animation = NULL;				// 接続中のテクスチャアニメーションコンポーネント

public:
	Plate3DRenderer(GameObject* AttachObject) : Draw3DComponent(AttachObject) {}

	void Init(const char* TextureName, D3DXVECTOR2 Size,
		Renderer::TextureRenderMode Mode = Renderer::TextureRenderMode::Static,
		AnchorPosition AnchorPos = AnchorPosition::Center_Middle,
		bool IsBillBoard = false, bool IsAlphaToCoverage = false);
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// テクスチャアニメーションと接続
	void Connect(TextureAnimation* Animation,
		D3DXVECTOR2*& TexCoordBegin, D3DXVECTOR2*& TexCoordDistance,
		int& WidthDiv, int& HeightDiv);

	// テクスチャアニメーションとの接続を解除
	void DisConnect();

	// 自身の削除を予約
	void SetDestroy() override;

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	Texture* GetTexture() { return m_Texture; }
	void SetTexture(string Name);

	AnchorPosition GetAnchorPosition() { return m_AnchorPosition; }
	void SetAnchorPosition(AnchorPosition AnchorPos) { m_AnchorPosition = AnchorPos; }

	D3DXVECTOR2 GetSize() { return m_Size; }
	void SetSize(D3DXVECTOR2 Size) { m_Size = Size; }

	D3DXVECTOR2 GetTexCoordBegin() { return m_TexCoordBegin; }
	void SetTexCoordBegin(D3DXVECTOR2 Coord) { m_TexCoordBegin = Coord; }
	void SetTexCoordBeginX(float X) { m_TexCoordBegin.x = X; }
	void SetTexCoordBeginY(float Y) { m_TexCoordBegin.y = Y; }

	D3DXVECTOR2 GetTexCoordDistance() { return m_TexCoordDistance; }
	void SetTexCoordDistance(D3DXVECTOR2 Coord) { m_TexCoordDistance = Coord; }
	void SetTexCoordDistanceX(float X) { m_TexCoordDistance.x = X; }
	void SetTexCoordDistanceY(float Y) { m_TexCoordDistance.y = Y; }

	void SetTexColor(D3DXCOLOR Color) { m_TexColor = Color; }
	void SetTexAlphaColor(float Alpha) { m_TexColor.a = Alpha; }
	void SetTexRGBColor(float Red, float Green, float Blue)
	{
		m_TexColor.r = Red;
		m_TexColor.g = Green;
		m_TexColor.b = Blue;
	}
	/////////////////////////////
private:
	// 頂点情報を取得
	void GetVertex(VERTEX_3D* Vertex);

	// 頂点情報を生成
	void CreateVertex(VERTEX_3D* Vertex, D3DXVECTOR2 Offset);
};
