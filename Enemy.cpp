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
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	if (StartFlg == 0)
	{
		Enemyballoon();
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
#endif // DEBUG
	if (EnemyState == 0)
	{
		if (EnemyFlg == 0)
		{
			DrawBox(EnemyX, EnemyY, EnemyX + 20, EnemyY + 20, 0xffffff, TRUE);
		}
		if (EnemyFlg == 1)
		{
			DrawBox(EnemyX, EnemyY, EnemyX + 20, EnemyY + 20, 0xff0000, TRUE);
		}
		if (EnemyFlg == 2)
		{
			DrawBox(EnemyX, EnemyY, EnemyX + 20, EnemyY + 20, 0x00ff00, TRUE);
		}
		if (EnemyFlg == 3)
		{
			DrawBox(EnemyX, EnemyY, EnemyX + 20, EnemyY + 20, 0x0000ff, TRUE);
		}
		if (EnemyFlg == 4)
		{
			DrawBox(EnemyX, EnemyY, EnemyX + 20, EnemyY + 20, 0xffffff, TRUE);
		}
		if (EnemyFlg == 5)
		{
			DrawBox(EnemyX, EnemyY, EnemyX + 20, EnemyY + 20, 0xff0000, TRUE);
		}
		if (EnemyFlg == 6)
		{
			DrawBox(EnemyX, EnemyY, EnemyX + 20, EnemyY + 20, 0x00ff00, TRUE);
		}
	}
}

void Enemy::Enemyballoon()
{

	EnemyFlg++;

	if (EnemyFlg == 7)
	{
		EnemyFlg = 0;
		StartFlg = 1;
	}

	WaitTimer(300);
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

	if (EnemyY <= 0)
	{
		EnemyY = 0;
	}
	else if (EnemyY > 480)
	{
		EnemyY = 480;
		EnemyState += 1;
	}

	EnemyY++;
}