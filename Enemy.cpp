#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy()
{
	EnemyX = 300;
	EnemyY = 250;
	EnemyState = 0;
	EnemyFlg = 0;
	EnemyLife = 3;
	StartFlg = 0;
	WaitTime = 0;

	LoadDivGraph("image/Enemy/Enemy_P_Animation.png", 24, 8, 3, 64, 64, EnemyImg);//‰æ‘œ“Ç‚İ‚İ
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{

	if (StartFlg == 0)
	{
		if (++WaitTime <= 10)
		{
			Enemyballoon();
		}
	}
	
	if(StartFlg != 0 && EnemyState == 0)
	{
		EnemyMove();
	}
	else
	{
		EnemyX = 300;
		EnemyY = 250;
		EnemyState = 0;
		StartFlg = 0;
	}

}

void Enemy::Draw() const
{
#ifdef _DEBUG
	DrawFormatString(50, 50, 0xffffff, "EnX:%d EnY:%d", EnemyX, EnemyY);
	DrawFormatString(50, 70, 0xffffff, "Enflg:%d", EnemyFlg);
	DrawFormatString(50, 90, 0xffffff, "WaitTime:%d", WaitTime);

#endif // DEBUG
	if (EnemyState == 0)
	{
		if (StartFlg == 0)
		{
			DrawGraph(EnemyX, EnemyY, EnemyImg[EnemyFlg], TRUE);
		}
		else
		{
			DrawGraph(EnemyX, EnemyY, EnemyImg[8], TRUE);
		}
	}
}

void Enemy::Enemyballoon()
{
	
	EnemyFlg++;

	if (EnemyFlg == 8)
	{
		EnemyFlg = 0;
		StartFlg = 1;
	}

}

void Enemy::EnemyMove()
{

	if (EnemyX <= 0)
	{
		EnemyX = 640;
	}
	else if (EnemyX > 640)
	{
		EnemyX = 0;
	}
	
	EnemyX++;

	if (EnemyY <= -10)
	{
		EnemyY = -10;
	}
	else if (EnemyY > 480)
	{
		EnemyY = 480;
		EnemyState += 1;
	}

	EnemyY--;
}