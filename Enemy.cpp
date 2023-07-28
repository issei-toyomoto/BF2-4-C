#include "Enemy.h"
#include "Player.h"
#include "Common.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "stdlib.h"
#include<time.h>
#include "InputKey.h"

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

	VectorX = 0;
	VectorY = -1;

	UpCnt = 0;
	DownCnt = 0;

	LoadDivGraph("image/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, EnemyImg[0]);  //画像読み込み(ピンク)
	LoadDivGraph("image/Enemy/Enemy_G_Animation.png", 18, 6, 3, 64, 64, EnemyImg[1]);  //画像読み込み(みどり)
	LoadDivGraph("image/Enemy/Enemy_R_Animation.png", 18, 6, 3, 64, 64, EnemyImg[2]);  //画像読み込み(きいろ)
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

	srand(time(NULL));

	if (StartFlg == 0 && StartMotion < 4)
	{
		StartMove();
	}
	else if (StartFlg != 0)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemy[i].life != 0)
			{
				enemy[i].ran = rand() % 2 + 1;

				HitStage(i);
				HitFlg = HitEnemy(i);
				HitPFlg = HitPlayer(i);
				EnemyMove(i);

				// 敵のX座標範囲
				if (enemy[i].x <= 0.0f)
				{
					enemy[i].x = 640.0f;
				}
				else if (enemy[i].x > 640.0f)
				{
					enemy[i].x = 0.0f;
				}

				// 敵のY座標範囲
				if (enemy[i].y < -19.0f)
				{
					enemy[i].y = -5.0f;
				}
				else if (enemy[i].y > 356.0f)
				{
					enemy[i].y = 356.0f;
				}
			}
			else
			{
				EnemyDie(i);
			}

		}
	}
	

	//１秒たったらフレームカウント
	if (FPScnt > 60) 
	{
		
		FPScnt = 0;
		StartMotion++;
	}

	if (InputKey::GetKeyDown(PAD_INPUT_1) == TRUE) 
	{//Zキーを押したら敵リセット
		EnemyInit();
	}
}

// 描画の更新を実装する
void Enemy::Draw() const 
{
#ifdef _DEBUG
	DrawFormatString(50, 50, 0xffffff, "EnX:%f EnY:%f", enemy[2].x, enemy[2].y);
	DrawFormatString(50, 70, 0xffffff, "Enflg:%d", enemy[0].life);
	DrawFormatString(50, 90, 0xffffff, "Enflg:%d", enemy[1].life);
	DrawFormatString(50, 110, 0xffffff, "Enflg:%d", enemy[2].life);
	DrawFormatString(130, 70, 0xffffff, "die:%f", enemy[0].die);
	DrawFormatString(130, 90, 0xffffff, "Vx:%f", VectorX);
	DrawFormatString(130, 110, 0xffffff, "Vy:%f", VectorY);

	

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].life != 0)
		{
			// 敵の当たり判定表示
			if (enemy[i].state != 3)
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
					if (HitPFlg == i)
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
	}

