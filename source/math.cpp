/*******************************************************************************
*
*	�^�C�g���F	���w�I�֗��֐��p�ÓI�N���X	[ math.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "math.h"

#include <cmath>

/*******************************************************************************
*	�x�N�g���̐��K��(D3DXVECTOR3)
*******************************************************************************/
D3DXVECTOR3 Math::Normalize(D3DXVECTOR3 Vector)
{
	float magnitude = std::sqrtf(Vector.x * Vector.x + Vector.y * Vector.y + Vector.z * Vector.z);
	float ratio = 1 / magnitude;
	D3DXVECTOR3 result = Vector;

	result *= ratio;

	return result;
}
/*******************************************************************************
*	�x�N�g���̐��K��(float3��)
*******************************************************************************/
D3DXVECTOR3 Math::Normalize(float X, float Y, float Z)
{
	float magnitude = std::sqrtf(X * X + Y * Y + Z * Z);
	float ratio = 1 / magnitude;
	D3DXVECTOR3 result = D3DXVECTOR3(X, Y, Z);

	result *= ratio;
	return result;
}
/*******************************************************************************
*	�x�N�g���̐��K��(D3DXVECTOR2)
*******************************************************************************/
D3DXVECTOR2 Math::Normalize(D3DXVECTOR2 Vector)
{
	float magnitude = std::sqrtf(Vector.x * Vector.x + Vector.y * Vector.y);
	float ratio = 1 / magnitude;
	D3DXVECTOR2 result = Vector;

	result *= ratio;
	return result;
}
/*******************************************************************************
*	�x�N�g���̐��K��(float2��)
*******************************************************************************/
D3DXVECTOR2 Math::Normalize(float X, float Y)
{
	float magnitude = std::sqrtf(X * X + Y * Y);
	float ratio = 1 / magnitude;
	D3DXVECTOR2 result = D3DXVECTOR2(X, Y);

	result *= ratio;
	return result;
}

/*******************************************************************************
*	��������(int)
*******************************************************************************/
int Math::Random(int Max)
{
	return rand() % Max;
}
/*******************************************************************************
*	��������(float)
*******************************************************************************/
float Math::Random(float Max)
{
	return (float)rand() / RAND_MAX * Max;
}
/*******************************************************************************
*	��������(D3DXVECTOR2)
*******************************************************************************/
D3DXVECTOR2 Math::Random(D3DXVECTOR2 Max)
{
	D3DXVECTOR2 value;
	value.x = (float)rand() / RAND_MAX * Max.x;
	value.y = (float)rand() / RAND_MAX * Max.y;
	return value;
}
/*******************************************************************************
*	��������(D3DXVECTOR3)
*******************************************************************************/
D3DXVECTOR3 Math::Random(D3DXVECTOR3 Max)
{
	D3DXVECTOR3 value;
	value.x = (float)rand() / RAND_MAX * Max.x;
	value.y = (float)rand() / RAND_MAX * Max.y;
	value.z = (float)rand() / RAND_MAX * Max.z;
	return value;
}

/*******************************************************************************
*	�x���@���烉�W�A���ɕϊ�(1��)
*******************************************************************************/
float Math::DegreeToRadian(float Degree)
{
	return Degree * m_PI_DIV_HALF;
}
/*******************************************************************************
*	�x���@���烉�W�A���ɕϊ�(3��)
*******************************************************************************/
D3DXVECTOR3 Math::DegreeToRadian(D3DXVECTOR3 Degree)
{
	return Degree * m_PI_DIV_HALF;
}

/*******************************************************************************
*	���W�A������x���@�ɕϊ�(1��)
*******************************************************************************/
float Math::RadianToDegree(float Radian)
{
	return Radian * m_HALF_DIV_PI;
}
/*******************************************************************************
*	���W�A������x���@�ɕϊ�(3��)
*******************************************************************************/
D3DXVECTOR3 Math::RadianToDegree(D3DXVECTOR3 Radian)
{
	return Radian * m_HALF_DIV_PI;
}

