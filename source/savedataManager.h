/*******************************************************************************
*
*	タイトル：	セーブデータ管理用静的クラス	[ savedataManager.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "savedata.h"

#include <fstream>

class SavedataManager
{
public:
	//static const int m_SAVE_DATA_NUM = 3;
	static inline SaveData m_SaveData;		// セーブデータ情報

public:
	static void Init();
	static void Uninit();

	// セーブ
	static void Save();
	
private:
	// ロード
	static void Load(ifstream* Ifs);

	// 生成
	static SaveData Create();

	// 初期化
	static void Clear();
};
