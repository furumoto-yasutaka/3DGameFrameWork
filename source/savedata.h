/*******************************************************************************
*
*	タイトル：	セーブデータクラス	[ savedata.h ]
*
*	作成者：	古本 泰隆
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

// セーブデータ構造体
struct SaveData
{
	TargetBreakingMode TargetBreaking;
	KumiteMode KumiteNormal;
	KumiteMode KumiteHard;
};
