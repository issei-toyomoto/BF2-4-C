#define _USE_MATH_DEFINES
#include"bubble.h"
#include"Dxlib.h"
#include"Common.h"
#include"Player.h"
#include"Soundstorage.h"
#include"GameMain.h"
#include<math.h>
#define DEBUG

int bubble::BubleScore;

bubble::bubble() 
{
	// シャボン玉の構造体初期化
	for (int i = 0; i < 6; i++) {
		LoadDivGraph("images/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, Bubble[i].Img);
		Bubble[i].X = 250;
		Bubble[i].Y = 480;
		Bubble[i].detection = 0;
		Bubble[i].Flg = 0;
		Bubble[i].X_Old = 0;
		Bubble[i].Y_Old = 0;
		Bubble[i].AnimCount = 0;
		Bubble[i].Event = 0;
		Bubble[i].Count = 0;
	}
	BubbleNumber = 0;
	FPSCount = 0;
	px = 0;
	py = 0;
	BubbleScoreImg = LoadGraph("images-20230711T024428Z-001/images/Score/GetScore_500.png");
#ifdef DEBUG
	LoadDivGraph("image/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, BubbleVEnemy);
	BEnemyX = 250.0f;
	BEnemyY = 300.0f;
#endif // DEBUG

}

void bubble::Update(int flg)
{

	float amplitude = 2.5f;
	float frequency = 0.05f;

	FPSCount++;

	if (FPSCount == 60) {
		FPSCount = 0;
	}
	// プレイヤーのX座標、Y座標
	px = Player::PlayerX;
	py = Player::PlayerY;
	if (BEnemyY <= 430) {
		BEnemyY += 1.0f;
	}
	if (BEnemyY > 430 && Bubble[BubbleNumber].Event == 0) {
		Bubble[BubbleNumber].X = BEnemyX;
		Bubble[BubbleNumber].Y = 480;
		Bubble[BubbleNumber].Event = 1;
		BubbleNumber++;
	}
	if (py > 430 && Bubble[BubbleNumber].Event == 0) {
		Bubble[BubbleNumber].X = px;
		Bubble[BubbleNumber].Y = py;
		Bubble[BubbleNumber].Event = 1;
		BubbleNumber++;
	}
	// 敵が画面外へ落下した時に行う処理
	for (int i = 0; i < 6; i++) {
		if (Bubble[i].Event == 1) {
			Bubble[i].Y -= 1.0f;
			Bubble[i].X += amplitude * (float)sin(frequency * Bubble[i].Count);
			Bubble[i].Count += 1;
			// シャボン玉とプレイヤーの当たり判定
			if ((((int)Bubble[i].X + 15 > px + 18 && Bubble[i].X + 15 < px + 40) || (Bubble[i].X + 15 < px + 18 && Bubble[i].X + 50 > px + 18)) && ((Bubble[i].Y + 15 > py + 14 && Bubble[i].Y + 15 < py + 64) || (py + 14 > Bubble[i].Y + 15 && py + 14 < Bubble[i].Y + 50)) && Bubble[i].detection == 0) {
				BubleScore += 500;
				Bubble[i].X_Old = px;
				Bubble[i].Y_Old = py + 15;
				Bubble[i].Flg = 1;
				Bubble[i].detection = 1;
			}
			if (Bubble[i].Flg == 1)
			{
				Bubble[i].AnimCount++;
			}
			if (Bubble[i].AnimCount == 1) {
				GameMain::SoundFlg = 1;
				StopSoundMem(ss.gStartSE);
				PlaySoundMem(ss.BubbleSE, DX_PLAYTYPE_BACK, TRUE);
			}
			if (Bubble[i].AnimCount == 30 || Bubble[i].Y == 0)
			{
				Bubble[i].X = BEnemyX;
				Bubble[i].Y = 480;
				Bubble[i].AnimCount = 0;
				Bubble[i].Flg = 0;
				Bubble[i].detection = 0;
			}
			if (flg == 1) {
				BubleScore = 0;
			}
		}
	}
}
void bubble::Draw() const
{
	for (int i = 0; i < 10; i++) {
		if (Bubble[i].Event == 1) {
			if (Bubble[i].Flg == 0 && Bubble[i].detection == 0) {
				DrawGraph((int)Bubble[i].X, (int)Bubble[i].Y, Bubble[i].Img[0], TRUE);
				/*DrawBox((int)Bubble[i].X + 15, (int)Bubble[i].Y + 15, (int)Bubble[i].X + 50, (int)Bubble[i].Y + 50, C_RED, FALSE);*/
			}
			if (Bubble[i].Flg == 1) {
				if (Bubble[i].AnimCount < 100) {
					DrawGraphF(Bubble[i].X_Old, Bubble[i].Y_Old - 35.0f, BubbleScoreImg, TRUE);
				}
				if (Bubble[i].AnimCount < 2 && Bubble[i].AnimCount > 0) {
					DrawGraph((int)Bubble[i].X, (int)Bubble[i].Y, Bubble[i].Img[1], TRUE);
				}
				else if (Bubble[i].AnimCount < 4 && Bubble[i].AnimCount > 2) {
					DrawGraph((int)Bubble[i].X, (int)Bubble[i].Y, Bubble[i].Img[2], TRUE);
				}
				else if (Bubble[i].AnimCount < 6 && Bubble[i].AnimCount > 4) {
					DrawGraph((int)Bubble[i].X, (int)Bubble[i].Y, Bubble[i].Img[3], TRUE);
				}
			}
		}
	}
#ifdef _DEBUG
	DrawGraph((int)BEnemyX, (int)BEnemyY, BubbleVEnemy[9], TRUE);
#endif // DEBUG
}


