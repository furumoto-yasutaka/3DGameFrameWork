/*******************************************************************************
*
*	�^�C�g���F	�e�N�X�`���u���[�R���|�[�l���g	[ plate2dBlur.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "draw2dComponent.h"
#include "renderer.h"

#include <list>

class Plate2DRenderer;

class TextureBulr2D : public Draw2DComponent
{
private:
	Plate2DRenderer*	m_Plate2DRenderer = NULL;		// �A�g����2D�`��R���|�[�l���g
	ID3D11Buffer*		m_VertexBuffer = NULL;			// ���_�o�b�t�@
	ID3D11VertexShader* m_VertexShader = NULL;			// ���_�V�F�[�_�[
	ID3D11PixelShader*	m_PixelShader = NULL;			// �s�N�Z���V�F�[�_�[
	ID3D11InputLayout*	m_VertexLayout = NULL;			// ���̓��C�A�E�g

	int					m_BulrLayer = NULL;				// �u���[����
	int					m_BulrInterval = NULL;			// �u���[�����Ԋu(�t���[��)
	int					m_InterpolationBlur = NULL;		// �u���[��Ԗ���
	float				m_BulrAlphaDecayRate = 0.0f;	// 1��������̃A���t�@������
	int					m_FrameCount = NULL;			// �t���[���J�E���^
	list<D3DXVECTOR2>	m_BulrPosition;					// �u���[�����ʒu
	list<float>			m_BulrRotationZ;				// �u���[�̉�]

public:
	TextureBulr2D(GameObject* AttachObject) : Draw2DComponent(AttachObject) {}

	void Init(Plate2DRenderer* Plate2D, unsigned int BulrLayer, unsigned int BulrInterval, unsigned int InterpolationBlur = 0);
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	// ���_�����擾
	void GetVertex(VERTEX_3D* Vertex, D3DXVECTOR2 Pos, float Alpha, float Rot);

	// ���_���𐶐�
	void CreateVertex(VERTEX_3D* Vertex, D3DXVECTOR2 Pos, D3DXVECTOR2 Offset, float Alpha, float Rot);
};
