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
		//EnemyCollision();
	}
	else
	{
		EnemyInit();
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

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// 敵の当たり判定表示
		if (enemy[i].state == 0)
		{
			if (StartFlg == 0)
			{
				// スタートモーション時
				DrawBox((int)enemy[i].x, (int)enemy[i].y + 25, (int)enemy[i].x + 50, (int)enemy[i].y + 64, 0xffffff, FALSE);
			}
			else
			{
				// スタート以外
				DrawBox((int)enemy[i].x + 10, (int)enemy[i].y + 12, (int)enemy[i].x + 55, (int)enemy[i].y + 65, 0xffffff, FALSE);
				
			}
		}
	}

#endif // DEBUG

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// 敵画像の表示
		if (enemy[i].life != 0)
		{
			if (StartFlg == 0)
			{
				// スタートモーション時
				DrawGraph((int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].flg], TRUE);
			}
			else
			{
				// スタート以外
				// 画面内
				if (Px >= enemy[i].x + 10)
				{
					DrawTurnGraph((int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].flg], TRUE);
				}
				else
				{
					DrawGraph((int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].flg], TRUE);
				}

				// 画面外
				if (enemy[i].x < 0)
				{
					DrawGraph(640 + (int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].flg], TRUE);
				}
				else if (enemy[i].x > 640 - 64)
				{
					DrawGraph((int)enemy[i].x - 640, (int)enemy[i].y, EnemyImg[enemy[i].flg], TRUE);
				}
			}
		}
	}
}

// 敵の初期化処理
void Enemy::EnemyInit()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].x = ENEMY_X + 85 * i;
		enemy[i].y = ENEMY_Y;
		enemy[i].state = 0;
	}
}

// 敵の移動処理
void Enemy::EnemyMove()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// 敵のX座標範囲
		if (enemy[i].x <= 0)
		{
			enemy[i].x = 640;
		}
		else if (enemy[i].x > 640)
		{
			enemy[i].x = 0;
		}

		// 敵のY座標範囲
		if (enemy[i].y <= -20)
		{
			enemy[i].y = enemy[i].y * 0.8f;
		}
		else if (enemy[i].y > 356)
		{
			enemy[i].speed = enemy[i].speed;
			enemy[i].y = 356;
		}


		// プレイヤーが敵より右にいるときは右に移動
		if (Px >= enemy[i].x)
		{
			// X座標加算
			enemy[i].x += enemy[i].speed;

		}
		else
		{
			// プレイヤーが敵より左にいるときは左に移動
			// X座標減算
			enemy[i].x -= enemy[i].speed;

		}


		// プレイヤーが敵より上にいるときは浮上する
		if (Py < enemy[i].y)
		{
			EnemyUp();

			// Y座標減算
			enemy[i].y -= enemy[i].speed;
		}
		else
		{
			EnemyDown();

			// Y座標減算
			enemy[i].y += enemy[i].speed;

		}
	}
	
}

// 敵のスタート処理
void Enemy::StartMove()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (StartMotion == 0)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[i].flg = 0;
			}
			else
			{
				enemy[i].flg = 1;
			}
		}
		else if (StartMotion == 1)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[i].flg = 2;
			}
			else
			{
				enemy[i].flg = 3;
			}
		}
		else if (StartMotion == 2)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[i].flg = 4;
			}
			else
			{
				enemy[i].flg = 5;
			}
		}
		else if (StartMotion == 3)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[i].flg = 6;
			}
			else
			{
				enemy[i].flg = 7;
				StartFlg = 1;
				StartMotion = 0;
			}
		}
	}
}

// 敵の浮上モーション処理
void Enemy::EnemyUp()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// パタパタ手を動かすモーション
		if (FPScnt > 0 && FPScnt < 5 || FPScnt > 11 && FPScnt < 15 || FPScnt > 21 && FPScnt < 25)
		{
			enemy[i].flg = 8;
		}
		else if (FPScnt > 31 && FPScnt < 35 || FPScnt > 41 && FPScnt < 45 || FPScnt > 51 && FPScnt < 55)
		{
			enemy[i].flg = 8;
		}
		else
		{
			enemy[i].flg = 9;
		}
	}
}

// 敵の降下モーション処理
void Enemy::EnemyDown()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// 降下モーション
		if (FPScnt > 0 && FPScnt < 20)
		{
			enemy[i].flg = 12;
		}
		else if (FPScnt > 41  && FPScnt < 60 )
		{
			enemy[i].flg = 11;
		}
		else
		{
			enemy[i].flg = 10;

			// 10 11 10 12 10 
		}
	}
}

// 敵同士の当たり判定
void Enemy::EnemyCollision()
{
	int EnXL[ENEMY_MAX] = { 0 }, EnYL[ENEMY_MAX] = { 0 };//左上
	int EnXR[ENEMY_MAX] = { 0 }, EnYR[ENEMY_MAX] = { 0 };//右下

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnXL[i] = (int)(enemy[i].x + 10) - (ENEMY_W / 2);
		EnYL[i] = (int)(enemy[i].y + 12) - (ENEMY_H / 2);
		EnXR[i] = EnXL[i] + ENEMY_W;
		EnYR[i] = EnYL[i] + ENEMY_H;
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (i == 0)
		{
			if (EnXL[i] < EnXR[i + 1] && EnXL[i + 1] < EnXR[i] && EnYL[i] < EnYR[i + 1] && EnYL[i + 1] < EnYR[i])
			{
				
			}

			if (EnXL[i] < EnXR[i + 2] && EnXL[i + 2] < EnXR[i] && EnYL[i] < EnYR[i + 2] && EnYL[i + 2] < EnYR[i])
			{
				
			}
		}
		else if (i == 2)
		{
			if (EnXL[i] < EnXR[i - 1] && EnXL[i - 1] < EnXR[i] && EnYL[i] < EnYR[i - 1] && EnYL[i - 1] < EnYR[i])
			{
				
			}
		}
		
	}
	
}

// 敵とステージの当たり判定処理
void Enemy::StageCollision()
{
}

