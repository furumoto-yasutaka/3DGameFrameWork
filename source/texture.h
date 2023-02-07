/*******************************************************************************
*
*	タイトル：	テクスチャクラス	[ texture.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"

class Texture
{
private:
	char						m_Path[256];				// 相対パス
	int							m_Tag = 0;					// 使用するシーンを表すビットフラグ
	ID3D11ShaderResourceView*	m_TextureResource = NULL;	// テクスチャリソース
	bool						m_IsLoaded = false;			// ロード状況
	int							m_WidthDiv = 1;				// 横分割数
	int							m_HeightDiv = 1;			// 縦分割数

public:
	Texture() = delete;
	Texture(const char* Path) { strcpy(m_Path, Path); }
	
	// ロード
	void Load();

	// アンロード
	void Unload();

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	char* GetPath() { return m_Path; }
	void SetPath(char* path) { strcpy(m_Path, path); }

	int GetTag() { return m_Tag; }
	void AddTag(int Tag) { m_Tag |= Tag; }

	ID3D11ShaderResourceView* GetResource() { return m_TextureResource; }

	bool GetIsLoaded() { return m_IsLoaded; }

	int GetWidthDiv() { return m_WidthDiv; }
	void SetWidthDiv(int WidthDiv) { m_WidthDiv = WidthDiv; }

	int GetHeightDiv() { return m_HeightDiv; }
	void SetHeightDiv(int HeightDiv) { m_HeightDiv = HeightDiv; }
	/////////////////////////////
};
