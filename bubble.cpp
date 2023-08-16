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
	/*bubbleX = 320;
	bubbleY = 480;
	BubbleX_Old = 0;
	BubbleY_Old = 0;*/
	FPSCount = 0;
	px = 0;
	py = 0;
	Bubble_X = 0;
	Bubble_X_Old = 0;
	/*BubbleFlg = 0;
	BubleScore = 0;
	Bubbledetection = 0;*/
	/*BubbleAnimCount = 0;*/
	BubbleScoreImg = LoadGraph("images-20230711T024428Z-001/images/Score/GetScore_500.png");
	for(int i = 0; i < 4; i++)
	{
		BubbleAnimFase[i] = 0;
	}
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
		/*bubble::BubbleSpawn(BubbleNumber);
		bubble::BubleCollision(BubbleNumber);*/
		BubbleNumber++;
	}
	if (py > 430 && Bubble[BubbleNumber].Event == 0) {
		Bubble[BubbleNumber].X = px;
		Bubble[BubbleNumber].Y = py;
		Bubble[BubbleNumber].Event = 1;
		/*bubble::BubbleSpawn(BubbleNumber);
		bubble::BubleCollision(BubbleNumber);*/
		BubbleNumber++;
	}

	for (int i = 0; i < 6; i++) {
		if (Bubble[i].Event == 1) {
			Bubble[i].Y -= 1.0f;
			Bubble[i].X += amplitude * (float)sin(frequency * Bubble[i].Count);
			Bubble[i].Count += 1;
			// シャボン玉とプレイヤーの当たり判定
			if ((((int)Bubble[i].X + 15 > px + 18 && Bubble[i].X + 15 < px + 40) || (Bubble[i].X + 15 < px + 18 && Bubble[i].X + 50 > px + 18)) && ((Bubble[i].Y + 15 > py + 14 && Bubble[i].Y + 15< py + 64) || (py + 14 > Bubble[i].Y + 15 && py + 14 < Bubble[i].Y + 50)) && Bubble[i].detection == 0) {
				BubleScore += 500;
				Bubble[i].X_Old = Bubble[i].X + 15;
				Bubble[i].Y_Old = Bubble[i].Y + 15;
				Bubble[i].Flg = 1;
				Bubble[i].detection = 1;
			}
			if (Bubble[i].Flg == 1)
			{
				Bubble[i].AnimCount++;
			}
			if (Bubble[i].AnimCount == 1) {
				PlaySoundMem(soundstorage.BubbleSE, DX_PLAYTYPE_BACK, TRUE);
			}
#ifdef DEBUG
			if (Bubble[i].AnimCount == 30 || Bubble[i].Y == 0)
			{
				Bubble[i].X = BEnemyX;
				Bubble[i].Y = 480;
				Bubble[i].AnimCount = 0;
				Bubble[i].Flg = 0;
				Bubble[i].detection = 0;
				/*Bubble[i].Event = 0;*/
				/*bubble::Draw();*/
			}
			if (flg == 1) {
				BubleScore = 0;
			}
		}
#endif // DEBUG
			
			/*Bubble[BubbleNumber].X = px;*/

			/*BubbleNumber++;*/

		/*bubble::BubleCollision();*/
			;

			//Bubble[BubbleNumber].X -= FPSCount % 10 * 0.25f;// 1.5f
		/*}*/
		//if (FPSCount >= 30 && FPSCount <= 60) {
		//	Bubble[BubbleNumber].X += FPSCount % 10 * 0.25f; // 1.5f
		//	Bubble[BubbleNumber].X -= FPSCount % 10 * 0.05f;// 1.5f
		//}


	}
	/*if (Bubble[0].AnimCount == 100)
	{
		Bubble[0].X = 320;
		Bubble[0].Y = 480;
		Bubble[0].AnimCount = 0;
		Bubble[0].Flg = 0;
		Bubble[0].detection = 0;
		bubble::Draw();
	}*/
}

void bubble::Draw() const
{
	DrawFormatString(20, 300, C_WHITE, "%d", Bubble[0].Y);
	DrawFormatString(20, 350, C_WHITE, "%d", Bubble[0].Event);
	for (int i = 0; i < 10; i++) {
		if (Bubble[i].Event == 1) {
			DrawFormatString(80, 300, C_RED, "%d", Bubble[i].AnimCount);
			if (Bubble[i].Flg == 0 && Bubble[i].detection == 0)
			{
				DrawGraph((int)Bubble[i].X, (int)Bubble[i].Y, Bubble[i].Img[0], TRUE);
				DrawBox((int)Bubble[i].X + 15, (int)Bubble[i].Y + 15, (int)Bubble[i].X + 50, (int)Bubble[i].Y + 50, C_RED, FALSE);
			}
			if (Bubble[i].Flg == 1)
			{
				if (Bubble[i].AnimCount < 100)
				{
					DrawGraph(Bubble[i].X_Old, Bubble[i].Y_Old - 35, BubbleScoreImg, TRUE);
				}
				if (Bubble[i].AnimCount < 2 && Bubble[i].AnimCount > 0)
				{
					DrawGraph((int)Bubble[i].X, (int)Bubble[BubbleNumber].Y, Bubble[i].Img[1], TRUE);
				}
				else if (Bubble[i].AnimCount < 4 && Bubble[i].AnimCount > 2)
				{
					DrawGraph((int)Bubble[i].X, (int)Bubble[i].Y, Bubble[i].Img[2], TRUE);
				}
				else if (Bubble[i].AnimCount < 6 && Bubble[i].AnimCount > 4)
				{
					DrawGraph((int)Bubble[i].X, (int)Bubble[i].Y, Bubble[i].Img[3], TRUE);
				}
			}
		}
	}
#ifdef DEBUG
	DrawGraph((int)BEnemyX, (int)BEnemyY, BubbleVEnemy[9],TRUE);
#endif // DEBUG

}
void bubble::BubbleSpawn(int n)
{
	if (Bubble[n].Flg != 1) {
		float amplitude = 25.0f;
		float frequency = 0.05f;

		/*Bubble_X_Old = Bubble[n].X;*/
		Bubble[n].Y -= 1.0f;
		/*Bubble_X = Bubble_X_Old;*/
		Bubble[n].X += amplitude * (float)sin(frequency * Bubble[n].Count);
		/*Bubble[n].X = Bubble_X;*/
		Bubble[n].Count += 1;
	}
}
// シャボン玉の当たり判定
void bubble::BubleCollision(int n)
{
	////シャボン玉の矩形の座標
	//int BubleX1, BubleY1, BubleX2, BubleY2; // 左上座標(x1,x2) 右上座標(x2,y2)
	//BubleX1 = (int)Bubble[n].X + 15;
	//BubleY1 = (int)Bubble[n].Y + 15;
	//BubleX2 = (int)Bubble[n].X + 50;
	//BubleY2 = (int)Bubble[n].Y + 50;

	// シャボン玉とプレイヤーの当たり判定
	//if (((BubleX1 > px + 18 && BubleX1 < px + 40) || (BubleX1 < px + 18 && BubleX2 > px + 18)) && ((BubleY1 > py + 14 && BubleY1 < py + 64) || (py + 14 > BubleY1 && py + 14 < BubleY2)) && Bubble[0].detection == 0) {
	//	BubleScore += 500;
	//	Bubble[n].X_Old = BubleX1;
	//	Bubble[n].Y_Old = BubleY1;
	//	Bubble[n].Flg = 1;
	//	Bubble[n].detection = 1;
	//}
}



