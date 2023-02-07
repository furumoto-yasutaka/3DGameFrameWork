/*******************************************************************************
*
*	タイトル：	ゲーム全体管理用静的クラス	[ manager.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "scene.h"
#include "transition.h"

class Manager
{
public:
	static inline Scene* m_Scene = NULL;		// シーンのインスタンス
	static inline Scene* m_NextScene = NULL;	// 予約用シーンのインスタンス

public:
	static void Init(HINSTANCE hInstance);
	static void Uninit();
	static void Update();
	static void Draw();

	// 次のシーンを予約
	template<class T>
	static void SetScene(Transition::TransitionOption Info)
	{
		m_NextScene = DBG_NEW T();

		if (m_Scene)
		{// シーンが存在する場合
			// 通常の遷移
			Transition::StartTransitionOut(Info);
		}
		else
		{// シーンが存在しない場合
			// ゲーム起動直後ということなのでフェードアウトはせず、遷移設定を反映する
			Transition::SetTransitionOption(Info);
		}
	}

	// シーン遷移を行うか確認
	static void CheckScene();

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	static Scene* GetScene() { return m_Scene; }
	/////////////////////////////
};
