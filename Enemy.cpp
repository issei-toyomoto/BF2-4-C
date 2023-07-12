#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy()
{
	enemy.x = ENEMY_X;
	enemy.y = ENEMY_Y;
	enemy.state = 0;
	enemy.life = 3;
	enemy.flg = 0;
	enemy.speed = 2;
	StartFlg = 0;
	WaitTime = 0;
	FPScnt = 0;
	i = 0;

	LoadDivGraph("image/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, EnemyImg);//画像読み込み
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	FPScnt++;

	if (StartFlg == 0 && i < 4)
	{
			StartMove();
	}
	else if(StartFlg != 0 && enemy.state == 0)
	{
		EnemyMove();
	}
	else
	{
		enemy.x = ENEMY_X;
		enemy.y = ENEMY_Y;
		enemy.state = 0;
		StartFlg = 0;
	}

	//１秒たったらフレームカウント
	if (FPScnt > 60) {
		FPScnt = 0;
		i++;
	}
}

void Enemy::Draw() const
{
#ifdef _DEBUG
	DrawFormatString(50, 50, 0xffffff, "EnX:%d EnY:%d", enemy.x, enemy.y);
	DrawFormatString(50, 70, 0xffffff, "Enflg:%d", enemy.flg);
	DrawFormatString(50, 90, 0xffffff, "WaitTime:%d", FPScnt);
	if (enemy.state == 0)
	{
		if (StartFlg == 0)
		{
			DrawBox(enemy.x, enemy.y + 25, enemy.x + 50, enemy.y + 64, 0xffffff, FALSE);
			DrawBox(enemy.x + 85, enemy.y + 25, enemy.x + 50 + 85, enemy.y + 64, 0xffffff, FALSE);
			DrawBox(enemy.x + 170, enemy.y + 25, enemy.x + 50 + 170, enemy.y + 64, 0xffffff, FALSE);
		}
		else
		{
			DrawBox(enemy.x + 10, enemy.y + 10, enemy.x + 55, enemy.y + 65, 0xffffff, FALSE);
			/*DrawBox(EnemyX + 95, EnemyY + 10, EnemyX + 55 + 85, EnemyY + 64, 0xffffff, FALSE);
			DrawBox(EnemyX + 180, EnemyY + 10, EnemyX + 55 + 170, EnemyY + 64, 0xffffff, FALSE);*/

		}
	}
#endif // DEBUG
	if (enemy.state == 0)
	{
		if (StartFlg == 0)
		{
			DrawGraph(enemy.x, enemy.y, EnemyImg[enemy.flg], TRUE);
			DrawGraph(enemy.x + 85, enemy.y, EnemyImg[enemy.flg], TRUE);
			DrawGraph(enemy.x + 170, enemy.y, EnemyImg[enemy.flg], TRUE);
		}
		else
		{
			DrawGraph(enemy.x, enemy.y, EnemyImg[enemy.flg], TRUE);
			/*DrawGraph(EnemyX + 85, EnemyY, EnemyImg[8], TRUE);
			DrawGraph(EnemyX + 170, EnemyY, EnemyImg[8], TRUE);*/
		}
	}
}

void Enemy::EnemyMove()
{
	if (FPScnt > 0 && FPScnt < 5 || FPScnt > 11 && FPScnt < 15 || FPScnt > 21 && FPScnt < 25)
	{
		enemy.flg = 8;
	}
	else if (FPScnt > 31 && FPScnt < 35 || FPScnt > 41 && FPScnt < 45 || FPScnt > 51 && FPScnt < 55)
	{
		enemy.flg = 8;
	}
	else
	{
		enemy.flg = 9;
	}

	if (enemy.x <= 0)
	{
		enemy.speed = -enemy.speed;
	}
	else if (enemy.x > 640)
	{
		enemy.speed = -enemy.speed;
	}

	if (enemy.y <= -15)
	{
		enemy.speed = -enemy.speed;
	}
	else if (enemy.y > 480)
	{
		enemy.speed = -enemy.speed;
		enemy.state += 1;
	}
	else
	{
		enemy.speed = enemy.speed;
	}

	enemy.x += enemy.speed;
	enemy.y -= enemy.speed;
}

void Enemy::StartMove()
{
		if (i == 0)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45) {
				enemy.flg = 0;
			}
			else if (FPScnt > 16 && FPScnt < 30 || FPScnt > 46 && FPScnt < 60) {
				enemy.flg = 1;
			}
		}
		else if(i == 1)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45) {
				enemy.flg = 2;
			}
			else if (FPScnt > 16 && FPScnt < 30 || FPScnt > 46 && FPScnt < 60) {
				enemy.flg = 3;
			}
		}
		else if(i == 2)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45) {
				enemy.flg = 4;
			}
			else if (FPScnt > 16 && FPScnt < 30 || FPScnt > 46 && FPScnt < 60) {
				enemy.flg = 5;
			}
		}
		else if (i == 3)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45) {
				enemy.flg = 6;
			}
			else if (FPScnt > 16 && FPScnt < 30 || FPScnt > 46 && FPScnt < 60) {
				enemy.flg = 7;
				StartFlg = 1;
				i = 0;
			}
		}
}

void Enemy::EnemyCollision()
{

}