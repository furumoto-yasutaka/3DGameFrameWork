/*******************************************************************************
*
*	タイトル：	モデルクラス	[ model.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "renderer.h"
#include "texture.h"

// マテリアル構造体
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	Texture*					Tex;
};

// 描画サブセット構造体
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};

// モデル構造体
struct MODEL
{
	VERTEX_3D		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};

class Model
{
private:
	char			m_Path[256];			// 相対パス
	int				m_Tag = 0;				// 使用するシーンを表すビットフラグ
	bool			m_IsLoaded = false;		// ロード状況

	ID3D11Buffer*	m_VertexBuffer = NULL;	// 頂点バッファ
	ID3D11Buffer*	m_IndexBuffer = NULL;	// インデックスバッファ

	SUBSET*			m_SubsetArray = NULL;	// サブセット
	unsigned int	m_SubsetNum = NULL;		// サブセット数

public:
	Model() = delete;
	Model(const char* Path) { strcpy(m_Path, Path); }

	void Draw();

	// ロード
	void Load();

	// アンロード
	void Unload(bool TexDelete = false);
	
	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	char* GetPath() { return m_Path; }

	int GetTag() { return m_Tag; }
	void AddTag(int Tag) { m_Tag |= Tag; }

	bool GetIsLoaded() { return m_IsLoaded; }
	/////////////////////////////
private:
	// objファイル読み込み
	void LoadObj(const char* FileName, MODEL* Model);

	// mtlファイル読み込み
	void LoadMaterial(const char* FileName, MODEL_MATERIAL** MaterialArray, unsigned int* MaterialNum);
};
