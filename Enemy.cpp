#include "Enemy.h"
#include "DxLib.h"

// コンストラクタ
Enemy::Enemy()
{
	enemy.x = ENEMY_X;    // 敵のX座標
	enemy.y = ENEMY_Y;    // 敵のY座標
	enemy.state = 0;      // 敵の状態(0:ピンク 1:緑 2:黄色)
	enemy.life = 2;       // 敵のHP
	enemy.flg = 0;        // 敵の画像番号用
	enemy.speed = 0.4f;   // 敵の移動速度
	StartFlg = 0;         // スタート状態か判定する用
	FPScnt = 0;           // FPSカウント
	i = 0;                // スタート時、敵のモーション管理用

	LoadDivGraph("image/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, EnemyImg);  //画像読み込み
}

// デストラクタ
Enemy::~Enemy()
{

}

// 描画以外の更新を実装する
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
	if (FPScnt > 60) 
	{
		FPScnt = 0;
		i++;
	}
}

// 描画の更新を実装する
void Enemy::Draw() const
{
#ifdef _DEBUG
	DrawFormatString(50, 50, 0xffffff, "EnX:%f EnY:%f", enemy.x, enemy.y);
	DrawFormatString(50, 70, 0xffffff, "Enflg:%d", enemy.flg);

	// 敵の当たり判定表示
	if (enemy.state == 0)
	{
		if (StartFlg == 0)
		{
			// スタートモーション時
			DrawBox((int)enemy.x, (int)enemy.y + 25, (int)enemy.x + 50, (int)enemy.y + 64, 0xffffff, FALSE);
			DrawBox((int)enemy.x + 85, (int)enemy.y + 25, (int)enemy.x + 50 + 85, (int)enemy.y + 64, 0xffffff, FALSE);
			DrawBox((int)enemy.x + 170, (int)enemy.y + 25, (int)enemy.x + 50 + 170, (int)enemy.y + 64, 0xffffff, FALSE);
		}
		else
		{
			// スタート以外
			DrawBox((int)enemy.x + 10, (int)enemy.y + 12, (int)enemy.x + 55, (int)enemy.y + 65, 0xffffff, FALSE);
			/*DrawBox(EnemyX + 95, EnemyY + 10, EnemyX + 55 + 85, EnemyY + 64, 0xffffff, FALSE);
			DrawBox(EnemyX + 180, EnemyY + 10, EnemyX + 55 + 170, EnemyY + 64, 0xffffff, FALSE);*/

		}
	}

#endif // DEBUG

	// 敵画像の表示
	if (enemy.state == 0)
	{
		if (StartFlg == 0)
		{
			// スタートモーション時
			DrawGraph((int)enemy.x, (int)enemy.y, EnemyImg[enemy.flg], TRUE);
			DrawGraph((int)enemy.x + 85, (int)enemy.y, EnemyImg[enemy.flg], TRUE);
			DrawGraph((int)enemy.x + 170, (int)enemy.y, EnemyImg[enemy.flg], TRUE);
		}
		else
		{
			// スタート以外
			DrawGraph((int)enemy.x, (int)enemy.y, EnemyImg[enemy.flg], TRUE);
			/*DrawGraph(EnemyX + 85, EnemyY, EnemyImg[8], TRUE);
			DrawGraph(EnemyX + 170, EnemyY, EnemyImg[8], TRUE);*/
		}
	}
}

// 敵の移動処理
void Enemy::EnemyMove()
{
	// パタパタ手を動かすモーション
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

	// 敵のX座標
	if (enemy.x <= 0)
	{
		enemy.speed = -enemy.speed;
	}
	else if (enemy.x > 640)
	{
		enemy.speed = -enemy.speed;
	}

	// 敵のY座標範囲
	if (enemy.y <= -15)
	{
		enemy.speed = -enemy.speed;
	}
	else if (enemy.y > 480)
	{
		enemy.speed = enemy.speed;
		enemy.state += 1;
	}
	else
	{
		enemy.speed = enemy.speed;
	}

	// X座標加算
	enemy.x += enemy.speed;

	// Y座標減算
	enemy.y -= enemy.speed;
}

// 敵のスタート処理
void Enemy::StartMove()
{
		if (i == 0)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45) 
			{
				enemy.flg = 0;
			}
			else if (FPScnt > 16 && FPScnt < 30 || FPScnt > 46 && FPScnt < 60)
			{
				enemy.flg = 1;
			}
		}
		else if(i == 1)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45) 
			{
				enemy.flg = 2;
			}
			else if (FPScnt > 16 && FPScnt < 30 || FPScnt > 46 && FPScnt < 60) 
			{
				enemy.flg = 3;
			}
		}
		else if(i == 2)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45) 
			{
				enemy.flg = 4;
			}
			else if (FPScnt > 16 && FPScnt < 30 || FPScnt > 46 && FPScnt < 60) 
			{
				enemy.flg = 5;
			}
		}
		else if (i == 3)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45) 
			{
				enemy.flg = 6;
			}
			else if (FPScnt > 16 && FPScnt < 30 || FPScnt > 46 && FPScnt < 60) 
			{
				enemy.flg = 7;
				StartFlg = 1;
				i = 0;
			}
		}
}

// 敵とステージの当たり判定処理
void Enemy::EnemyCollision()
{

}