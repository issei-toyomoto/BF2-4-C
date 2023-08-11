#include"bubble.h"
#include"Dxlib.h"
#include"Common.h"
#include"Player.h"
#include"Soundstorage.h"
#define DEBUG

int bubble::BubleScore;

bubble::bubble() 
{

	for (int i = 0; i < 6; i++) {
		LoadDivGraph("images/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, Bubble[i].Img);
		Bubble[i].X = 320;
		Bubble[i].Y = 480;
		Bubble[i].detection = 0;
		Bubble[i].Flg = 0;
		Bubble[i].X_Old = 0;
		Bubble[i].Y_Old = 0;
		Bubble[i].AnimCount = 0;
		Bubble[i].Event = 0;
	}
	BubbleNumber = 0;
	/*bubbleX = 320;
	bubbleY = 480;
	BubbleX_Old = 0;
	BubbleY_Old = 0;*/
	FPSCount = 0;
	px = 0;
	py = 0;
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
	FPSCount++;
	// プレイヤーのX座標、Y座標
	px = Player::PlayerX;
	py = Player::PlayerY;

	BEnemyY += 1;
	if (BEnemyY > 470 && Bubble[BubbleNumber].Event == 0) {
		Bubble[BubbleNumber].Event = 1;
	}
	/*else
	{
		BubbleNumber += 1;
	}*/

	if (Bubble[BubbleNumber].Event == 1) {
		bubble::BubleCollision();

		Bubble[BubbleNumber].Y -= FPSCount % 10 * 0.25f;
		if (FPSCount <= 29) {
			Bubble[BubbleNumber].X -= FPSCount % 10 * 0.25f;// 1.5f
			Bubble[BubbleNumber].X += FPSCount % 10 * 0.05f;// 1.5f
		}
		if (FPSCount >= 30 && FPSCount <= 60) {
			Bubble[BubbleNumber].X += FPSCount % 10 * 0.25f; // 1.5f
			Bubble[BubbleNumber].X -= FPSCount % 10 * 0.05f;// 1.5f
		}

		if (FPSCount == 60) {
			FPSCount = 0;
		}
		if (Bubble[BubbleNumber].Flg == 1)
		{
			Bubble[BubbleNumber].AnimCount++;
		}
		if (Bubble[BubbleNumber].AnimCount == 1) {
			PlaySoundMem(soundstorage.BubbleSE, DX_PLAYTYPE_BACK, TRUE);
		}
#ifdef DEBUG
		if (Bubble[BubbleNumber].AnimCount == 30)
		{
			Bubble[BubbleNumber].X = BEnemyX;
			Bubble[BubbleNumber].Y = 480;
			Bubble[BubbleNumber].AnimCount = 0;
			Bubble[BubbleNumber].Flg = 0;
			Bubble[BubbleNumber].detection = 0;
			Bubble[BubbleNumber].Event = 0;
			bubble::Draw();
		}
		if (flg == 1) {
			BubleScore = 0;
		}
	}
#endif // DEBUG

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
	/*DrawFormatStringF(0, 200, C_RED, "%d", px_old);
	DrawFormatStringF(20, 200, C_RED, "%d", py_old);*/
	if (Bubble[BubbleNumber].Event == 1) {
		DrawFormatString(80, 300, C_RED, "%d", Bubble[BubbleNumber].AnimCount);
		if (Bubble[BubbleNumber].Flg == 0 && Bubble[BubbleNumber].detection == 0)
		{
			DrawGraph((int)Bubble[BubbleNumber].X, (int)Bubble[BubbleNumber].Y, Bubble[BubbleNumber].Img[0], TRUE);
			DrawBox((int)Bubble[BubbleNumber].X + 15, (int)Bubble[BubbleNumber].Y + 15, (int)Bubble[BubbleNumber].X + 50, (int)Bubble[BubbleNumber].Y + 50, C_RED, FALSE);
		}
		if (Bubble[0].Flg == 1)
		{
			if (Bubble[BubbleNumber].AnimCount < 100)
			{
				DrawGraph(Bubble[BubbleNumber].X_Old, Bubble[BubbleNumber].Y_Old - 35, BubbleScoreImg, TRUE);
			}
			if (Bubble[0].AnimCount < 2 && Bubble[0].AnimCount > 0)
			{
				DrawGraph((int)Bubble[BubbleNumber].X, (int)Bubble[BubbleNumber].Y, Bubble[BubbleNumber].Img[1], TRUE);
			}
			else if (Bubble[0].AnimCount < 4 && Bubble[0].AnimCount > 2)
			{
				DrawGraph((int)Bubble[BubbleNumber].X, (int)Bubble[BubbleNumber].Y, Bubble[BubbleNumber].Img[2], TRUE);
			}
			else if (Bubble[BubbleNumber].AnimCount < 6 && Bubble[BubbleNumber].AnimCount > 4)
			{
				DrawGraph((int)Bubble[BubbleNumber].X, (int)Bubble[BubbleNumber].Y, Bubble[BubbleNumber].Img[3], TRUE);
			}
		}
	}
#ifdef DEBUG
	DrawGraph(BEnemyX, BEnemyY, BubbleVEnemy[9],TRUE);
#endif // DEBUG

}
// シャボン玉の当たり判定
void bubble::BubleCollision()

{
	//シャボン玉の矩形の座標
	int BubleX1, BubleY1, BubleX2, BubleY2; // 左上座標(x1,x2) 右上座標(x2,y2)
	BubleX1 = (int)Bubble[BubbleNumber].X + 15;
	BubleY1 = (int)Bubble[BubbleNumber].Y + 15;
	BubleX2 = (int)Bubble[BubbleNumber].X + 50;
	BubleY2 = (int)Bubble[BubbleNumber].Y + 50;

	// シャボン玉とプレイヤーの当たり判定
	if (((BubleX1 > px + 18 && BubleX1 < px + 40) || (BubleX1 < px + 18 && BubleX2 > px + 18)) && ((BubleY1 > py + 14 && BubleY1 < py + 64) || (py + 14 > BubleY1 && py + 14 < BubleY2)) && Bubble[0].detection == 0) {
		BubleScore += 4500;
		Bubble[BubbleNumber].X_Old = BubleX1;
		Bubble[BubbleNumber].Y_Old = BubleY1;
		Bubble[BubbleNumber].Flg = 1;
		Bubble[BubbleNumber].detection = 1;
	}
}



