/*******************************************************************************
*
*	タイトル：	3Dコリジョン管理用静的クラス	[ collision3dManager.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "treeCell.h"
#include "collider3d.h"

#include <list>

class Collision3DManager
{
private:
	static inline const unsigned int m_TREE_MAX_LEVEL = 6;

	static inline int m_Pow[m_TREE_MAX_LEVEL + 2];
	static inline TreeCell<Collider3D>* m_TreeCellList = NULL;
	static inline list<TreeCellData<Collider3D>*> m_TreeCellDataList;
	static inline D3DXVECTOR3 m_Min;
	static inline D3DXVECTOR3 m_Size;
	static inline D3DXVECTOR3 m_Unit;
	static inline DWORD m_CellNum = 0;
	static inline int m_Level = 0;

#ifdef _DEBUG
	static inline int m_VertexNum = 0;
	static inline ID3D11Buffer* m_VertexBuffer = NULL;			// 頂点バッファ
	static inline ID3D11VertexShader* m_VertexShader = NULL;	// 頂点シェーダー
	static inline ID3D11PixelShader* m_PixelShader = NULL;		// ピクセルシェーダー
	static inline ID3D11InputLayout* m_VertexLayout = NULL;		// 入力レイアウト

	static inline int m_CollisionCount = 0;
#endif

public:
	static void Init(unsigned int Level, D3DXVECTOR3 Min, D3DXVECTOR3 Size);
	static void Uninit();
	static void Update();
	static void Draw();

	static TreeCellData<Collider3D>* Regist(Collider3D* Collider);
	static void RemoveTreeCellData(TreeCellData<Collider3D>* data);
	static void ResetSpace(unsigned int Level, D3DXVECTOR3 Min, D3DXVECTOR3 Size);

private:
	static void UpdateCells();
	static void CheckCollision(DWORD Index, list<Collider3D*>& Stack);
	static void CheckCallBack();

	static DWORD GetMortonNumber(D3DXVECTOR3 Min, D3DXVECTOR3 Max);
	// 座標→線形8分木要素番号変換関数
	static DWORD GetCellIndex(D3DXVECTOR3 Pos);
	// ビット分割関数
	static DWORD BitSeparate(BYTE n);

public:
	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	static inline int GetLevel() { return m_Level; }
	static inline D3DXVECTOR3 GetMin() { return m_Min; }
	static inline D3DXVECTOR3 GetSize() { return m_Size; }
	/////////////////////////////

#ifdef _DEBUG
private:
	static void InitDebug();
	static void UninitDebug();
	static void DrawDebug();
	static void CreateVertex(VERTEX_3D* Vertex);

public:
	static void AddCollisionCount() { m_CollisionCount++; }
#endif
};
