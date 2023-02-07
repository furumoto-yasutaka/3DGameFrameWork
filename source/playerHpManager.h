/*******************************************************************************
*
*	タイトル：	プレイヤーHP制御ステートクラス	[ playerHpManager.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class PlayerParameter;
class Plate2DRenderer;

class PlayerHpManager : public ScriptComponent
{
private:
	static inline const float m_FILL_INTERPOLATION_RATE = 0.1f;
	static inline const float m_FILL_INTERPOLATION_THRESHOLD = 0.01f;
	static inline const D3DXVECTOR2 m_UI_SIZE = { 80.0f, 80.0f };
	static inline const float m_UI_DISTANCE = 80.0f;
	static inline const float m_SHAKE_LENGTH = 2.0f;

	PlayerParameter* m_PlayerParameter = NULL;
	float m_FillRate = 0.0f;

public:
	PlayerHpManager(GameObject* AttachObject) :
		ScriptComponent(AttachObject) {}

	void Init() {}
	void Uninit() override {}
	void Update() override;
	void Draw() override {}

	void CreateUi(PlayerParameter* Parameter);

	void FillInterporation();
	void FillDecrease(int UiIndex, float Amount);
	void FillRise(int UiIndex, float Amount);
	void SetFill(Plate2DRenderer* Plate, float Rate);

	void UiShake(int UiIndex);
	void UiStop(int UiIndex);
};
