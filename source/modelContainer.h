/*******************************************************************************
*
*	タイトル：	モデル管理用静的クラス	[ modelContainer.h ]
*
*	作成者：	古本 泰隆
* 
*******************************************************************************/
#pragma once
#include "model.h"

#include <unordered_map>

class ModelContainer
{
private:
	// ▼要素
	// 引数1	string型	モデル名称(キー)
	// 引数2	Model*型	モデル情報
	static inline unordered_map<string, Model*> m_ModelInfo;	// モデルリスト

public:
	static void Init();
	static void Uninit();

	// すべてのモデルに対してタグに応じて
	// ロード・アンロードを実行(シーン変更時用)
	static void LoadAndUnload_AllModel();

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//

	// モデル取得(名称で検索)
	static Model* GetModel_InName(string Name);
	/////////////////////////////
private:
	// モデル追加
	static void AddModel(string Name, string Path, int Tag);
};
