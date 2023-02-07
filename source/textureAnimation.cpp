/*******************************************************************************
*
*	タイトル：	テクスチャアニメーションコンポーネント	[ textureAnimation.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "textureAnimation.h"
#include "gameObject.h"

void TextureAnimation::Init(Plate2DRenderer* ConnectComponent, AnimationMode Mode, int AnimationInterval)
{
	// Plate2DRendererと接続
	ConnectComponent->Connect(this, m_TexCoordBegin, m_TexCoordDistance, m_WidthDiv, m_HeightDiv);

	// 初期化
	m_Mode = Mode;
	m_FrameCount = 0;
	m_AnimationInterval = AnimationInterval;
	m_TexCoordDistance->x = 1.0f / m_WidthDiv;
	m_TexCoordDistance->y = 1.0f / m_HeightDiv;
}

void TextureAnimation::Init(Plate3DRenderer* ConnectComponent, AnimationMode Mode, int AnimationInterval)
{
	// Plate3DRendererと接続
	ConnectComponent->Connect(this, m_TexCoordBegin, m_TexCoordDistance, m_WidthDiv, m_HeightDiv);

	// 初期化
	m_Mode = Mode;
	m_FrameCount = 0;
	m_AnimationInterval = AnimationInterval;
	m_TexCoordDistance->x = 1.0f / m_WidthDiv;
	m_TexCoordDistance->y = 1.0f / m_HeightDiv;
}

void TextureAnimation::Update()
{
	// テクスチャ座標計算
	int progres = m_FrameCount / m_AnimationInterval;
	m_TexCoordBegin->x = progres % m_WidthDiv * m_TexCoordDistance->x;
	m_TexCoordBegin->y = progres / m_WidthDiv * m_TexCoordDistance->y;

	// アニメーションの終端に達したら
	if (m_FrameCount >= m_WidthDiv * m_HeightDiv * m_AnimationInterval)
	{
		switch (m_Mode)
		{
		case AnimationMode::Loop:
			m_FrameCount = 0;
			break;
		case AnimationMode::Once_ObjectDestroy:
			m_AttachObject->SetDestroy();
			break;
		case AnimationMode::Once_ObjectDisable:
			m_FrameCount = 0;
			m_AttachObject->SetActive(false);
			break;
		default: return;
		}
	}

	// カウント進行
	m_FrameCount++;
}
