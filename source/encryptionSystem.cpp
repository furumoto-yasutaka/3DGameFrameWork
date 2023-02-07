/*******************************************************************************
*
*	タイトル：	暗号化用静的クラス	[ encryptionSystem.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "encryptionSystem.h"

void EncryptionSystem::Init()
{

}

void EncryptionSystem::Uninit()
{

}

vector<uint8_t> EncryptionSystem::Encryption(vector<uint8_t> Binary)
{
	//// 実験：暗号化処理
	//vector<uint8_t> secret(16, 1);

	//// 乱数生成用
	//random_device rd;
	//uniform_int_distribution<int> uid(0, 0xff);

	//// 暗号を複雑にするためのランダムなバイト(初期化ベクトル)
	//vector<uint8_t> iv0, iv1;
	//for (int i = 0; i < 16; i++)
	//{
	//	int temp = uid(rd);
	//	iv0.push_back(temp);
	//	//temp = uid(rd);
	//	iv1.push_back(temp);
	//}

	//vector<uint8_t> encrypted; // 暗号化後データ
	//vector<uint8_t> decrypted; // 復号化後データ

	//// 暗号化アルゴリズムプロバイダを開く
	//BCRYPT_ALG_HANDLE alg = NULL;
	//(void)BCryptOpenAlgorithmProvider(&alg, L"AES", NULL, 0);

	//if (alg != NULL)
	//{
	//	ULONG keyLength = 0;	// キーのサイズ(アルゴリズムによってサイズが変化する)
	//	ULONG temp;				// 値は使わないがエラーが出るため一時変数を作る

	//	// キーのサイズを取得
	//	(void)BCryptGetProperty(alg, L"ObjectLength", reinterpret_cast<PUCHAR>(&keyLength), sizeof(keyLength), &temp, 0);

	//	// キーオブジェクトを作成
	//	BCRYPT_KEY_HANDLE key = NULL;			// 暗号化に使用するキーハンドル
	//	vector<uint8_t> keyObject(keyLength);	// キーオブジェクト
	//	(void)BCryptGenerateSymmetricKey(alg, &key, &keyObject[0], keyLength, &secret[0], 16, 0);

	//	if (key != NULL)
	//	{
	//		// 暗号化するデータを準備
	//		vector<uint8_t> temp = json::to_msgpack(j);	// Jsonを一旦バイナリに変換
	//		size_t textLen = temp.size() + 1;			// バイト数を取得(+1はNULL文字)

	//		// 暗号化後のサイズを確認して領域を確保してから暗号化を行う
	//		uint8_t* plainText = temp.data();	// 型の都合が悪いのでvectorからポインタを取得
	//		ULONG encryptedSize;
	//		(void)BCryptEncrypt(key, plainText, textLen, NULL, &iv0[0], 16, NULL, 0, &encryptedSize, 0x00000001);
	//		encrypted.resize(encryptedSize);
	//		(void)BCryptEncrypt(key, plainText, textLen, NULL, &iv0[0], 16, &encrypted[0], encryptedSize, &encryptedSize, 0x00000001);

	//		// 復号化後のサイズを確認して領域を確保してから復号を行う
	//		uint8_t* encryptedText = encrypted.data();	// 型の都合が悪いのでvectorからポインタを取得
	//		ULONG decryptedSize;
	//		(void)BCryptDecrypt(key, encryptedText, encryptedSize, NULL, &iv1[0], 16, NULL, 0, &decryptedSize, 0x00000001);
	//		decrypted.resize(decryptedSize);
	//		(void)BCryptDecrypt(key, encryptedText, encryptedSize, NULL, &iv1[0], 16, &decrypted[0], decryptedSize, &decryptedSize, 0x00000001);

	//		(void)BCryptDestroyKey(key);	// 使い終わった暗号化キーを破棄する
	//	}
	//	// 暗号化アルゴリズムプロバイダを閉じる
	//	(void)BCryptCloseAlgorithmProvider(alg, 0);
	//}
	//else
	//{
	//	return;
	//}


	////// 実験：そのままJson出力
	////ofstream ofs("asset\\json\\savedata.json");
	////
	////ofs << setw(4) << j << endl;


	////// 実験：バイナリ出力
	////ofstream ofs("asset\\json\\savedata.bin");
	////vector<uint8_t> v_msgpack = json::to_msgpack(j);
	////for (uint8_t t : v_msgpack)
	////{
	////	ofs << t;
	////}


	////// 実験：バイナリに変換してjsonにまた戻してから出力
	////ofstream ofs("asset\\json\\savedata.json");
	////vector<uint8_t> v_msgpack = json::to_msgpack(j);
	////json j2 = json::from_msgpack(v_msgpack);
	////ofs << setw(4) << j2 << endl;


	////// 実験：暗号化状態で出力
	////ofstream ofs("asset\\json\\savedata.bin");
	////for (uint8_t t : encrypted)
	////{
	////	ofs << t;
	////}


	//// 実験：暗号化後に復号してから出力
	//ofstream ofs("asset\\json\\savedata.json");
	//json j2 = json::from_msgpack(decrypted, false);
	//ofs << setw(4) << j2 << endl;
	
	return vector<uint8_t>();
}

vector<uint8_t> EncryptionSystem::Decryption(vector<uint8_t> Binary)
{
	return vector<uint8_t>();
}
