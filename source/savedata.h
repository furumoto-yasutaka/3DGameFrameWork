/*******************************************************************************
*
*	�^�C�g���F	�Z�[�u�f�[�^�N���X	[ savedata.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include <vector>

struct TargetBreakingMode
{
	int NormalTargetBreak;
	int RareTargetBreak;
	int Score;
};

struct KumiteMode
{
	int BulletHit;
	int ChargeBulletHit;
	int DestroyEnemy;
	int HitBalloon;
	int Score;
};

// �Z�[�u�f�[�^�\����
struct SaveData
{
	TargetBreakingMode TargetBreaking;
	KumiteMode KumiteNormal;
	KumiteMode KumiteHard;
};
