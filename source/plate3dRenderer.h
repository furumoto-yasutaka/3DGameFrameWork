/*******************************************************************************
*
*	�^�C�g���F	3D�|���S���`��R���|�[�l���g	[ plate3dRenderer.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "draw3dComponent.h"
#include "renderer.h"

#include <string>

class Texture;
class TextureAnimation;

class Plate3DRenderer : public Draw3DComponent
{
public:
	// �s�{�b�g�ʒu
	enum class AnchorPosition
	{
		Left_Top,		// ����
		Center_Middle,	// ����
	};

private:
	string				m_TextureName;			// �e�N�X�`���̖���(�R���e�i��̖��O)
	Texture*			m_Texture = NULL;		// �e�N�X�`���̏ڍ׏��
	ID3D11Buffer*		m_VertexBuffer = NULL;	// ���_�o�b�t�@
	ID3D11VertexShader* m_VertexShader = NULL;	// ���_�V�F�[�_�[
	ID3D11PixelShader*	m_PixelShader = NULL;	// �s�N�Z���V�F�[�_�[
	ID3D11InputLayout*	m_VertexLayout = NULL;	// ���̓��C�A�E�g

	Renderer::TextureRenderMode	m_RenderMode = Renderer::TextureRenderMode::Static;	// �`�惂�[�h
	AnchorPosition				m_AnchorPosition = AnchorPosition::Center_Middle;	// �s�{�b�g�ʒu
	bool						m_IsBillBoard = false;			// �r���{�[�h�ݒ�
	bool						m_IsAlphaToCoverage = false;	// �A���t�@�g�D�J�p���b�W�ݒ�
	D3DXVECTOR2					m_Size;							// �`��T�C�Y
	D3DXVECTOR2					m_TexCoordBegin;				// �e�N�X�`�����W(�n�_)
	D3DXVECTOR2					m_TexCoordDistance;				// �e�N�X�`�����W(�I�_)
	D3DXCOLOR					m_TexColor;						// �e�N�X�`���J���[
	TextureAnimation*			m_Animation = NULL;				// �ڑ����̃e�N�X�`���A�j���[�V�����R���|�[�l���g

public:
	Plate3DRenderer(GameObject* AttachObject) : Draw3DComponent(AttachObject) {}

	void Init(const char* TextureName, D3DXVECTOR2 Size,
		Renderer::TextureRenderMode Mode = Renderer::TextureRenderMode::Static,
		AnchorPosition AnchorPos = AnchorPosition::Center_Middle,
		bool IsBillBoard = false, bool IsAlphaToCoverage = false);
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// �e�N�X�`���A�j���[�V�����Ɛڑ�
	void Connect(TextureAnimation* Animation,
		D3DXVECTOR2*& TexCoordBegin, D3DXVECTOR2*& TexCoordDistance,
		int& WidthDiv, int& HeightDiv);

	// �e�N�X�`���A�j���[�V�����Ƃ̐ڑ�������
	void DisConnect();

	// ���g�̍폜��\��
	void SetDestroy() override;

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	Texture* GetTexture() { return m_Texture; }
	void SetTexture(string Name);

	AnchorPosition GetAnchorPosition() { return m_AnchorPosition; }
	void SetAnchorPosition(AnchorPosition AnchorPos) { m_AnchorPosition = AnchorPos; }

	D3DXVECTOR2 GetSize() { return m_Size; }
	void SetSize(D3DXVECTOR2 Size) { m_Size = Size; }

	D3DXVECTOR2 GetTexCoordBegin() { return m_TexCoordBegin; }
	void SetTexCoordBegin(D3DXVECTOR2 Coord) { m_TexCoordBegin = Coord; }
	void SetTexCoordBeginX(float X) { m_TexCoordBegin.x = X; }
	void SetTexCoordBeginY(float Y) { m_TexCoordBegin.y = Y; }

	D3DXVECTOR2 GetTexCoordDistance() { return m_TexCoordDistance; }
	void SetTexCoordDistance(D3DXVECTOR2 Coord) { m_TexCoordDistance = Coord; }
	void SetTexCoordDistanceX(float X) { m_TexCoordDistance.x = X; }
	void SetTexCoordDistanceY(float Y) { m_TexCoordDistance.y = Y; }

	void SetTexColor(D3DXCOLOR Color) { m_TexColor = Color; }
	void SetTexAlphaColor(float Alpha) { m_TexColor.a = Alpha; }
	void SetTexRGBColor(float Red, float Green, float Blue)
	{
		m_TexColor.r = Red;
		m_TexColor.g = Green;
		m_TexColor.b = Blue;
	}
	/////////////////////////////
private:
	// ���_�����擾
	void GetVertex(VERTEX_3D* Vertex);

	// ���_���𐶐�
	void CreateVertex(VERTEX_3D* Vertex, D3DXVECTOR2 Offset);
};
