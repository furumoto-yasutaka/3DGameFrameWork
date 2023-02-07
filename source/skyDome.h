/*******************************************************************************
*
*	タイトル：	スカイドーム用静的クラス	[ skyDome.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"

#include <string>

class Model;

class SkyDome
{
private:
	static string				m_ModelName;	// モデル名称(コンテナ上の名前)
	static Model*				m_Model;		// モデルの詳細情報
	static ID3D11VertexShader*	m_VertexShader;	// 頂点シェーダー
	static ID3D11PixelShader*	m_PixelShader;	// ピクセルシェーダー
	static ID3D11InputLayout*	m_VertexLayout;	// 入力レイアウト
	static float				m_Size;			// サイズ

public:
	static void Init();
	static void Uninit();
	static void Draw();
};
