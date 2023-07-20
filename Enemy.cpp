#include "Enemy.h"
#include "Player.h"
#include "Common.h"
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
	HitFlg = 0;
	HitPFlg = 0;

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
		HitStage();
		HitFlg = HitEnemy();
		HitPFlg = HitPlayer();
		EnemyMove();
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
	DrawFormatString(50, 160, 0xffffff, "Hit:%d", HitPFlg);
	

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
				//DrawBox((int)enemy[i].x + 10, (int)enemy[i].y + 12, (int)enemy[i].x + 55, (int)enemy[i].y + 65, 0xffffff, FALSE);
				
				// プレイヤーと当たってる場合赤枠、当たっていない場合白枠
				if (HitPFlg == 1)
				{
					DrawBox((int)EnXL[i], (int)EnYL[i], (int)EnXR[i], (int)EnYR[i], 0xff0000, FALSE);
				}
				else
				{
					DrawBox((int)EnXL[i], (int)EnYL[i], (int)EnXR[i], (int)EnYR[i], 0xffffff, FALSE);
				}
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
				if (enemy[i].direction == 1)
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


		
		if (Px >= enemy[i].x + 50)
		{
			// プレイヤーが敵より右にいるときは右に移動
			// X座標加算
			enemy[i].x += enemy[i].speed;
			enemy[i].direction = 1;

		}
		else
		{
			// プレイヤーが敵より左にいるときは左に移動
			// X座標減算
			enemy[i].x -= enemy[i].speed;
			enemy[i].direction = 0;

		}


		// プレイヤーが敵より上にいるときは浮上する
		if (Py < enemy[i].y || enemy[i].ground == 1)
		{
			enemy[i].speed = 0.6f;
		
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
		
		enemy[i].ground = 0;
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
			enemy[i].flg = 11;
		}
		else if (FPScnt > 41  && FPScnt < 60 )
		{
			enemy[i].flg = 12;
		}
		else
		{
			enemy[i].flg = 10;

			// 10 11 10 12 10 
		}
	}
}

// 敵同士の当たり判定
int Enemy::HitEnemy()
{

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnXL[i] = enemy[i].x + 10.0f;
		EnYL[i] = enemy[i].y + 12.0f;
		EnXR[i] = EnXL[i] + 45.0f;
		EnYR[i] = EnYL[i] + 53.0f;

		if (i == 0)
		{
			if (EnXL[i] <= EnXR[i + 1] && EnYL[i] <= EnYR[i + 1] && EnXR[i] >= EnXL[i + 1] && EnYR[i] >= EnYL[i])
			{
				enemy[i].x -= 10.0f;
				return 1;
			}
		}
		else if (i == 1)
		{
			if (EnXL[i] <= EnXR[i + 1] && EnYL[i] <= EnYR[i + 1] && EnXR[i] >= EnXL[i + 1] && EnYR[i] >= EnYL[i])
			{
				enemy[i].x -= 10.0f;
				return 2;
			}
		}
		else if (i == 2)
		{
			if (EnXL[i] <= EnXR[i - 2] && EnYL[i] <= EnYR[i - 2] && EnXR[i] >= EnXL[i - 2] && EnYR[i] >= EnYL[i])
			{
				enemy[i].x -= 10.0f;
				return 3;
			}
		}
	}

	return 0;
}

// 敵とステージの当たり判定処理
void Enemy::HitStage()
{
	int EnXL[ENEMY_MAX] = { 0 }, EnYL[ENEMY_MAX] = { 0 };//左上
	int EnXR[ENEMY_MAX] = { 0 }, EnYR[ENEMY_MAX] = { 0 };//右下

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnXL[i] = (int)enemy[i].x + 10;
		EnYL[i] = (int)enemy[i].y + 12;
		EnXR[i] = EnXL[i] + 50;
		EnYR[i] = EnYL[i] + 60;
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (EnXL[i] <= S_Ground_Left_XL && EnYR[i] >= S_Ground_Left_YU)
		{//左下の台（側面）
			enemy[i].ground = 1;
			enemy[i].y -= 0.8f;//反発係数？
		}
		else if (EnXR[i] >= S_Ground_Right_XU && EnYR[i] >= S_Ground_Right_YU) 
		{//右下の台（側面）
			enemy[i].ground = 1;
			enemy[i].y -= 0.8f;
		}
		else if (EnXR[i] >= S_Sky_Ground_0_XU && EnXR[i] <= S_Sky_Ground_0_XU && EnYR[i] >= S_Sky_Ground_0_YU  && EnYL[i] <= S_Sky_Ground_0_YL) 
		{//上の台の左（側面）
			enemy[i].ground = 1;
			enemy[i].y -= 0.8f;
		}
		else if (EnXL[i] >= S_Sky_Ground_0_XL && EnXL[i] <= S_Sky_Ground_0_XL && EnYR[i] >= S_Sky_Ground_0_YU && EnYL[i] <= S_Sky_Ground_0_YL) 
		{//上の台の右（側面）
			enemy[i].ground = 1;
			enemy[i].y -= 0.8f;
		}
		else if (EnYL[i] <= S_Sky_Ground_0_YL && EnYR[i] >= S_Sky_Ground_0_YU)
		{//上の台（下辺）
			if (EnXL[i] <= S_Sky_Ground_0_XL && EnXR[i] >= S_Sky_Ground_0_XU)
			{
				enemy[i].y -= 0.8f;
				//if (VectorY >= 0)
				//{//めり込まないようにするために加速度が０以上になると加速度に１足す
				//	VectorY += 1.0f;
				//}
			}
		}
		else if (EnYL[i] <= 0)
		{//画面上の当たり判定
			enemy[i].ground = 1;
			enemy[i].y -= 0.8f;
			//if (VectorY >= 0) 
			//{//めり込まないようにするために加速度が０以上になると加速度に１足す
			//	VectorY += 1.0f;
			//}
		}
	}
}

// 敵とプレイヤーの当たり判定
int Enemy::HitPlayer()
{
	//プレイヤーの矩形の座標
	float PXL, PYL;//左上
	float PXR, PYR;//右下

	PXL = Px + 18;//左上X
	PYL = Py + 14;//左上Y
	PXR = Px + 40;//右下X
	PYR = Py+ 64;//右下Y

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnXL[i] = enemy[i].x + 10.0f;
		EnYL[i] = enemy[i].y + 12.0f;
		EnXR[i] = EnXL[i] + 45.0f;
		EnYR[i] = EnYL[i] + 53.0f;

		if (EnXL[i] <= PXR && EnYL[i] <= PYR && EnXR[i] >= PXL && EnYR[i] >= PYL)
		{
			enemy[i].flg = 17;
			return 1;
		}
	}

	return 0;
}


