/*******************************************************************************
*
*	タイトル：	分木の1空間分のクラス	[ treeCell.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
template<class T>
class TreeCellData;

// 分木の1空間分のクラス
template<class T>
class TreeCell
{
private:
	TreeCellData<T>* m_DataList = NULL;	// 空間内のオブジェクトの先頭アドレス

public:
	~TreeCell()
	{
		// 全ての要素を削除する
		TreeCellData<T>* temp;
		while (m_DataList)
		{
			// 削除の前に自身の次の要素を保存する
			temp = m_DataList->m_Next;
			// 先頭要素を削除
			delete m_DataList;
			// 保存した要素を先頭とする
			m_DataList = temp;
		}
	}

	// オブジェクトを登録
	void Push(TreeCellData<T>* Data)
	{
		// 不正な値または既に自身を登録している場合は登録しない
		if (!Data || Data->m_BelongToCell == this) { return; }

		// 別の空間に属している場合はその空間から削除
		// (どの空間にも属していないパターンは分木の範囲外から範囲内に戻るような場合に発生)
		if (Data->m_BelongToCell != NULL)
		{
			Data->Remove();
		}

		// 現在空間に別のオブジェクトが存在するか
		if (m_DataList)
		{// 存在する
			// 参照をいじって登録
			Data->m_Next = m_DataList;
			m_DataList->m_Prev = Data;
			m_DataList = Data;
		}
		else
		{// 存在しない
			// 代入で登録
			m_DataList = Data;
		}
		Data->m_BelongToCell = this;
	}

	// オブジェクトの削除通知
	void OnRemove(TreeCellData<T>* Data)
	{
		// 先頭要素が削除された場合ポインタを更新する
		if (m_DataList == Data && Data != NULL)
		{
			m_DataList = m_DataList->m_Next;
		}
	}

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	TreeCellData<T>* GetDataList() { return m_DataList; }
	/////////////////////////////
};

// コリジョン1つ分の情報を持ったデータクラス
template<class T>
class TreeCellData
{
public:
	TreeCell<T>*		m_BelongToCell = NULL;	// 属している空間
	T*					m_Object = NULL;		// 管理対象コンポーネント
	TreeCellData<T>*	m_Prev = NULL;			// 属している空間において自身の前の要素
	TreeCellData<T>*	m_Next = NULL;			// 属している空間において自身の次の要素

public:
	TreeCellData() = delete;
	TreeCellData(T* Object)
	{
		m_Object = Object;
	};

	// 空間オブジェクトのリストから削除する
	// (座標移動による再登録時とコンポーネント削除時に呼び出される)
	void Remove()
	{
		if (m_BelongToCell != NULL)
		{
			// 削除通知
			m_BelongToCell->OnRemove(this);

			// 参照を整理
			if (m_Prev) { m_Prev->m_Next = m_Next; }
			if (m_Next) { m_Next->m_Prev = m_Prev; }

			m_Prev = NULL;
			m_Next = NULL;
			
			m_BelongToCell = NULL;
		}
	}
};
