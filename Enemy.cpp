#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy()
{
	EnemyX = ENEMY_X;
	EnemyY = ENEMY_Y;
	EnemyState = 0;
	EnemyFlg = 0;
	EnemyLife = 3;
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
	else if(StartFlg != 0 && EnemyState == 0)
	{
		EnemyMove();
	}
	else
	{
		EnemyX = ENEMY_X;
		EnemyY = ENEMY_Y;
		EnemyState = 0;
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
	DrawFormatString(50, 50, 0xffffff, "EnX:%d EnY:%d", EnemyX, EnemyY);
	DrawFormatString(50, 70, 0xffffff, "Enflg:%d", EnemyFlg);
	DrawFormatString(50, 90, 0xffffff, "WaitTime:%d", FPScnt);
	if (EnemyState == 0)
	{
		if (StartFlg == 0)
		{
			DrawBox(EnemyX, EnemyY + 25, EnemyX + 50, EnemyY + 64, 0xffffff, FALSE);
			DrawBox(EnemyX + 85, EnemyY + 25, EnemyX + 50 + 85, EnemyY + 64, 0xffffff, FALSE);
			DrawBox(EnemyX + 170, EnemyY + 25, EnemyX + 50 + 170, EnemyY + 64, 0xffffff, FALSE);
		}
		else
		{
			DrawBox(EnemyX + 10, EnemyY + 10, EnemyX + 55, EnemyY + 64, 0xffffff, FALSE);
			/*DrawBox(EnemyX + 95, EnemyY + 10, EnemyX + 55 + 85, EnemyY + 64, 0xffffff, FALSE);
			DrawBox(EnemyX + 180, EnemyY + 10, EnemyX + 55 + 170, EnemyY + 64, 0xffffff, FALSE);*/

		}
	}
#endif // DEBUG
	if (EnemyState == 0)
	{
		if (StartFlg == 0)
		{
			DrawGraph(EnemyX, EnemyY, EnemyImg[EnemyFlg], TRUE);
			DrawGraph(EnemyX + 85, EnemyY, EnemyImg[EnemyFlg], TRUE);
			DrawGraph(EnemyX + 170, EnemyY, EnemyImg[EnemyFlg], TRUE);
		}
		else
		{
			DrawGraph(EnemyX, EnemyY, EnemyImg[8], TRUE);
			/*DrawGraph(EnemyX + 85, EnemyY, EnemyImg[8], TRUE);
			DrawGraph(EnemyX + 170, EnemyY, EnemyImg[8], TRUE);*/
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

void Enemy::StartMove()
{
		if (i == 0)
		{
			if (FPScnt > 0 && FPScnt < 15) {
				EnemyFlg = 0;
			}
			else if (FPScnt > 16 && FPScnt < 30) {
				EnemyFlg = 1;
			}
			else if (FPScnt > 31 && FPScnt < 45) {
				EnemyFlg = 0;
			}
			else if (FPScnt > 46 && FPScnt < 60) {
				EnemyFlg = 1;
			}
		}
		else if(i == 1)
		{
			if (FPScnt > 0 && FPScnt < 15) {
				EnemyFlg = 2;
			}
			else if (FPScnt > 16 && FPScnt < 30) {
				EnemyFlg = 3;
			}
			else if (FPScnt > 31 && FPScnt < 45) {
				EnemyFlg = 2;
			}
			else if (FPScnt > 46 && FPScnt < 60) {
				EnemyFlg = 3;
			}
		}
		else if(i == 2)
		{
			if (FPScnt > 0 && FPScnt < 15) {
				EnemyFlg = 4;
			}
			else if (FPScnt > 16 && FPScnt < 30) {
				EnemyFlg = 5;
			}
			else if (FPScnt > 31 && FPScnt < 45) {
				EnemyFlg = 4;
			}
			else if (FPScnt > 46 && FPScnt < 60) {
				EnemyFlg = 5;
			}
		}
		else if (i == 3)
		{
			if (FPScnt > 0 && FPScnt < 15) {
				EnemyFlg = 6;
			}
			else if (FPScnt > 16 && FPScnt < 30) {
				EnemyFlg = 7;
			}
			else if (FPScnt > 31 && FPScnt < 45) {
				EnemyFlg = 6;
			}
			else if (FPScnt > 46 && FPScnt < 60) {
				EnemyFlg = 7;
				StartFlg = 1;
				i = 0;
			}
		}
}

void Enemy::EnemyCollision()
{

}