#endif // DEBUG

	DrawFormatString(180, 30, 0xff0000, "Zキーで敵リセット");

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// 敵画像の表示
		if (enemy[i].life != 6)
		{
			if (StartFlg == 0)
			{
				// スタートモーション時
				DrawGraph((int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);
			}
			else
			{
				// スタート以外
				// 画面内
				if (enemy[i].direction < 1)
				{
					DrawGraph((int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);
				}
				else
				{
					DrawTurnGraph((int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);
				}


				// 画面外
				if (enemy[i].x < 0)
				{
					DrawGraph(640 + (int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);
				}
				else if (enemy[i].x > 640 - 64)
				{
					DrawGraph((int)enemy[i].x - 640, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);
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
		enemy[i].x = ENEMY_X + 85.0f * i;
		enemy[i].y = ENEMY_Y;
		enemy[i].state = 0;
		enemy[i].life = 2;
	}
}

// 敵の移動処理
void Enemy::EnemyMove(int i)
{
	//// 敵のX座標範囲
	//if (enemy[i].x <= 0.0f)
	//{
	//	enemy[i].x = 640.0f;
	//}
	//else if (enemy[i].x > 640.0f)
	//{
	//	enemy[i].x = 0.0f;
	//}

	//// 敵のY座標範囲
	//if (enemy[i].y < -20.0f)
	//{
	//	enemy[i].y = MinY;
	//}
	//else if (enemy[i].y > 356.0f)
	//{
	//	enemy[i].y = 356.0f;
	//}


	// プレイヤーが敵より右にいるときは右に移動する
	if (Px >= enemy[i].x)
	{
		EnemyRight(i);
	}
	else
	{
		// プレイヤーが敵より左にいるときは左に移動する
		EnemyLeft(i);
	}


	// プレイヤーが敵より上にいるときは浮上する
	if (Py < enemy[i].y || enemy[i].ground == 1)
	{
		EnemyUp(i);
	}
	else
	{
		// プレイヤーが敵より下にいるときは降下する
		EnemyDown(i);
	}
	enemy[i].ground = 0;	
}

// 敵のスタート処理
void Enemy::StartMove()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].life != 0)
		{
			HitStart(i);

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
		else
		{
			EnemyDie(i);
		}
	}
}

// 敵の浮上モーション処理
void Enemy::EnemyUp(int e)
{
	// パタパタ手を動かすモーション
	if (FPScnt > 0 && FPScnt < 5 || FPScnt > 11 && FPScnt < 15 || FPScnt > 21 && FPScnt < 25)
	{
		enemy[e].flg = 8;
	}
	else if (FPScnt > 31 && FPScnt < 35 || FPScnt > 41 && FPScnt < 45 || FPScnt > 51 && FPScnt < 55)
	{
		enemy[e].flg = 8;
	}
	else
	{
		enemy[e].flg = 9;
	}

	enemy[e].vecy += 0.05f;

	if (enemy[e].vecy >= 1.0f)
	{
		enemy[e].vecy = 1.0f;
	}

	enemy[e].vecy *= 0.95f;

	enemy[e].y -= enemy[e].vecy;
}

// 敵の降下モーション処理
void Enemy::EnemyDown(int e)
{
	// 降下モーション
	if (enemy[e].ran == 2)
	{
		if (FPScnt > 0 && FPScnt < 20)
		{
			enemy[e].flg = 11;
		}
		else if (FPScnt > 41 && FPScnt < 60)
		{
			enemy[e].flg = 12;
		}
		else
		{
			enemy[e].flg = 10;

			// 10 11 10 12 10 
		}
	}
	
	enemy[e].vecy += 0.06f;

	if (enemy[e].vecy >= 1.5f)
	{
		enemy[e].vecy = 1.5f;
	}

	enemy[e].vecy *= 0.95f;

	enemy[e].y += enemy[e].vecy;

	if (enemy[e].ran == 1)
	{
		// パタパタ手を動かすモーション
		if (FPScnt > 0 && FPScnt < 5 || FPScnt > 11 && FPScnt < 15 || FPScnt > 21 && FPScnt < 25)
		{
			enemy[e].flg = 8;
		}
		else if (FPScnt > 31 && FPScnt < 35 || FPScnt > 41 && FPScnt < 45 || FPScnt > 51 && FPScnt < 55)
		{
			enemy[e].flg = 8;
		}
		else
		{
			enemy[e].flg = 9;
		}

		enemy[e].vecy += 0.05f;

		if (enemy[e].vecy >= 1.0f)
		{
			enemy[e].vecy = 1.0f;
		}

		enemy[e].vecy *= 0.95f;

		enemy[e].y -= enemy[e].vecy;
	}
	
}

// 敵の左移動処理
void Enemy::EnemyLeft(int e)
{
	// プレイヤーが敵より左にいるときは左に移動
    // X座標減算
	enemy[e].direction = 0;

	enemy[e].vecx += 0.05f;

	if (enemy[e].vecx >= 1.0f)
	{
		enemy[e].vecx = 1.0f;
	}

	enemy[e].vecx *= 0.95f;

	enemy[e].x -= enemy[e].vecx;
}

// 敵の右移動処理
void Enemy::EnemyRight(int e)
{
	// プレイヤーが敵より右にいるときは右に移動
	// X座標減算
	enemy[e].direction = 1;

	enemy[e].vecx += 0.05f;

	if (enemy[e].vecx >= 1.0f)
	{
		enemy[e].vecx = 1.0f;
	}

	enemy[e].vecx *= 0.95f;

	enemy[e].x += enemy[e].vecx;

}

// 敵とプレイヤーの当たり判定(スタート時)
int Enemy::HitStart(int e)
{
	// プレイヤーの矩形の座標
	float PXL, PYL;//左上
	float PXR, PYR;//右下

	PXL = Px + 18;//左上X
	PYL = Py + 14;//左上Y
	PXR = Px + 40;//右下X
	PYR = Py + 64;//右下Y


	EnXL[e] = enemy[e].x;
	EnYL[e] = enemy[e].y + 25.0f;
	EnXR[e] = EnXL[e] + 50.0f;
	EnYR[e] = EnYL[e] + 64.0f;


	if (enemy[e].life != 0)
	{
		if (EnXL[e] <= PXR && EnYL[e] <= PYR && EnXR[e] >= PXL && EnYR[e] >= PYL)
		{
			enemy[e].flg = 17;
			// 仮
			enemy[e].life -= 1;
			return e;
		}
	}

	return 3;
}

// 敵同士の当たり判定
int Enemy::HitEnemy(int e)
{
	EnXL[e] = enemy[e].x + 10.0f;
	EnYL[e] = enemy[e].y + 12.0f;
	EnXR[e] = EnXL[e] + 45.0f;
	EnYR[e] = EnYL[e] + 53.0f;

	if (e == 0)
	{
		if (enemy[e + 1].life != 0)
		{
			if (EnXL[e] <= EnXR[e + 1] && EnYL[e] <= EnYR[e + 1] && EnXR[e] >= EnXL[e + 1] && EnYR[e] >= EnYL[e])
			{
				enemy[e].x -= 10.0f;
				return 1;
			}
		}
	}
	else if (e == 1)
	{
		if (enemy[e + 1].life != 0)
		{
			if (EnXL[e] <= EnXR[e + 1] && EnYL[e] <= EnYR[e + 1] && EnXR[e] >= EnXL[e + 1] && EnYR[e] >= EnYL[e])
			{
				enemy[e].x -= 10.0f;
				return 2;
			}
		}
	}
	else if (e == 2)
	{
		if (enemy[e - 2].life != 0)
		{
			if (EnXL[e] <= EnXR[e - 2] && EnYL[e] <= EnYR[e - 2] && EnXR[e] >= EnXL[e - 2] && EnYR[e] >= EnYL[e])
			{
				enemy[e].x -= 10.0f;
				return 3;
			}
		}
	}
	
	return 0;
}

// 敵とステージの当たり判定処理
void Enemy::HitStage(int e)
{
	int EnXL[ENEMY_MAX] = { 0 }, EnYL[ENEMY_MAX] = { 0 };//左上
	int EnXR[ENEMY_MAX] = { 0 }, EnYR[ENEMY_MAX] = { 0 };//右下

	
	EnXL[e] = (int)enemy[e].x + 10;
	EnYL[e] = (int)enemy[e].y + 12;
	EnXR[e] = EnXL[e] + 50;
	EnYR[e] = EnYL[e] + 60;
	

	if (EnXL[e] <= S_Ground_Left_XL && EnYR[e] >= S_Ground_Left_YU)
	{//左下の台（側面）
		enemy[e].ground = 1;
		enemy[e].y -= 0.8f;//反発係数？
	}
	else if (EnXR[e] >= S_Ground_Right_XU && EnYR[e] >= S_Ground_Right_YU) 
	{//右下の台（側面）
		enemy[e].ground = 1;
		enemy[e].y -= 0.8f;
	}
	else if (EnXR[e] >= S_Sky_Ground_0_XU && EnXR[e] <= S_Sky_Ground_0_XU && EnYR[e] >= S_Sky_Ground_0_YU  && EnYL[e] <= S_Sky_Ground_0_YL) 
	{//上の台の左（側面）
		enemy[e].ground = 1;
		enemy[e].y -= 0.8f;
	}
	else if (EnXL[e] >= S_Sky_Ground_0_XL && EnXL[e] <= S_Sky_Ground_0_XL && EnYR[e] >= S_Sky_Ground_0_YU && EnYL[e] <= S_Sky_Ground_0_YL) 
	{//上の台の右（側面）
		enemy[e].ground = 1;
		enemy[e].y -= 0.8f;
	}
	else if (EnYL[e] <= S_Sky_Ground_0_YL && EnYR[e] >= S_Sky_Ground_0_YU)
	{//上の台（下辺）
		if (EnXL[e] <= S_Sky_Ground_0_XL && EnXR[e] >= S_Sky_Ground_0_XU)
		{
			enemy[e].y -= 0.8f;
			//if (VectorY >= 0)
			//{//めり込まないようにするために加速度が０以上になると加速度に１足す
			//	VectorY += 1.0f;
			//}
		}
	}
	else if (EnYL[e] <= 0)
	{//画面上の当たり判定
		enemy[e].ground = 1;
		enemy[e].y -= 0.8f;
		//if (VectorY >= 0) 
		//{//めり込まないようにするために加速度が０以上になると加速度に１足す
		//	VectorY += 1.0f;
		//}
	}
	
}

// 敵とプレイヤーの当たり判定
int Enemy::HitPlayer(int e)
{
	//プレイヤーの矩形の座標
	float PXL, PYL;//左上
	float PXR, PYR;//右下

	PXL = Px + 18;//左上X
	PYL = Py + 14;//左上Y
	PXR = Px + 40;//右下X
	PYR = Py+ 64;//右下Y

	
	EnXL[e] = enemy[e].x + 10.0f;
	EnYL[e] = enemy[e].y + 12.0f;
	EnXR[e] = EnXL[e] + 45.0f;
	EnYR[e] = EnYL[e] + 53.0f;

	
	if (enemy[e].life != 0)
	{
		if (EnXL[e] <= PXR && EnYL[e] <= PYR && EnXR[e] >= PXL && EnYR[e] >= PYL)
		{
			enemy[e].flg = 17;
			// 仮
			enemy[e].life -= 1;
			return e;
		}
	}
		
	return 3;
}

// 敵の死亡モーション処理
void Enemy::EnemyDie(int e)
{
	// パタパタ手を動かすモーション
	if (FPScnt > 0 && FPScnt < 4 || FPScnt > 9 && FPScnt < 12 || FPScnt > 17 && FPScnt < 20)
	{
		enemy[e].flg = 13;
	}
	else if (FPScnt > 25 && FPScnt < 28 || FPScnt > 33 && FPScnt < 36 || FPScnt > 41 && FPScnt < 44)
	{
		enemy[e].flg = 13;
	}
	else if (FPScnt > 49 && FPScnt < 52 || FPScnt > 57 && FPScnt < 60)
	{
		enemy[e].flg = 13;
	}
	else
	{
		enemy[e].flg = 14;
	}

	if (enemy[e].die <= 8)
	{
		enemy[e].die++;
		enemy[e].y -= 2.8f;
	}
	else if(enemy[e].die <= 15)
	{
		enemy[e].die++;
	}
	else if(enemy[e].y <= 490.0f)
	{
		enemy[e].y += 3.0f;
	}
}



