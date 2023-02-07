/*******************************************************************************
*
*	タイトル：	遷移演出用静的クラス	[ transition.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "renderer.h"
#include "textureContainer.h"
#include "callbackListner.h"

#include <functional>

class Texture;
class Component;

class Transition
{
public:
	// トランジションの形式
	enum class TransitionPattern
	{
		None = 0,	// ぱっと切り替え
		Fade,		// フェード
		Wipe,
	};
	// トランジションの状況
	enum class TransitionState
	{
		Out = 0,		// 画面を隠していく
		In,				// 画面を見せていく
		OutComplete,	// 画面が隠れた状態になった
		None,			// 無処理・画面が見える状態になった
		Length,
	};

	// トランジション設定用構造体
	struct TransitionOption
	{
		Transition::TransitionPattern	Mode[2];			// 現在は未使用
		float							TimeLimitSec[2];
		Texture*						Texture;

		TransitionOption()
		{
			for (int i = 0; i < 2; i++)
			{
				Mode[i] = TransitionPattern::None;
				TimeLimitSec[i] = 0.0f;
			}
			Texture = NULL;
		}
	};

private:
	static inline TransitionState		m_State;				// トランジションの状況
	static inline TransitionOption		m_Option;				// トランジション設定
	static inline float					m_TimeCountSec = 0.0f;	// 経過時間
	static inline bool					m_IsLoadFrame = false;	// ロードがあるフレーム

	static inline ID3D11Buffer*			m_VertexBuffer = NULL;	// 頂点バッファ
	static inline ID3D11VertexShader*	m_VertexShader = NULL;	// 頂点シェーダー
	static inline ID3D11PixelShader*	m_PixelShader = NULL;	// ピクセルシェーダー
	static inline ID3D11InputLayout*	m_VertexLayout = NULL;	// 入力レイアウト

	static inline CallBackBase*			m_CallBack = NULL;		// コールバック関数(シーンが切り替わった瞬間呼ばれる)

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// シーン切り替え前トランジション開始
	static void StartTransitionOut(TransitionOption Option);

	// シーン切り替え後トランジション開始
	static void StartTransitionIn();

	// ゲーム起動時のトランジションオプションを取得
	static TransitionOption GetFirstTransitionOption();

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	static void SetTransitionOption(TransitionOption Option) { m_Option = Option; }

	static TransitionState GetTransitionState() { return m_State; }

	// コールバックを設定
	template<class T>
	static void SetCallBack(T* Origin, void(T::* Function)())
	{
		m_CallBack = new CallBackListner<T>(Origin, Function);
	}
	/////////////////////////////
private:
	// 頂点情報を生成
	static void CreateVertex(VERTEX_3D* Vertex, float Alpha);
	static void CreateVertex_WipeLeft(VERTEX_3D* Vertex, float Rate);
	static void CreateVertex_WipeRight(VERTEX_3D* Vertex, float Rate);

	// 描画処理
	static void Draw_Fade();
	static void Draw_Wipe();
};
