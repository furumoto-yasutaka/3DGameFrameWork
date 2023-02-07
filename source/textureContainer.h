/*******************************************************************************
*
*	タイトル：	テクスチャ管理用静的クラス	[ textureContainer.h ]
*	※ モデルに付属しているテクスチャは管理に含みません
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "texture.h"

#include <unordered_map>
#include <memory>

class TextureContainer
{
private:
	// ▼要素
	// 引数1	string型	テクスチャ名称(キー)
	// 引数2	Texture*型	テクスチャ情報
	static inline unordered_map<string, Texture*> m_TextureInfo;	// テクスチャリスト

public:
	static void Init();
	static void Uninit();

	// すべてのテクスチャに対して使用フラグに応じて
	// ロード・アンロードを実行(シーン変更時用)
	static void LoadAndUnload_AllTexture();

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//

	// テクスチャ取得(名称で検索)
	static Texture* GetTexture_InName(string Name);
	/////////////////////////////
private:
	// テクスチャ追加
	static void AddTexture(string Name, string Path,
						int WidthDiv, int HeightDiv, int Tag);
};
