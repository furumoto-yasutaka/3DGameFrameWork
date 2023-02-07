/*******************************************************************************
*
*	タイトル：　画像点滅スクリプト	[ blinkImage.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "blinkImage.h"
#include "time.h"
#include "plate2dRenderer.h"
#include "gameObject.h"

void BlinkImage::Init(BlinkMode Mode, float VisibleTimeSec, float InVisibleTimeSec,
					float ChangeVisibleTimeSec, float ChangeInVisibleTimeSec)
{
	m_Mode = Mode;
	m_State = BlinkState::Visible;
	m_TimeCountSec = VisibleTimeSec;
	m_VisibleTimeSec = VisibleTimeSec;
	m_InVisibleTimeSec = InVisibleTimeSec;
	m_ChangeVisibleTimeSec = ChangeVisibleTimeSec;
	m_ChangeInVisibleTimeSec = ChangeInVisibleTimeSec;
}

void BlinkImage::Update()
{
	m_TimeCountSec -= Time::GetDeltaTimeSec();

	if (m_TimeCountSec > 0.0f)
	{
		ChangeAlpha();
	}
	else
	{
		ChangeState();
	}
}

/*******************************************************************************
*	透明度変更
*******************************************************************************/
void BlinkImage::ChangeAlpha()
{
	switch (m_Mode)
	{
	case BlinkMode::Fade:
		ChangeAlpha_Fade();
		break;
	default: return;
	}
}

/*******************************************************************************
*	透明度変更(フェードモード)
*******************************************************************************/
void BlinkImage::ChangeAlpha_Fade()
{
	Plate2DRenderer* plate2dRenderer = m_AttachObject->GetComponent<Plate2DRenderer>();

	switch (m_State)
	{
	case BlinkState::ChangeInVisible:
		plate2dRenderer->SetTexAlphaColor(m_TimeCountSec / m_ChangeInVisibleTimeSec);
		break;
	case BlinkState::ChangeVisible:
		plate2dRenderer->SetTexAlphaColor(1.0f - (m_TimeCountSec / m_ChangeVisibleTimeSec));
		break;
	default: return;
	}
}

/*******************************************************************************
*	点滅状況変更
*******************************************************************************/
void BlinkImage::ChangeState()
{
	switch (m_Mode)
	{
	case BlinkMode::None:
		ChangeState_None();
		break;
	case BlinkMode::Fade:
		ChangeState_Fade();
		break;
	default: return;
	}
}

/*******************************************************************************
*	点滅状況変更(無設定モード)
*******************************************************************************/
void BlinkImage::ChangeState_None()
{
	Plate2DRenderer* plate2dRenderer = m_AttachObject->GetComponent<Plate2DRenderer>();

	switch (m_State)
	{
	case BlinkState::Visible:
		m_State = BlinkState::InVisible;
		m_TimeCountSec = m_InVisibleTimeSec;
		plate2dRenderer->SetTexAlphaColor(0.0f);
		break;
	case BlinkState::InVisible:
		m_State = BlinkState::Visible;
		m_TimeCountSec = m_VisibleTimeSec;
		plate2dRenderer->SetTexAlphaColor(1.0f);
		break;
	default: return;
	}
}

/*******************************************************************************
*	点滅状況変更(フェードモード)
*******************************************************************************/
void BlinkImage::ChangeState_Fade()
{
	Plate2DRenderer* plate2dRenderer = m_AttachObject->GetComponent<Plate2DRenderer>();

	switch (m_State)
	{
	case BlinkState::Visible:
		m_State = BlinkState::ChangeInVisible;
		m_TimeCountSec = m_ChangeInVisibleTimeSec;
		break;
	case BlinkState::ChangeInVisible:
		m_State = BlinkState::InVisible;
		m_TimeCountSec = m_InVisibleTimeSec;
		plate2dRenderer->SetTexAlphaColor(0.0f);
		break;
	case BlinkState::InVisible:
		m_State = BlinkState::ChangeVisible;
		m_TimeCountSec = m_ChangeVisibleTimeSec;
		break;
	case BlinkState::ChangeVisible:
		m_State = BlinkState::Visible;
		m_TimeCountSec = m_VisibleTimeSec;
		plate2dRenderer->SetTexAlphaColor(1.0f);
		break;
	default: return;
	}
}
