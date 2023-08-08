#include "Enemy.h"
#include "Player.h"
#include "Common.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "stdlib.h"
#include<time.h>
#include "InputKey.h"

int Enemy::HitPFlg = 0;

// コンストラクタ
Enemy::Enemy()
{
	EnemyInit();

	StartFlg = 0;   // スタート状態か判定する用
	Fcnt = 0;     // FPSカウント
	StartMotion = 0;          // スタート時、敵のモーション管理用
	Px = 0;         // プレイヤーのX座標
	Py = 0;         // プレイヤーのY座標
	HitFlg = 0;
	HitPeFlg = 0;
	UpCnt = 0;
	DownCnt = 0;
	NowStage = 0;
	
	LoadDivGraph("image/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, EnemyImg[0]);  //画像読み込み(ピンク)
	LoadDivGraph("image/Enemy/Enemy_G_Animation.png", 18, 6, 3, 64, 64, EnemyImg[1]);  //画像読み込み(みどり)
	LoadDivGraph("image/Enemy/Enemy_R_Animation.png", 18, 6, 3, 64, 64, EnemyImg[2]);  //画像読み込み(きいろ)
}

// デストラクタ
Enemy::~Enemy()
{

}

// 描画以外の更新を実装する
void Enemy::Update(int nowstage)
{
	
	Fcnt++;

	NowStage = nowstage;

	// プレイヤーの座標取得
	Px = Player::PlayerX;
	Py = Player::PlayerY;

	srand(time(NULL));

	if (StartFlg == 0 && StartMotion < 4)
	{
		StartMove();
	}
	else
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemy[i].start == 1 && enemy[i].sm < 4)
			{
				StartMove(i);
			}
			else
			{
				if (enemy[i].life == 2)
				{
					enemy[i].ran = rand() % 2 + 1;

					HitStage(i);
					HitFlg = HitEnemy(i);
					HitPeFlg = HitPlayer(i);
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
				else if (enemy[i].life == 1)
				{
					EnemyPara(i);
				}
				else
				{
					EnemyDie(i);
				}

			}
		}
	}
	

	//１秒たったらフレームカウント
	if (Fcnt > 60) 
	{
		Fcnt = 0;

		if (StartFlg == 0)
		{
			StartMotion++;
		}

		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemy[i].start == 1)
			{
				enemy[i].sm++;
			}
		}
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
	DrawFormatString(130, 70, 0xffffff, "Hit:%d", HitPFlg);
	DrawFormatString(130, 90, 0xffffff, "Vx:%f", enemy[0].vecx);
	DrawFormatString(130, 110, 0xffffff, "Vy:%f", enemy[0].vecy);

	

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].life == 2)
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
					if (HitPeFlg == i)
					{
						DrawBox((int)EnXL[i], (int)EnYL[i], (int)EnXR[i], (int)EnYR[i], 0xff0000, FALSE);
					}
					else
					{
						// 風船ありの敵の範囲（白）
						DrawBox((int)EnXL[i], (int)EnYL[i], (int)EnXR[i], (int)EnYR[i], 0xffffff, FALSE);
						// 風船抜きの敵の範囲（緑）
						DrawBox((int)EnXL[i], (int)EnYL[i] + 20, (int)EnXR[i], (int)EnYR[i], 0x00ff00, FALSE);
						// 風船抜きの敵の範囲の半分（青）
						DrawBox((int)EnXL[i], (int)EnYL[i]+36, (int)EnXR[i], (int)EnYR[i], 0x0000ff, FALSE);
					}
				}
			}
		}
		else if (enemy[i].life == 1)
		{
		}
	}

#endif // DEBUG

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// 敵画像の表示
		if (enemy[i].life == 2)
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
		else
		{
			// スタート以外
			// 画面内
			DrawGraph((int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);

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

// 敵の初期化処理
void Enemy::EnemyInit()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].x = ENEMY_X + 85.0f * i;
		enemy[i].y = ENEMY_Y;
		enemy[i].state = 0;
		enemy[i].life = 2;
		enemy[i].sm = 0;
	}
}

// 敵の移動処理
void Enemy::EnemyMove(int i)
{
	// プレイヤーが敵より右にいるときは右に移動する
	if (Px >= enemy[i].x)
	{
		EnemyRight(i);

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

	}
	else
	{
		// プレイヤーが敵より左にいるときは左に移動する
		EnemyLeft(i);

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
	}

	enemy[i].ground = 0;	
}

