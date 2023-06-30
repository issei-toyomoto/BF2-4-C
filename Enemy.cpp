#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy()
{
	EnemyX = 300;
	EnemyY = 250;
	EnemyState = 0;
	EnemyFlg = 0;
	EnemyLife = 0;
	StartFlg = 0;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	if (StartFlg == 0)
	{
		EnemyStart();
	}
}

void Enemy::Draw() const
{
	if (EnemyFlg == 0 &&  EnemyState == 0)
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

void Enemy::EnemyStart()
{

	EnemyFlg++;

	if (EnemyFlg == 7)
	{
		EnemyFlg = 0;
		StartFlg = 1;
	}

	WaitTimer(300);
}