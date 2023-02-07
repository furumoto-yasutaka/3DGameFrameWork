/*******************************************************************************
*
*	タイトル：	一意名称生成用静的クラス	[ uniqueNamingSystem.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"

#include <string>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>

class UniqueNamingSystem
{
private:
	static inline const unsigned long long m_MAX_NAME_COUNT = 9999;	// 重複名称の最大数

public:
	static void Init();
	static void Uninit();

	// 一意名称生成(map)
	template<typename T>
	static string CreateUniqueName(string BaseName, map<string, T> Names)
	{
		unsigned int i;
		string candidate;

		// 使用していない名前が見つかるまで探索
		for (i = 1; i < m_MAX_NAME_COUNT; i++)
		{
			candidate = string(BaseName) + " (" + to_string(i) + ")";
			if (Names.find(candidate) == Names.end()) { return candidate; }
		}

		CreateLimitError();
		return BaseName;
	}

	// 一意名称生成(unordered_map)
	template<typename T>
	static string CreateUniqueName(string BaseName, unordered_map<string, T> Names)
	{
		unsigned int i;
		string candidate;

		// 使用していない名前が見つかるまで探索
		for (i = 1; i < m_MAX_NAME_COUNT; i++)
		{
			candidate = string(BaseName) + " (" + to_string(i) + ")";
			if (Names.find(candidate) == Names.end()) { return candidate; }
		}

		CreateLimitError();
		return BaseName;
	}

	// 一意名称生成(multimap)
	template<typename T>
	static string CreateUniqueName(string BaseName, multimap<string, T> Names)
	{
		unsigned int i;
		string candidate;

		// 使用していない名前が見つかるまで探索
		for (i = 1; i < m_MAX_NAME_COUNT; i++)
		{
			candidate = string(BaseName) + " (" + to_string(i) + ")";
			if (Names.find(candidate) == Names.end()) { return candidate; }
		}

		CreateLimitError();
		return BaseName;
	}

	// 一意名称生成(unordered_multimap)
	template<typename T>
	static string CreateUniqueName(string BaseName, unordered_multimap<string, T> Names)
	{
		unsigned int i;
		string candidate;

		// 使用していない名前が見つかるまで探索
		for (i = 1; i < m_MAX_NAME_COUNT; i++)
		{
			candidate = string(BaseName) + " (" + to_string(i) + ")";
			if (Names.find(candidate) == Names.end()) { return candidate; }
		}

		CreateLimitError();
		return BaseName;
	}

private:
	// 生成の限界数に達した場合のエラー処理
	static void CreateLimitError();
};
