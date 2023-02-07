/*******************************************************************************
*
*	タイトル：	数学的関数・構造体用静的クラス	[ math.h ]
*
*	作成者：	古本 泰隆
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
	// ベクトルの正規化
	//-----------------------
	static D3DXVECTOR3 Normalize(D3DXVECTOR3 Vector);
	static D3DXVECTOR3 Normalize(float X, float Y, float Z);
	static D3DXVECTOR2 Normalize(D3DXVECTOR2 Vector);
	static D3DXVECTOR2 Normalize(float X, float Y);

	//-------------
	// 乱数生成
	//-------------
	static int Random(int Max);
	static float Random(float Max);
	static D3DXVECTOR2 Random(D3DXVECTOR2 Max);
	static D3DXVECTOR3 Random(D3DXVECTOR3 Max);

	//---------------------------------------
	// 度数法からラジアンに変換
	//---------------------------------------
	static float DegreeToRadian(float Degree);				// (1軸)
	static D3DXVECTOR3 DegreeToRadian(D3DXVECTOR3 Degree);	// (3軸)

	//---------------------------------------
	// ラジアンから度数法に変換
	//---------------------------------------
	static float RadianToDegree(float Radian);				// (1軸)
	static D3DXVECTOR3 RadianToDegree(D3DXVECTOR3 Radian);	// (3軸)

	//---------------------------------------
	// オイラー角をクオータニオンに変換
	//---------------------------------------
	static D3DXQUATERNION EulerAngleToQuaternion(float X, float Y, float Z);
	static D3DXQUATERNION EulerAngleToQuaternion(D3DXVECTOR3 EulerAngle);

	//---------------------------------------
	// クオータニオンをオイラー角に変換
	//---------------------------------------
	static D3DXVECTOR3 QuaternionToEulerAngle(float X, float Y, float Z, float W);
	static D3DXVECTOR3 QuaternionToEulerAngle(D3DXQUATERNION Quaternion);

	//---------------------------------------
	// 単位作成
	//---------------------------------------
	static D3DXQUATERNION GetQuaternionIdentity();
	static D3DXMATRIX GetMatrixIdentity();

	//---------------------------------------
	// 回転クオータニオン生成
	//---------------------------------------
	static D3DXQUATERNION AxisRotation_Radian(D3DXVECTOR3 Axis, float Value);
	static D3DXQUATERNION AxisRotation_Degree(D3DXVECTOR3 Axis, float Value);

	//---------------------------------------
	// ベクトルのなす角を計算(両周りで近い方向)
	//---------------------------------------
	static float VectorAngle(D3DXVECTOR3 V1, D3DXVECTOR3 V2);
	static float VectorAngle(D3DXVECTOR2 V1, D3DXVECTOR2 V2);

	//---------------------------------------
	// 2Dベクトルのなす角を計算(左回り)
	//---------------------------------------
	static float Vector2DAngle_TurnLeft(D3DXVECTOR2 V1, D3DXVECTOR2 V2);

	//---------------------------------------
	// 2Dベクトルのなす角を計算(右回り)
	//---------------------------------------
	static float Vector2DAngle_TurnRight(D3DXVECTOR2 V1, D3DXVECTOR2 V2);
};
