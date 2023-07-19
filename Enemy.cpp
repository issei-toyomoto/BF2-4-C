#include "Enemy.h"
#include "Player.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

// コンストラクタ
Enemy::Enemy()
{
	EnemyInit();

	StartFlg = 0;   // スタート状態か判定する用
	FPScnt = 0;     // FPSカウント
	StartMotion = 0;          // スタート時、敵のモーション管理用
	Px = 0;         // プレイヤーのX座標
	Py = 0;         // プレイヤーのY座標

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

	// プレイヤーの座標取得
	Px = Player::PlayerX;
	Py = Player::PlayerY;

	if (StartFlg == 0 && StartMotion < 4)
	{
		StartMove();
	}
	else if(StartFlg != 0)
	{
		EnemyMove();
	}
	else
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			enemy[j].x = ENEMY_X;
			enemy[j].y = ENEMY_Y;
			enemy[j].state = 0;
		}

		StartFlg = 0;
	}

	//１秒たったらフレームカウント
	if (FPScnt > 60) 
	{
		FPScnt = 0;
		StartMotion++;
	}
}

// 描画の更新を実装する
void Enemy::Draw() const
{
#ifdef _DEBUG
	DrawFormatString(50, 50, 0xffffff, "EnX:%f EnY:%f", enemy[2].x, enemy[2].y);
	DrawFormatString(50, 70, 0xffffff, "Enflg:%d", enemy[0].flg);
	DrawFormatString(50, 100, 0xffffff, "Px:%f", Px);
	DrawFormatString(50, 130, 0xffffff, "Py:%f", Py);

	for (int j = 0; j < ENEMY_MAX; j++)
	{
		// 敵の当たり判定表示
		if (enemy[j].state == 0)
		{
			if (StartFlg == 0)
			{
				// スタートモーション時
				DrawBox((int)enemy[j].x, (int)enemy[j].y + 25, (int)enemy[j].x + 50, (int)enemy[j].y + 64, 0xffffff, FALSE);
			}
			else
			{
				// スタート以外
				DrawBox((int)enemy[j].x + 10, (int)enemy[j].y + 12, (int)enemy[j].x + 55, (int)enemy[j].y + 65, 0xffffff, FALSE);
				
			}
		}
	}

#endif // DEBUG

	for (int j = 0; j < ENEMY_MAX; j++)
	{
		// 敵画像の表示
		if (enemy[j].life != 0)
		{
			if (StartFlg == 0)
			{
				// スタートモーション時
				DrawGraph((int)enemy[j].x, (int)enemy[j].y, EnemyImg[enemy[j].flg], TRUE);
			}
			else
			{
				// スタート以外
				// 画面内
				if (Px >= enemy[j].x + 10)
				{
					DrawTurnGraph((int)enemy[j].x, (int)enemy[j].y, EnemyImg[enemy[j].flg], TRUE);
				}
				else
				{
					DrawGraph((int)enemy[j].x, (int)enemy[j].y, EnemyImg[enemy[j].flg], TRUE);
				}

				// 画面外
				if (enemy[j].x < 0)
				{
					DrawGraph(640 + (int)enemy[j].x, (int)enemy[j].y, EnemyImg[enemy[j].flg], TRUE);
				}
				else if (enemy[j].x > 640 - 64)
				{
					DrawGraph((int)enemy[j].x - 640, (int)enemy[j].y, EnemyImg[enemy[j].flg], TRUE);
				}
			}
		}
	}
}

// 敵の初期化処理
void Enemy::EnemyInit()
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		enemy[j].x = ENEMY_X + 85 * j;
		enemy[j].y = ENEMY_Y;
	}
}

// 敵の移動処理
void Enemy::EnemyMove()
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		// 敵のX座標範囲
		if (enemy[j].x <= 0)
		{
			enemy[j].x = 640;
		}
		else if (enemy[j].x > 640)
		{
			enemy[j].x = 0;
		}

		// 敵のY座標範囲
		if (enemy[j].y <= -20)
		{
			enemy[j].y = enemy[j].y * 0.8f;
		}
		else if (enemy[j].y > 356)
		{
			enemy[j].speed = enemy[j].speed;
			enemy[j].y = 356;
		}


		// プレイヤーが敵より右にいるときは右に移動
		if (Px >= enemy[j].x)
		{
			// X座標加算
			enemy[j].x += enemy[j].speed;

		}
		else
		{
			// プレイヤーが敵より左にいるときは左に移動
			// X座標減算
			enemy[j].x -= enemy[j].speed;

		}


		// プレイヤーが敵より上にいるときは浮上する
		if (Py < enemy[j].y)
		{
			EnemyUp();

			// Y座標減算
			enemy[j].y -= enemy[j].speed;
		}
		else
		{
			EnemyDown();

			// Y座標減算
			enemy[j].y += enemy[j].speed;

		}
	}
	
}

// 敵のスタート処理
void Enemy::StartMove()
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		if (StartMotion == 0)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[j].flg = 0;
			}
			else
			{
				enemy[j].flg = 1;
			}
		}
		else if (StartMotion == 1)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[j].flg = 2;
			}
			else
			{
				enemy[j].flg = 3;
			}
		}
		else if (StartMotion == 2)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[j].flg = 4;
			}
			else
			{
				enemy[j].flg = 5;
			}
		}
		else if (StartMotion == 3)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[j].flg = 6;
			}
			else
			{
				enemy[j].flg = 7;
				StartFlg = 1;
				StartMotion = 0;
			}
		}
	}
}

// 敵の浮上モーション処理
void Enemy::EnemyUp()
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		// パタパタ手を動かすモーション
		if (FPScnt > 0 && FPScnt < 5 || FPScnt > 11 && FPScnt < 15 || FPScnt > 21 && FPScnt < 25)
		{
			enemy[j].flg = 8;
		}
		else if (FPScnt > 31 && FPScnt < 35 || FPScnt > 41 && FPScnt < 45 || FPScnt > 51 && FPScnt < 55)
		{
			enemy[j].flg = 8;
		}
		else
		{
			enemy[j].flg = 9;
		}
	}
}

// 敵の降下モーション処理
void Enemy::EnemyDown()
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		// 降下モーション
		if (FPScnt > 0 && FPScnt < 20)
		{
			enemy[j].flg = 11;
		}
		else if (FPScnt > 21 && FPScnt < 40)
		{
			enemy[j].flg = 12;
		}
		else
		{
			enemy[j].flg = 10;

			// 10 11 10 12 10 
		}
	}
}

// 敵とステージの当たり判定処理
void Enemy::StageCollision()
{

}