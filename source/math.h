/*******************************************************************************
*
*	�^�C�g���F	���w�I�֐��E�\���̗p�ÓI�N���X	[ math.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include <d3dx9.h>

class Math
{
public:
	template<class T>
	struct MinMax
	{
		T Min;
		T Max;

		MinMax()
		{
			Min = T();
			Max = T();
		}
		MinMax(T Min, T Max)
		{
			this->Min = Min;
			this->Max = Max;
		}
	};

	static const inline float m_PI = 3.1415926f;
	static const inline float m_HALF_DIV_PI = 57.295779f;	// 180 / PI
	static const inline float m_PI_DIV_HALF = 0.0174532f;	// PI / 180

	//-----------------------
	// �x�N�g���̐��K��
	//-----------------------
	static D3DXVECTOR3 Normalize(D3DXVECTOR3 Vector);
	static D3DXVECTOR3 Normalize(float X, float Y, float Z);
	static D3DXVECTOR2 Normalize(D3DXVECTOR2 Vector);
	static D3DXVECTOR2 Normalize(float X, float Y);

	//-------------
	// ��������
	//-------------
	static int Random(int Max);
	static float Random(float Max);
	static D3DXVECTOR2 Random(D3DXVECTOR2 Max);
	static D3DXVECTOR3 Random(D3DXVECTOR3 Max);

	//---------------------------------------
	// �x���@���烉�W�A���ɕϊ�
	//---------------------------------------
	static float DegreeToRadian(float Degree);				// (1��)
	static D3DXVECTOR3 DegreeToRadian(D3DXVECTOR3 Degree);	// (3��)

	//---------------------------------------
	// ���W�A������x���@�ɕϊ�
	//---------------------------------------
	static float RadianToDegree(float Radian);				// (1��)
	static D3DXVECTOR3 RadianToDegree(D3DXVECTOR3 Radian);	// (3��)

	//---------------------------------------
	// �I�C���[�p���N�I�[�^�j�I���ɕϊ�
	//---------------------------------------
	static D3DXQUATERNION EulerAngleToQuaternion(float X, float Y, float Z);
	static D3DXQUATERNION EulerAngleToQuaternion(D3DXVECTOR3 EulerAngle);

	//---------------------------------------
	// �N�I�[�^�j�I�����I�C���[�p�ɕϊ�
	//---------------------------------------
	static D3DXVECTOR3 QuaternionToEulerAngle(float X, float Y, float Z, float W);
	static D3DXVECTOR3 QuaternionToEulerAngle(D3DXQUATERNION Quaternion);

	//---------------------------------------
	// �P�ʍ쐬
	//---------------------------------------
	static D3DXQUATERNION GetQuaternionIdentity();
	static D3DXMATRIX GetMatrixIdentity();

	//---------------------------------------
	// ��]�N�I�[�^�j�I������
	//---------------------------------------
	static D3DXQUATERNION AxisRotation_Radian(D3DXVECTOR3 Axis, float Value);
	static D3DXQUATERNION AxisRotation_Degree(D3DXVECTOR3 Axis, float Value);

	//---------------------------------------
	// �x�N�g���̂Ȃ��p���v�Z(������ŋ߂�����)
	//---------------------------------------
	static float VectorAngle(D3DXVECTOR3 V1, D3DXVECTOR3 V2);
	static float VectorAngle(D3DXVECTOR2 V1, D3DXVECTOR2 V2);

	//---------------------------------------
	// 2D�x�N�g���̂Ȃ��p���v�Z(�����)
	//---------------------------------------
	static float Vector2DAngle_TurnLeft(D3DXVECTOR2 V1, D3DXVECTOR2 V2);

	//---------------------------------------
	// 2D�x�N�g���̂Ȃ��p���v�Z(�E���)
	//---------------------------------------
	static float Vector2DAngle_TurnRight(D3DXVECTOR2 V1, D3DXVECTOR2 V2);
};
