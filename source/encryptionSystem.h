/*******************************************************************************
*
*	タイトル：	暗号化用静的クラス	[ encryptionSystem.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"

#include <vector>

#include <nlohmann/json.hpp>

using namespace nlohmann;

class EncryptionSystem
{
private:
	static inline vector<uint8_t> m_Vector;
	static inline BCRYPT_KEY_HANDLE m_KeyHandle;
	static inline vector<uint8_t> m_KeyObject;

public:
	static void Init();
	static void Uninit();

	// 暗号化
	static vector<uint8_t> Encryption(vector<uint8_t> Binary);
	// 復号化
	static vector<uint8_t> Decryption(vector<uint8_t> Binary);
};
