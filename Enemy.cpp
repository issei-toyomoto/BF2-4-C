#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy()
{
	EnemyX = 300;
	EnemyY = 250;
	EnemyFlg = 0;
	StartFlg = 0;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	if (StartFlg == 0)
	{
		for (int i = 0; i < 7; i++)
		{
			EnemyFlg++;

			if (EnemyFlg == 2)
			{
				EnemyFlg = 0;
			}
		}

		WaitTimer(200);
	}
	
}

void Enemy::Draw() const
{
	if (EnemyFlg == 0)
	{
		DrawBox(EnemyX, EnemyY, EnemyX + 20, EnemyY + 20, 0xffffff, TRUE);
	}
	if (EnemyFlg == 1)
	{
		DrawBox(EnemyX, EnemyY, EnemyX + 20, EnemyY + 20, 0xff0000, TRUE);
	}
}