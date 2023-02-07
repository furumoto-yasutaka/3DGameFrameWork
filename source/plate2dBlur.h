/*******************************************************************************
*
*	タイトル：	テクスチャブラーコンポーネント	[ plate2dBlur.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "draw2dComponent.h"
#include "renderer.h"

#include <list>

class Plate2DRenderer;

class TextureBulr2D : public Draw2DComponent
{
private:
	Plate2DRenderer*	m_Plate2DRenderer = NULL;		// 連携中の2D描画コンポーネント
	ID3D11Buffer*		m_VertexBuffer = NULL;			// 頂点バッファ
	ID3D11VertexShader* m_VertexShader = NULL;			// 頂点シェーダー
	ID3D11PixelShader*	m_PixelShader = NULL;			// ピクセルシェーダー
	ID3D11InputLayout*	m_VertexLayout = NULL;			// 入力レイアウト

	int					m_BulrLayer = NULL;				// ブラー枚数
	int					m_BulrInterval = NULL;			// ブラー発生間隔(フレーム)
	int					m_InterpolationBlur = NULL;		// ブラー補間枚数
	float				m_BulrAlphaDecayRate = 0.0f;	// 1枚当たりのアルファ減衰率
	int					m_FrameCount = NULL;			// フレームカウンタ
	list<D3DXVECTOR2>	m_BulrPosition;					// ブラー発生位置
	list<float>			m_BulrRotationZ;				// ブラーの回転

public:
	TextureBulr2D(GameObject* AttachObject) : Draw2DComponent(AttachObject) {}

	void Init(Plate2DRenderer* Plate2D, unsigned int BulrLayer, unsigned int BulrInterval, unsigned int InterpolationBlur = 0);
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	// 頂点情報を取得
	void GetVertex(VERTEX_3D* Vertex, D3DXVECTOR2 Pos, float Alpha, float Rot);

	// 頂点情報を生成
	void CreateVertex(VERTEX_3D* Vertex, D3DXVECTOR2 Pos, D3DXVECTOR2 Offset, float Alpha, float Rot);
};