/*******************************************************************************
*	�I�C���[�p���N�I�[�^�j�I���ɕϊ�(float�����w��)
*******************************************************************************/
D3DXQUATERNION Math::EulerAngleToQuaternion(float X, float Y, float Z)
{
	float cosX = cosf(X * 0.5f);
	float sinX = sinf(X * 0.5f);
	float cosY = cosf(Y * 0.5f);
	float sinY = sinf(Y * 0.5f);
	float cosZ = cosf(Z * 0.5f);
	float sinZ = sinf(Z * 0.5f);

	float qX = cosZ * cosX * cosY + sinZ * sinX * sinY;
	float qY = sinZ * cosX * cosY - cosZ * sinX * sinY;
	float qZ = cosZ * sinX * cosY + sinZ * cosX * sinY;
	float qW = cosZ * cosX * sinY - sinZ * sinX * cosY;

	return D3DXQUATERNION(qX, qY, qZ, qW);
}
/*******************************************************************************
*	�I�C���[�p���N�I�[�^�j�I���ɕϊ�(D3DXVECTOR3)
*******************************************************************************/
D3DXQUATERNION Math::EulerAngleToQuaternion(D3DXVECTOR3 EulerAngle)
{
	float cosX = cosf(EulerAngle.x * 0.5f);
	float sinX = sinf(EulerAngle.x * 0.5f);
	float cosY = cosf(EulerAngle.y * 0.5f);
	float sinY = sinf(EulerAngle.y * 0.5f);
	float cosZ = cosf(EulerAngle.z * 0.5f);
	float sinZ = sinf(EulerAngle.z * 0.5f);

	float qX = cosZ * cosX * cosY + sinZ * sinX * sinY;
	float qY = sinZ * cosX * cosY - cosZ * sinX * sinY;
	float qZ = cosZ * sinX * cosY + sinZ * cosX * sinY;
	float qW = cosZ * cosX * sinY - sinZ * sinX * cosY;

	return D3DXQUATERNION(qX, qY, qZ, qW);
}

/*******************************************************************************
*	�N�I�[�^�j�I�����I�C���[�p�ɕϊ�(float�����w��)
*******************************************************************************/
D3DXVECTOR3 Math::QuaternionToEulerAngle(float X, float Y, float Z, float W)
{
	float XX = X * X;
	float XY = X * Y;
	float XZ = X * Z;
	float XW = X * W;
	float YY = Y * Y;
	float YZ = Y * Z;
	float YW = Y * W;
	float ZZ = Z * Z;
	float ZW = Z * W;
	float WW = W * W;

	float pitch = asinf(2.0f * (XZ - YW));
	float yaw = atan2f(2.0f * (YZ + XW), XX + YY - ZZ - WW);
	float roll = atan2f(2.0f * (ZW + XY), XX - YY - ZZ + WW);

	return D3DXVECTOR3(pitch, yaw, roll);
}
/*******************************************************************************
*	�N�I�[�^�j�I�����I�C���[�p�ɕϊ�(D3DXQUATERNION)
*******************************************************************************/
D3DXVECTOR3 Math::QuaternionToEulerAngle(D3DXQUATERNION Quaternion)
{
	float XX = Quaternion.x * Quaternion.x;
	float XY = Quaternion.x * Quaternion.y;
	float XZ = Quaternion.x * Quaternion.z;
	float XW = Quaternion.x * Quaternion.w;
	float YY = Quaternion.y * Quaternion.y;
	float YZ = Quaternion.y * Quaternion.z;
	float YW = Quaternion.y * Quaternion.w;
	float ZZ = Quaternion.z * Quaternion.z;
	float ZW = Quaternion.z * Quaternion.w;
	float WW = Quaternion.w * Quaternion.w;

	//float yaw = atan2f(2.0f * (YZ + XW), XX + YY - ZZ - WW);
	//float pitch = asinf(2.0f * (XZ - YW));
	//float roll = atan2f(2.0f * (ZW + XY), XX - YY - ZZ + WW);

	float sy = 2.0f * XZ + 2.0f * YW;
	bool unlocked = fabs(sy) < 0.99999f;

	float yaw = unlocked ? atan2f(-(2.0f * YZ - 2.0f * XW), 2.0f * WW + 2.0f * ZZ - 1.0f) :
		atan2f(2.0f * YZ + 2.0f + XW, 2.0f * WW + 2.0f * YY - 1.0f);
	float pitch = asinf(sy);
	float roll = unlocked ? atan2f(-(2.0f * XY - 2.0f * ZW), 2.0f * WW + 2.0f * XX - 1.0f) : 0.0f;
	
	return D3DXVECTOR3(yaw, pitch, roll);
}

