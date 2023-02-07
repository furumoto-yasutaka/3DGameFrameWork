/*******************************************************************************
*
*	�^�C�g���F	�`��ݒ�ÓI�N���X	[ renderer.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"

struct VERTEX_3D
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXCOLOR	Diffuse;
	D3DXVECTOR2 TexCoord;
};

struct MATERIAL
{
	D3DXCOLOR	Ambient;	// ����(�e�̐F)
	D3DXCOLOR	Diffuse;	// �g�U���ˌ�(�\�ʂ̐F)
	D3DXCOLOR	Specular;	// ���ʔ��ˌ�(�n�C���C�g)
	D3DXCOLOR	Emission;	// ����
	float		Shininess;	// ���ʔ��ˌ����x
	float		Dummy[3];	// 
};

struct LIGHT
{
	BOOL		Enable;		// �L�����
	BOOL		Dummy[3];	// 
	D3DXVECTOR4	Direction;	// ����
	D3DXCOLOR	Diffuse;	// �F
	D3DXCOLOR	Ambient;	// ����(�e�̐F)
};

class Renderer
{
public:
	enum class TextureRenderMode
	{
		Static = 0,
		Dynamic,
	};

private:
	static inline D3D_FEATURE_LEVEL			m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	static inline ID3D11Device*				m_Device = NULL;
	static inline ID3D11DeviceContext*		m_DeviceContext = NULL;
	static inline IDXGISwapChain*			m_SwapChain = NULL;
	static inline ID3D11RenderTargetView*	m_RenderTargetView = NULL;
	static inline ID3D11DepthStencilView*	m_DepthStencilView = NULL;

	static inline ID3D11Buffer*				m_WorldBuffer = NULL;
	static inline ID3D11Buffer*				m_ViewBuffer = NULL;
	static inline ID3D11Buffer*				m_ProjectionBuffer = NULL;
	static inline ID3D11Buffer*				m_MaterialBuffer = NULL;
	static inline ID3D11Buffer*				m_LightBuffer = NULL;
	static inline ID3D11Buffer*				m_CameraBuffer = NULL;

	static inline ID3D11DepthStencilState*	m_DepthStateEnable = NULL;
	static inline ID3D11DepthStencilState*	m_DepthStateDisable = NULL;

public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX* WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX* ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);
	static void SetCameraPosition(D3DXVECTOR3 CameraPosition);

	static void SetWireFrame(bool IsWireFrame);
	static void SetAlphaToCaverage(bool IsAlphaToCaverage);

	static ID3D11Device* GetDevice() { return m_Device; }
	static ID3D11DeviceContext* GetDeviceContext() { return m_DeviceContext; }
	static IDXGISwapChain* GetSwapChain() { return m_SwapChain; }
	static ID3D11RenderTargetView* GetRenderTargetView() { return m_RenderTargetView; }

	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);
};
