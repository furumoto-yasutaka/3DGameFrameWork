/*******************************************************************************
*
*	�^�C�g���F	��Ӗ��̐����p�ÓI�N���X	[ uniqueNamingSystem.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
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
	static inline const unsigned long long m_MAX_NAME_COUNT = 9999;	// �d�����̂̍ő吔

public:
	static void Init();
	static void Uninit();

	// ��Ӗ��̐���(map)
	template<typename T>
	static string CreateUniqueName(string BaseName, map<string, T> Names)
	{
		unsigned int i;
		string candidate;

		// �g�p���Ă��Ȃ����O��������܂ŒT��
		for (i = 1; i < m_MAX_NAME_COUNT; i++)
		{
			candidate = string(BaseName) + " (" + to_string(i) + ")";
			if (Names.find(candidate) == Names.end()) { return candidate; }
		}

		CreateLimitError();
		return BaseName;
	}

	// ��Ӗ��̐���(unordered_map)
	template<typename T>
	static string CreateUniqueName(string BaseName, unordered_map<string, T> Names)
	{
		unsigned int i;
		string candidate;

		// �g�p���Ă��Ȃ����O��������܂ŒT��
		for (i = 1; i < m_MAX_NAME_COUNT; i++)
		{
			candidate = string(BaseName) + " (" + to_string(i) + ")";
			if (Names.find(candidate) == Names.end()) { return candidate; }
		}

		CreateLimitError();
		return BaseName;
	}

	// ��Ӗ��̐���(multimap)
	template<typename T>
	static string CreateUniqueName(string BaseName, multimap<string, T> Names)
	{
		unsigned int i;
		string candidate;

		// �g�p���Ă��Ȃ����O��������܂ŒT��
		for (i = 1; i < m_MAX_NAME_COUNT; i++)
		{
			candidate = string(BaseName) + " (" + to_string(i) + ")";
			if (Names.find(candidate) == Names.end()) { return candidate; }
		}

		CreateLimitError();
		return BaseName;
	}

	// ��Ӗ��̐���(unordered_multimap)
	template<typename T>
	static string CreateUniqueName(string BaseName, unordered_multimap<string, T> Names)
	{
		unsigned int i;
		string candidate;

		// �g�p���Ă��Ȃ����O��������܂ŒT��
		for (i = 1; i < m_MAX_NAME_COUNT; i++)
		{
			candidate = string(BaseName) + " (" + to_string(i) + ")";
			if (Names.find(candidate) == Names.end()) { return candidate; }
		}

		CreateLimitError();
		return BaseName;
	}

private:
	// �����̌��E���ɒB�����ꍇ�̃G���[����
	static void CreateLimitError();
};