//---------------------------------------
// �P�ʃN�I�[�^�j�I���쐬
//---------------------------------------
D3DXQUATERNION Math::GetQuaternionIdentity()
{
	D3DXQUATERNION q;
	D3DXQuaternionIdentity(&q);
	return q;
}

//---------------------------------------
// �P�ʃ}�g���N�X�쐬
//---------------------------------------
D3DXMATRIX Math::GetMatrixIdentity()
{
	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	return m;
}

/*******************************************************************************
*	��]�N�I�[�^�j�I������(Radian�F���W�A��)
*******************************************************************************/
D3DXQUATERNION Math::AxisRotation_Radian(D3DXVECTOR3 Axis, float Value)
{
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &Axis, Value);
	return quat;
}
/*******************************************************************************
*	��]�N�I�[�^�j�I������(Degree�F�x���@)
*******************************************************************************/
D3DXQUATERNION Math::AxisRotation_Degree(D3DXVECTOR3 Axis, float Value)
{
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &Axis, DegreeToRadian(Value));
	return quat;
}

/*******************************************************************************
*	�x�N�g���̂Ȃ��p���v�Z(������ŋ߂�����)(D3DXVECTOR3)
*******************************************************************************/
float Math::VectorAngle(D3DXVECTOR3 V1, D3DXVECTOR3 V2)
{
	float dot = D3DXVec3Dot(&V1, &V2);
	if (dot > 1.0f) { dot = 1.0f; }
	else if (dot < -1.0f) { dot = -1.0f; }
	return acosf(dot);
}

/*******************************************************************************
*	�x�N�g���̂Ȃ��p���v�Z(������ŋ߂�����)(D3DXVECTOR2)
*******************************************************************************/
float Math::VectorAngle(D3DXVECTOR2 V1, D3DXVECTOR2 V2)
{
	float dot = D3DXVec2Dot(&V1, &V2);
	return acosf(dot);
}

/*******************************************************************************
*	2D�x�N�g���̂Ȃ��p���v�Z(�����)
*******************************************************************************/
float Math::Vector2DAngle_TurnLeft(D3DXVECTOR2 V1, D3DXVECTOR2 V2)
{
	float angle1 = atan2f(V1.y, V1.x);
	if (angle1 < 0.0f) { angle1 += m_PI * 2.0f; }

	float angle2 = atan2f(V2.y, V2.x);
	if (angle2 < 0.0f) { angle2 += m_PI * 2.0f; }

	float angleDistance = angle1 - angle2;
	if (angleDistance < 0.0f) { angleDistance += m_PI * 2.0f; }

	return angleDistance;
}

/*******************************************************************************
*	2D�x�N�g���̂Ȃ��p���v�Z(�E���)
*******************************************************************************/
float Math::Vector2DAngle_TurnRight(D3DXVECTOR2 V1, D3DXVECTOR2 V2)
{
	float angleDistance = Vector2DAngle_TurnLeft(V1, V2);
	angleDistance = m_PI * 2.0f - angleDistance;

	return angleDistance;
}