void Enemy::StartMove()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].life != 0)
		{
			HitPeFlg = HitStart(i);

			if (StartMotion == 0)
			{
				if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
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
				if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
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
				if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
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
				if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
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

// 敵のスタート処理
void Enemy::StartMove(int i)
{
	if (enemy[i].life != 0)
	{
		HitPeFlg = HitStart(i);

		if (enemy[i].sm == 0)
		{
			if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
			{
				enemy[i].flg = 0;
			}
			else
			{
				enemy[i].flg = 1;
			}
		}
		else if (enemy[i].sm == 1)
		{
			if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
			{
				enemy[i].flg = 2;
			}
			else
			{
				enemy[i].flg = 3;
			}
		}
		else if (enemy[i].sm == 2)
		{
			if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
			{
				enemy[i].flg = 4;
			}
			else
			{
				enemy[i].flg = 5;
			}
		}
		else if (enemy[i].sm == 3)
		{
			if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
			{
				enemy[i].flg = 6;
			}
			else
			{
				enemy[i].flg = 7;

				if (enemy[i].state != 2)
				{
					enemy[i].state++;
				}

				enemy[i].okballoon = 0;
				enemy[i].start = 0;
				enemy[i].sm = 0;
			}
		}
	}
	else
	{
		EnemyDie(i);
	}
	
}

// 敵の浮上モーション処理
void Enemy::EnemyUp(int e)
{
	// パタパタ手を動かすモーション
	if (Fcnt > 0 && Fcnt < 5 || Fcnt > 11 && Fcnt < 15 || Fcnt > 21 && Fcnt < 25)
	{
		enemy[e].flg = 8;
	}
	else if (Fcnt > 31 && Fcnt < 35 || Fcnt > 41 && Fcnt < 45 || Fcnt > 51 && Fcnt < 55)
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
		if (Fcnt > 0 && Fcnt < 20)
		{
			enemy[e].flg = 11;
		}
		else if (Fcnt > 41 && Fcnt < 60)
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
		if (Fcnt > 0 && Fcnt < 5 || Fcnt > 11 && Fcnt < 15 || Fcnt > 21 && Fcnt < 25)
		{
			enemy[e].flg = 8;
		}
		else if (Fcnt > 31 && Fcnt < 35 || Fcnt > 41 && Fcnt < 45 || Fcnt > 51 && Fcnt < 55)
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

// 敵のパラシュート処理
void Enemy::EnemyPara(int e)
{
	float amplitude = 0.85f;  // 揺れの振幅
	float frequency = 0.9f;   // 揺れの周波数

	if (enemy[e].para <= 1)
	{
		enemy[e].flg = 15;
		enemy[e].para++;
	}
	else if(enemy[e].para <= 4)
	{
		enemy[e].flg = 16;
		enemy[e].para++;
	}
	else
	{
		enemy[e].para = 5;
		enemy[e].flg = 17;
		
		enemy[e].x += amplitude * sin(frequency * GetNowCount() / 1000.0f);

		enemy[e].y += 0.3f;

		// パラシュート状態確認時コメントアウト
		/*HitPeFlg = HitPlayer(e);*/

		HitStage(e);

		// 地面に着いたら風船を膨らませる
		if (enemy[e].ground == 1)
		{
			enemy[e].life = 2;
			enemy[e].start = 1;
		}
	}
}

// 敵の死亡モーション処理
void Enemy::EnemyDie(int e)
{
	// パタパタ手を動かすモーション
	if (Fcnt > 0 && Fcnt < 4 || Fcnt > 9 && Fcnt < 12 || Fcnt > 17 && Fcnt < 20)
	{
		enemy[e].flg = 13;
	}
	else if (Fcnt > 25 && Fcnt < 28 || Fcnt > 33 && Fcnt < 36 || Fcnt > 41 && Fcnt < 44)
	{
		enemy[e].flg = 13;
	}
	else if (Fcnt > 49 && Fcnt < 52 || Fcnt > 57 && Fcnt < 60)
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
	else if (enemy[e].die <= 15)
	{
		enemy[e].die++;
	}
	else if (enemy[e].y <= 490.0f)
	{
		enemy[e].y += 3.0f;
	}
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
	EnXL[e] = enemy[e].x + 10.0f;//左上X
	EnYL[e] = enemy[e].y + 12.0f;//左上Y
	EnXR[e] = EnXL[e] + 45.0f;//右下X
	EnYR[e] = EnYL[e] + 53.0f;//右下Y

	if (NowStage == 1) {//***************　１ステージ　***************//
/*******************************************************************************************************************************/
		//側面の当たり判定//
/*******************************************************************************************************************************/
		if (enemy[e].ground == 0) {
			if (EnXL[e] <= S_Ground_Left_XL && EnYR[e] >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}

			if (EnXR[e] >= S_Ground_Right_XU && EnYR[e] >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}

			if (EnYR[e] >= S_Sky_Ground_0_YU + PlusPx && EnYL[e] <= S_Sky_Ground_0_YL - PlusPx) {//上の台（側面）
				if (EnXL[e] <= S_Sky_Ground_0_XL + PlusPx && EnXR[e] >= S_Sky_Ground_0_XL) {//上の台の右
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						enemy[e].vecx += 0.9f;
					}
				}
				else if (EnXR[e] >= S_Sky_Ground_0_XU - PlusPx && EnXR[e] <= S_Sky_Ground_0_XU) {//上の台の左
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
						enemy[e].vecx -= 0.9f;
					}
				}
			}
			/*******************************************************************************************************************************/
					//下辺の当たり判定//
			/*******************************************************************************************************************************/
			if (EnYL[e] <= S_Sky_Ground_0_YL - PlusPx && EnYR[e] >= S_Sky_Ground_0_YL) {//上の台（下辺）
				if (EnXL[e] <= S_Sky_Ground_0_XL && EnXR[e] >= S_Sky_Ground_0_XU) {
					enemy[e].vecy *= -COR;
					if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						enemy[e].vecy += 0.9f;
					}
				}
			}

			if (EnYL[e] <= 0) {//画面上の当たり判定
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		/*******************************************************************************************************************************/
				//上辺の当たり判定//
		/*******************************************************************************************************************************/
		if (EnYR[e] >= S_Ground_Left_YU && EnYR[e] <= S_Ground_Left_YU + PlusPx && EnXL[e] <= S_Ground_Left_XL) {//左下の台（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Ground_Right_YU && EnYR[e] <= S_Ground_Right_YU + PlusPx && EnXR[e] >= S_Ground_Right_XU) {//右下の台（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Sky_Ground_0_YU && EnYR[e] <= S_Sky_Ground_0_YU + PlusPx && EnXL[e] <= S_Sky_Ground_0_XL && EnXR[e] >= S_Sky_Ground_0_XU) {//浮いている中央の台（上辺）
			enemy[e].ground = 1;
		}
		else {
			enemy[e].ground = 0;
		}
	}
	else if (NowStage == 2) {//***************　２ステージ　***************//
/*******************************************************************************************************************************/
		//側面の当たり判定//
/*******************************************************************************************************************************/
		if (enemy[e].ground == 0) {
			if (EnXL[e] <= S_Ground_Left_XL && EnYR[e] >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}

			if (EnXR[e] >= S_Ground_Right_XU && EnYR[e] >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}

			if (EnYR[e] >= S_Sky_Ground_0_YU + PlusPx && EnYL[e] <= S_Sky_Ground_0_YL - PlusPx) {//上の台（側面）
				if (EnXL[e] <= S_Sky_Ground_0_XL + PlusPx && EnXR[e] >= S_Sky_Ground_0_XL) {//上の台の右
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						enemy[e].vecx += 0.9f;
					}
				}
				else if (EnXR[e] >= S_Sky_Ground_0_XU - PlusPx && EnXR[e] <= S_Sky_Ground_0_XU) {//上の台の左
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
						enemy[e].vecx -= 0.9f;
					}
				}
			}

			if (EnYR[e] >= S2_Sky_Ground_0_YU + PlusPx && EnYL[e] <= S2_Sky_Ground_0_YL - PlusPx) {//左上の台（側面）
				if (EnXL[e] <= S2_Sky_Ground_0_XL + PlusPx && EnXR[e] >= S2_Sky_Ground_0_XL) {//左上の台の右
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						enemy[e].vecx += 0.9f;
					}
				}
				else if (EnXR[e] >= S2_Sky_Ground_0_XU - PlusPx && EnXR[e] <= S2_Sky_Ground_0_XU) {//左上の台の左
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
						enemy[e].vecx -= 0.9f;
					}
				}
			}

			if (EnYR[e] >= S2_Sky_Ground_1_YU + PlusPx && EnYL[e] <= S2_Sky_Ground_1_YL - PlusPx) {//右上の台（側面）
				if (EnXL[e] <= S2_Sky_Ground_1_XL + PlusPx && EnXR[e] >= S2_Sky_Ground_1_XL) {//右上の台の右
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						enemy[e].vecx += 0.9f;
					}
				}
				else if (EnXR[e] >= S2_Sky_Ground_1_XU - PlusPx && EnXR[e] <= S2_Sky_Ground_1_XU) {//右上の台の左
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
						enemy[e].vecx -= 0.9f;
					}
				}
			}
			/*******************************************************************************************************************************/
					//下辺の当たり判定//
			/*******************************************************************************************************************************/
			if (EnYL[e] <= S_Sky_Ground_0_YL - PlusPx && EnYR[e] >= S_Sky_Ground_0_YL) {//上の台（下辺）
				if (EnXL[e] <= S_Sky_Ground_0_XL && EnXR[e] >= S_Sky_Ground_0_XU) {
					enemy[e].vecy *= -COR;
					if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						enemy[e].vecy += 0.9f;
					}
				}
			}

			if (EnYL[e] <= S2_Sky_Ground_0_YL - PlusPx && EnYR[e] >= S2_Sky_Ground_0_YL) {//左上の台（下辺）
				if (EnXL[e] <= S2_Sky_Ground_0_XL && EnXR[e] >= S2_Sky_Ground_0_XU) {
					enemy[e].vecy *= -COR;
					if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						enemy[e].vecy += 0.9f;
					}
				}
			}

			if (EnYL[e] <= S2_Sky_Ground_1_YL - PlusPx && EnYR[e] >= S2_Sky_Ground_1_YL) {//右上の台（下辺）
				if (EnXL[e] <= S2_Sky_Ground_1_XL && EnXR[e] >= S2_Sky_Ground_1_XU) {
					enemy[e].vecy *= -COR;
					if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						enemy[e].vecy += 0.9f;
					}
				}
			}

			if (EnYL[e] <= 0) {//画面上の当たり判定
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}
		/*******************************************************************************************************************************/
				//上辺の当たり判定//
		/*******************************************************************************************************************************/
		if (EnYR[e] >= S_Ground_Left_YU && EnYR[e] <= S_Ground_Left_YU + PlusPx && EnXL[e] <= S_Ground_Left_XL) {//左下の台（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Ground_Right_YU && EnYR[e] <= S_Ground_Right_YU + PlusPx && EnXR[e] >= S_Ground_Right_XU) {//右下の台（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Sky_Ground_0_YU && EnYR[e] <= S_Sky_Ground_0_YU + PlusPx && EnXL[e] <= S_Sky_Ground_0_XL && EnXR[e] >= S_Sky_Ground_0_XU) {//浮いている中央の台（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S2_Sky_Ground_0_YU && EnYR[e] <= S2_Sky_Ground_0_YU + PlusPx && EnXL[e] <= S2_Sky_Ground_0_XL && EnXR[e] >= S2_Sky_Ground_0_XU) {//浮いている左上の台（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S2_Sky_Ground_1_YU && EnYR[e] <= S2_Sky_Ground_1_YU + PlusPx && EnXL[e] <= S2_Sky_Ground_1_XL && EnXR[e] >= S2_Sky_Ground_1_XU) {//浮いている左上の台（上辺）
			enemy[e].ground = 1;
		}
		else {
			enemy[e].ground = 0;
		}
	}
	else if (NowStage == 3) {//***************　３ステージ　***************//
/*******************************************************************************************************************************/
		//側面の当たり判定//
/*******************************************************************************************************************************/
		if (enemy[e].ground == 0) {
			if (EnXL[e] <= S_Ground_Left_XL && EnYR[e] >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}

			if (EnXR[e] >= S_Ground_Right_XU && EnYR[e] >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_SGround_0_YU + PlusPx && EnYL[e] <= S3_Sky_SGround_0_YL - PlusPx) {//左鍾乳石（地面）
			if (EnXL[e] <= S3_Sky_SGround_0_XL + PlusPx && EnXR[e] >= S3_Sky_SGround_0_XL) {//左鍾乳石の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_SGround_0_XU - PlusPx && EnXR[e] <= S3_Sky_SGround_0_XU) {//左鍾乳石の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_SStone_0_YU + PlusPx && EnYL[e] <= S3_Sky_SStone_0_YL - PlusPx) {//左鍾乳石（石）
			if (EnXL[e] <= S3_Sky_SStone_0_XL + PlusPx && EnXR[e] >= S3_Sky_SStone_0_XL) {//左鍾乳石の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_SStone_0_XU - PlusPx && EnXR[e] <= S3_Sky_SStone_0_XU) {//左鍾乳石の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_SGround_1_YU + PlusPx && EnYL[e] <= S3_Sky_SGround_1_YL - PlusPx) {//中央鍾乳石（地面）
			if (EnXL[e] <= S3_Sky_SGround_1_XL + PlusPx && EnXR[e] >= S3_Sky_SGround_1_XL) {//中央鍾乳石の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_SGround_1_XU - PlusPx && EnXR[e] <= S3_Sky_SGround_1_XU) {//中央鍾乳石の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_SStone_1_YU + PlusPx && EnYL[e] <= S3_Sky_SStone_1_YL - PlusPx) {//中央鍾乳石（石）
			if (EnXL[e] <= S3_Sky_SStone_1_XL + PlusPx && EnXR[e] >= S3_Sky_SStone_1_XL) {//中央鍾乳石の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_SStone_1_XU - PlusPx && EnXR[e] <= S3_Sky_SStone_1_XU) {//中央鍾乳石の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_SGround_2_YU + PlusPx && EnYL[e] <= S3_Sky_SGround_2_YL - PlusPx) {//右鍾乳石（地面）
			if (EnXL[e] <= S3_Sky_SGround_2_XL + PlusPx && EnXR[e] >= S3_Sky_SGround_2_XL) {//右鍾乳石の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_SGround_2_XU - PlusPx && EnXR[e] <= S3_Sky_SGround_2_XU) {//右鍾乳石の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_SStone_2_YU + PlusPx && EnYL[e] <= S3_Sky_SStone_2_YL - PlusPx) {//右鍾乳石（石）
			if (EnXL[e] <= S3_Sky_SStone_2_XL + PlusPx && EnXR[e] >= S3_Sky_SStone_2_XL) {//右鍾乳石の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_SStone_2_XU - PlusPx && EnXR[e] <= S3_Sky_SStone_2_XU) {//右鍾乳石の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_Ground_0_YU + PlusPx && EnYL[e] <= S3_Sky_Ground_0_YL - PlusPx) {//上空中床
			if (EnXL[e] <= S3_Sky_Ground_0_XL + PlusPx && EnXR[e] >= S3_Sky_Ground_0_XL) {//上空中床の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_Ground_0_XU - PlusPx && EnXR[e] <= S3_Sky_Ground_0_XU) {//上空中床の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_Ground_1_YU + PlusPx && EnYL[e] <= S3_Sky_Ground_1_YL - PlusPx) {//下空中床
			if (EnXL[e] <= S3_Sky_Ground_1_XL + PlusPx && EnXR[e] >= S3_Sky_Ground_1_XL) {//下空中床の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_Ground_1_XU - PlusPx && EnXR[e] <= S3_Sky_Ground_1_XU) {//下空中床の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}
		/*******************************************************************************************************************************/
				//下辺の当たり判定//
		/*******************************************************************************************************************************/
		if (EnYL[e] <= S3_Sky_SGround_0_YL - PlusPx && EnYR[e] >= S3_Sky_SGround_0_YL) {//左鍾乳石（地面）（下辺）
			if (EnXL[e] <= S3_Sky_SGround_0_XL && EnXR[e] >= S3_Sky_SGround_0_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_SStone_0_YL - PlusPx && EnYR[e] >= S3_Sky_SStone_0_YL) {//左鍾乳石（石）（下辺）
			if (EnXL[e] <= S3_Sky_SStone_0_XL && EnXR[e] >= S3_Sky_SStone_0_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_SGround_1_YL - PlusPx && EnYR[e] >= S3_Sky_SGround_1_YL) {//中央鍾乳石（地面）（下辺）
			if (EnXL[e] <= S3_Sky_SGround_1_XL && EnXR[e] >= S3_Sky_SGround_1_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_SStone_1_YL - PlusPx && EnYR[e] >= S3_Sky_SStone_1_YL) {//中央鍾乳石（石）（下辺）
			if (EnXL[e] <= S3_Sky_SStone_1_XL && EnXR[e] >= S3_Sky_SStone_1_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_SGround_2_YL - PlusPx && EnYR[e] >= S3_Sky_SGround_2_YL) {//左鍾乳石（地面）（下辺）
			if (EnXL[e] <= S3_Sky_SGround_2_XL && EnXR[e] >= S3_Sky_SGround_2_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_SStone_2_YL - PlusPx && EnYR[e] >= S3_Sky_SStone_2_YL) {//左鍾乳石（石）（下辺）
			if (EnXL[e] <= S3_Sky_SStone_2_XL && EnXR[e] >= S3_Sky_SStone_2_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_Ground_0_YL - PlusPx && EnYR[e] >= S3_Sky_Ground_0_YL) {//上空中床（下辺）
			if (EnXL[e] <= S3_Sky_Ground_0_XL && EnXR[e] >= S3_Sky_Ground_0_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_Ground_1_YL - PlusPx && EnYR[e] >= S3_Sky_Ground_1_YL) {//下空中床（下辺）
			if (EnXL[e] <= S3_Sky_Ground_1_XL && EnXR[e] >= S3_Sky_Ground_1_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= 0) {//画面上の当たり判定
			enemy[e].vecy *= -COR;
			if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
				enemy[e].vecy += 0.9f;
			}
		}

		/*******************************************************************************************************************************/
				//上辺の当たり判定//
		/*******************************************************************************************************************************/

		if (EnYR[e] >= S_Ground_Left_YU && EnYR[e] <= S_Ground_Left_YU + PlusPx && EnXL[e] <= S_Ground_Left_XL) {//左下の台（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Ground_Right_YU && EnYR[e] <= S_Ground_Right_YU + PlusPx && EnXR[e] >= S_Ground_Right_XU) {//右下の台（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S3_Sky_SGround_0_YU && EnYR[e] <= S3_Sky_SGround_0_YU + PlusPx && EnXL[e] <= S3_Sky_SGround_0_XL && EnXR[e] >= S3_Sky_SGround_0_XU) {//左鍾乳石（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S3_Sky_SGround_1_YU && EnYR[e] <= S3_Sky_SGround_1_YU + PlusPx && EnXL[e] <= S3_Sky_SGround_1_XL && EnXR[e] >= S3_Sky_SGround_1_XU) {//中央鍾乳石（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S3_Sky_SGround_2_YU && EnYR[e] <= S3_Sky_SGround_2_YU + PlusPx && EnXL[e] <= S3_Sky_SGround_2_XL && EnXR[e] >= S3_Sky_SGround_2_XU) {//右鍾乳石（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S3_Sky_Ground_0_YU && EnYR[e] <= S3_Sky_Ground_0_YU + PlusPx && EnXL[e] <= S3_Sky_Ground_0_XL && EnXR[e] >= S3_Sky_Ground_0_XU) {//上空中床（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S3_Sky_Ground_1_YU && EnYR[e] <= S3_Sky_Ground_1_YU + PlusPx && EnXL[e] <= S3_Sky_Ground_1_XL && EnXR[e] >= S3_Sky_Ground_1_XU) {//下空中床（上辺）
			enemy[e].ground = 1;
		}
		else {
			enemy[e].ground = 0;
		}
	}
	else if (NowStage == 4) {//***************　４ステージ　***************//
/*******************************************************************************************************************************/
		//側面の当たり判定//
/*******************************************************************************************************************************/
		if (enemy[e].ground == 0) {
			if (EnXL[e] <= S_Ground_Left_XL && EnYR[e] >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}

			if (EnXR[e] >= S_Ground_Right_XU && EnYR[e] >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S4_Sky_Ground_0_YU + PlusPx && EnYL[e] <= S4_Sky_Ground_0_YL - PlusPx) {//１番左
			if (EnXL[e] <= S4_Sky_Ground_0_XL + PlusPx && EnXR[e] >= S4_Sky_Ground_0_XL) {//１番左の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S4_Sky_Ground_0_XU - PlusPx && EnXR[e] <= S4_Sky_Ground_0_XU) {//１番左の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S4_Sky_Ground_1_YU + PlusPx && EnYL[e] <= S4_Sky_Ground_1_YL - PlusPx) {//左から２番目
			if (EnXL[e] <= S4_Sky_Ground_1_XL + PlusPx && EnXR[e] >= S4_Sky_Ground_1_XL) {//左から２番目の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S4_Sky_Ground_1_XU - PlusPx && EnXR[e] <= S4_Sky_Ground_1_XU) {//左から２番目の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S4_Sky_Ground_2_YU + PlusPx && EnYL[e] <= S4_Sky_Ground_2_YL - PlusPx) {//１番上
			if (EnXL[e] <= S4_Sky_Ground_2_XL + PlusPx && EnXR[e] >= S4_Sky_Ground_2_XL) {//１番上の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S4_Sky_Ground_2_XU - PlusPx && EnXR[e] <= S4_Sky_Ground_2_XU) {//１番上の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S4_Sky_Ground_3_YU + PlusPx && EnYL[e] <= S4_Sky_Ground_3_YL - PlusPx) {//１番下
			if (EnXL[e] <= S4_Sky_Ground_3_XL + PlusPx && EnXR[e] >= S4_Sky_Ground_3_XL) {//１番下の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S4_Sky_Ground_3_XU - PlusPx && EnXR[e] <= S4_Sky_Ground_3_XU) {//１番下の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S4_Sky_Ground_4_YU + PlusPx && EnYL[e] <= S4_Sky_Ground_4_YL - PlusPx) {//１番右
			if (EnXL[e] <= S4_Sky_Ground_4_XL + PlusPx && EnXR[e] >= S4_Sky_Ground_4_XL) {//１番右の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S4_Sky_Ground_4_XU - PlusPx && EnXR[e] <= S4_Sky_Ground_4_XU) {//１番右の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}
		/*******************************************************************************************************************************/
				//下辺の当たり判定//
		/*******************************************************************************************************************************/
		if (EnYL[e] <= S4_Sky_Ground_0_YL - PlusPx && EnYR[e] >= S4_Sky_Ground_0_YL) {//１番左
			if (EnXL[e] <= S4_Sky_Ground_0_XL && EnXR[e] >= S4_Sky_Ground_0_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S4_Sky_Ground_1_YL - PlusPx && EnYR[e] >= S4_Sky_Ground_1_YL) {//左から２番目
			if (EnXL[e] <= S4_Sky_Ground_1_XL && EnXR[e] >= S4_Sky_Ground_1_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S4_Sky_Ground_2_YL - PlusPx && EnYR[e] >= S4_Sky_Ground_2_YL) {//１番上
			if (EnXL[e] <= S4_Sky_Ground_2_XL && EnXR[e] >= S4_Sky_Ground_2_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S4_Sky_Ground_3_YL - PlusPx && EnYR[e] >= S4_Sky_Ground_3_YL) {//１番下
			if (EnXL[e] <= S4_Sky_Ground_3_XL && EnXR[e] >= S4_Sky_Ground_3_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S4_Sky_Ground_4_YL - PlusPx && EnYR[e] >= S4_Sky_Ground_4_YL) {//１番右
			if (EnXL[e] <= S4_Sky_Ground_4_XL && EnXR[e] >= S4_Sky_Ground_4_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= 0) {//画面上の当たり判定
			enemy[e].vecy *= -COR;
			if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
				enemy[e].vecy += 0.9f;
			}
		}

		/*******************************************************************************************************************************/
				//上辺の当たり判定//
		/*******************************************************************************************************************************/

		if (EnYR[e] >= S_Ground_Left_YU && EnYR[e] <= S_Ground_Left_YU + PlusPx && EnXL[e] <= S_Ground_Left_XL) {//左下の台（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Ground_Right_YU && EnYR[e] <= S_Ground_Right_YU + PlusPx && EnXR[e] >= S_Ground_Right_XU) {//右下の台（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S4_Sky_Ground_0_YU && EnYR[e] <= S4_Sky_Ground_0_YU + PlusPx && EnXL[e] <= S4_Sky_Ground_0_XL && EnXR[e] >= S4_Sky_Ground_0_XU) {//１番左の台
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S4_Sky_Ground_1_YU && EnYR[e] <= S4_Sky_Ground_1_YU + PlusPx && EnXL[e] <= S4_Sky_Ground_1_XL && EnXR[e] >= S4_Sky_Ground_1_XU) {//左から２番目の台
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S4_Sky_Ground_2_YU && EnYR[e] <= S4_Sky_Ground_2_YU + PlusPx && EnXL[e] <= S4_Sky_Ground_2_XL && EnXR[e] >= S4_Sky_Ground_2_XU) {//１番上の台
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S4_Sky_Ground_3_YU && EnYR[e] <= S4_Sky_Ground_3_YU + PlusPx && EnXL[e] <= S4_Sky_Ground_3_XL && EnXR[e] >= S4_Sky_Ground_3_XU) {//１番下の台
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S4_Sky_Ground_4_YU && EnYR[e] <= S4_Sky_Ground_4_YU + PlusPx && EnXL[e] <= S4_Sky_Ground_4_XL && EnXR[e] >= S4_Sky_Ground_4_XU) {//１番右の台
			enemy[e].ground = 1;
		}
		else {
			enemy[e].ground = 0;
		}
	}
	else if (NowStage == 5) {//***************　５ステージ　***************//
/*******************************************************************************************************************************/
		//側面の当たり判定//
/*******************************************************************************************************************************/
		if (enemy[e].ground == 0) {
			if (EnXL[e] <= S_Ground_Left_XL && EnYR[e] >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}

			if (EnXR[e] >= S_Ground_Right_XU && EnYR[e] >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S5_Sky_SGround_0_YU + PlusPx && EnYL[e] <= S5_Sky_SGround_0_YL - PlusPx) {//左鍾乳石
			if (EnXL[e] <= S5_Sky_SGround_0_XL + PlusPx && EnXR[e] >= S5_Sky_SGround_0_XL) {//左鍾乳石の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S5_Sky_SGround_0_XU - PlusPx && EnXR[e] <= S5_Sky_SGround_0_XU) {//左鍾乳石の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S5_Sky_SGround_1_YU + PlusPx && EnYL[e] <= S5_Sky_SGround_1_YL - PlusPx) {//中央鍾乳石
			if (EnXL[e] <= S5_Sky_SGround_1_XL + PlusPx && EnXR[e] >= S5_Sky_SGround_1_XL) {//中央鍾乳石の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S5_Sky_SGround_1_XU - PlusPx && EnXR[e] <= S5_Sky_SGround_1_XU) {//中央鍾乳石の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S5_Sky_SGround_2_YU + PlusPx && EnYL[e] <= S5_Sky_SGround_2_YL - PlusPx) {//右鍾乳石
			if (EnXL[e] <= S5_Sky_SGround_2_XL + PlusPx && EnXR[e] >= S5_Sky_SGround_2_XL) {//右鍾乳石の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S5_Sky_SGround_2_XU - PlusPx && EnXR[e] <= S5_Sky_SGround_2_XU) {//右鍾乳石の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S5_Sky_Ground_0_YU + PlusPx && EnYL[e] <= S5_Sky_Ground_0_YL - PlusPx) {//１番上
			if (EnXL[e] <= S5_Sky_Ground_0_XL + PlusPx && EnXR[e] >= S5_Sky_Ground_0_XL) {//１番上の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S5_Sky_Ground_0_XU - PlusPx && EnXR[e] <= S5_Sky_Ground_0_XU) {//１番上の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S5_Sky_Ground_1_YU + PlusPx && EnYL[e] <= S5_Sky_Ground_1_YL - PlusPx) {//下の右
			if (EnXL[e] <= S5_Sky_Ground_1_XL + PlusPx && EnXR[e] >= S5_Sky_Ground_1_XL) {//下の右の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S5_Sky_Ground_1_XU - PlusPx && EnXR[e] <= S5_Sky_Ground_1_XU) {//下の右の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S5_Sky_Ground_2_YU + PlusPx && EnYL[e] <= S5_Sky_Ground_2_YL - PlusPx) {//下の左
			if (EnXL[e] <= S5_Sky_Ground_2_XL + PlusPx && EnXR[e] >= S5_Sky_Ground_2_XL) {//下の左の右
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S5_Sky_Ground_2_XU - PlusPx && EnXR[e] <= S5_Sky_Ground_2_XU) {//下の左の左
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					enemy[e].vecx -= 0.9f;
				}
			}
		}
		/*******************************************************************************************************************************/
				//下辺の当たり判定//
		/*******************************************************************************************************************************/
		if (EnYL[e] <= S5_Sky_SGround_0_YL - PlusPx && EnYR[e] >= S5_Sky_SGround_0_YL) {//右鍾乳石
			if (EnXL[e] <= S5_Sky_SGround_0_XL && EnXR[e] >= S5_Sky_SGround_0_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S5_Sky_SGround_1_YL - PlusPx && EnYR[e] >= S5_Sky_SGround_1_YL) {//中央鍾乳石
			if (EnXL[e] <= S5_Sky_SGround_1_XL && EnXR[e] >= S5_Sky_SGround_1_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S5_Sky_SGround_2_YL - PlusPx && EnYR[e] >= S5_Sky_SGround_2_YL) {//右鍾乳石
			if (EnXL[e] <= S5_Sky_SGround_2_XL && EnXR[e] >= S5_Sky_SGround_2_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S5_Sky_Ground_0_YL - PlusPx && EnYR[e] >= S5_Sky_Ground_0_YL) {//１番上
			if (EnXL[e] <= S5_Sky_Ground_0_XL && EnXR[e] >= S5_Sky_Ground_0_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S5_Sky_Ground_1_YL - PlusPx && EnYR[e] >= S5_Sky_Ground_1_YL) {//下の右
			if (EnXL[e] <= S5_Sky_Ground_1_XL && EnXR[e] >= S5_Sky_Ground_1_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S5_Sky_Ground_2_YL - PlusPx && EnYR[e] >= S5_Sky_Ground_2_YL) {//下の左
			if (EnXL[e] <= S5_Sky_Ground_2_XL && EnXR[e] >= S5_Sky_Ground_2_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= 0) {//画面上の当たり判定
			enemy[e].vecy *= -COR;
			if (enemy[e].vecy >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
				enemy[e].vecy += 0.9f;
			}
		}

		/*******************************************************************************************************************************/
				//上辺の当たり判定//
		/*******************************************************************************************************************************/

		if (EnYR[e] >= S_Ground_Left_YU && EnYR[e] <= S_Ground_Left_YU + PlusPx && EnXL[e] <= S_Ground_Left_XL) {//左下の台（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Ground_Right_YU && EnYR[e] <= S_Ground_Right_YU + PlusPx && EnXR[e] >= S_Ground_Right_XU) {//右下の台（上辺）
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S5_Sky_SGround_0_YU && EnYR[e] <= S5_Sky_SGround_0_YU + PlusPx && EnXL[e] <= S5_Sky_SGround_0_XL && EnXR[e] >= S5_Sky_SGround_0_XU) {//左鍾乳石
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S5_Sky_SGround_1_YU && EnYR[e] <= S5_Sky_SGround_1_YU + PlusPx && EnXL[e] <= S5_Sky_SGround_1_XL && EnXR[e] >= S5_Sky_SGround_1_XU) {//中央鍾乳石
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S5_Sky_SGround_2_YU && EnYR[e] <= S5_Sky_SGround_2_YU + PlusPx && EnXL[e] <= S5_Sky_SGround_2_XL && EnXR[e] >= S5_Sky_SGround_2_XU) {//右鍾乳石
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S5_Sky_Ground_0_YU && EnYR[e] <= S5_Sky_Ground_0_YU + PlusPx && EnXL[e] <= S5_Sky_Ground_0_XL && EnXR[e] >= S5_Sky_Ground_0_XU) {//一番上
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S5_Sky_Ground_1_YU && EnYR[e] <= S5_Sky_Ground_1_YU + PlusPx && EnXL[e] <= S5_Sky_Ground_1_XL && EnXR[e] >= S5_Sky_Ground_1_XU) {//下の左
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S5_Sky_Ground_2_YU && EnYR[e] <= S5_Sky_Ground_2_YU + PlusPx && EnXL[e] <= S5_Sky_Ground_2_XL && EnXR[e] >= S5_Sky_Ground_2_XU) {//下の右
			enemy[e].ground = 1;
		}
		else {
			enemy[e].ground = 0;
		}
  }
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

			HitPFlg = 1;  // プレイヤーが敵に跳ね返る

			return e;
		}
	}

	return 3;
}

// 敵とプレイヤーの当たり判定
int Enemy::HitPlayer(int e)
{
	//プレイヤーの矩形の座標
	float PXL, PYL; //左上
	float PXR, PYR; //右下

	PXL = Px + 18;  //左上X
	PYL = Py + 14;  //左上Y
	PXR = Px + 40;  //右下X
	PYR = Py+ 64;   //右下Y

	
	EnXL[e] = enemy[e].x + 10.0f;  //左上X
	EnYL[e] = enemy[e].y + 12.0f;  //左上Y
	EnXR[e] = EnXL[e] + 45.0f;     //右下X
	EnYR[e] = EnYL[e] + 53.0f;     //右下Y

	if (enemy[e].life == 2) // 敵が風船状態のとき
	{
		if (EnXL[e] <= PXR && EnYL[e] <= PYR && EnXR[e] >= PXL && EnYR[e] >= PYL)
		{
			if (PYR < (EnYL[e] + 36))    // プレイヤーの位置(高さ)が敵キャラ(風船を除く人の部分)の半分より上にいる場合
			{
				enemy[e].flg = 17;
				// 仮
				enemy[e].life -= 1;

				HitPFlg = 1; // プレイヤーが敵に跳ね返る

				return e;

			}
			else if (EnYR[e] > (PYL + 37)) // 敵の位置(高さ)がプレイヤー(風船を除く人の部分)の半分より上にいる場合
			{
				enemy[e].flg = 17;

				HitPFlg = 2; // プレイヤーが敵に跳ね返る(風船あり)、プレイヤーの風船が一個減る

				return 3;
			}
			else // 敵の位置とプレイヤの位置(高さ)に上記以上の差がない場合
			{
				enemy[e].flg = 17;

				HitPFlg = 1; // プレイヤーが敵に跳ね返る

				return 3;
			}
		}
	}
	else if(enemy[e].life == 1)  // 敵がパラシュート状態のとき
	{
		if (EnXL[e] <= PXR && EnYL[e] <= PYR && EnXR[e] >= PXL && EnYR[e] >= PYL)
		{
			if (PYR < (EnYL[e] + 36))    // プレイヤーの位置(高さ)が敵キャラ(風船を除く人の部分)の半分より上にいる場合
			{
				enemy[e].flg = 17;
				// 仮
				enemy[e].life -= 1;

				HitPFlg = 1; // プレイヤーが敵に跳ね返る

				return e;

			}
			else // 上記以上の場合
			{
				enemy[e].flg = 17;

				HitPFlg = 1; // プレイヤーが敵に跳ね返る

				return 3;
			}
		}	
	}
	else
	{
		return 3;
	}
		
	return 3;
}