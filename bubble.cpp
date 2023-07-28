#include"bubble.h"
#include"Dxlib.h"
#include"Common.h"
#include"Player.h"

int bubble::BubleScore;

bubble::bubble() {
	LoadDivGraph("images/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, BubbleImg);
	bubbleX = 320;
	bubbleY = 480;
	BubbleX_Old = 0;
	BubbleY_Old = 0;
	FPSCount = 0;
	px = 0;
	py = 0;
	BubbleFlg = 0;
	BubleScore = 0;
	Bubbledetection = 0;
	BubbleAnimCount = 0;
	BubbleScoreImg = LoadGraph("images-20230711T024428Z-001/images/Score/GetScore_500.png");
	for(int i = 0; i < 4; i++)
	{
		BubbleAnimFase[i] = 0;
	}
}


void bubble::Update()
{
	FPSCount++;
	// プレイヤーのX座標、Y座標
	px = Player::PlayerX;
	py = Player::PlayerY;

	bubble::BubleCollision();

	bubbleY -= 0.75;
	if (FPSCount <= 29) {
		bubbleX -= 1.5;
	}
	if (FPSCount >= 30 && FPSCount <= 60) {
		bubbleX += 1.5;
	}

	if (FPSCount == 60) {
		FPSCount = 0;
	}
	if (BubbleFlg == 1)
	{
		BubbleAnimCount++;
	}
	if (BubbleAnimCount == 100)
	{
		BubbleAnimCount = 0;
		BubbleFlg = 0;
		bubble::Draw();
	}
}

void bubble::Draw() const
{
	/*DrawFormatStringF(0, 200, C_RED, "%d", px_old);
	DrawFormatStringF(20, 200, C_RED, "%d", py_old);*/
	/*DrawFormatString(80, 300, C_RED, "%d", BubbleAnimCount);*/
	if (BubbleFlg == 0 && Bubbledetection == 0)
	{
		DrawGraph((int)bubbleX, (int)bubbleY, BubbleImg[0], TRUE);
		DrawBox((int)bubbleX + 15, (int)bubbleY + 15, (int)bubbleX + 50, (int)bubbleY + 50, C_RED, FALSE);
	}
	if (BubbleFlg == 1)
	{
		if (BubbleAnimCount < 100)
		{
			DrawGraph(BubbleX_Old , BubbleY_Old -35, BubbleScoreImg, TRUE);
		}
		if (BubbleAnimCount < 2 && BubbleAnimCount > 1)
		{
			DrawGraph((int)bubbleX, (int)bubbleY, BubbleImg[1], TRUE);
		}
		else if(BubbleAnimCount < 4 && BubbleAnimCount > 2)
		{
			DrawGraph((int)bubbleX, (int)bubbleY, BubbleImg[2], TRUE);
		}
		else if(BubbleAnimCount < 6 && BubbleAnimCount > 4)
		{
			DrawGraph((int)bubbleX, (int)bubbleY, BubbleImg[3], TRUE);
		}
	}
}
// シャボン玉の当たり判定
void bubble::BubleCollision()

{
	//シャボン玉の矩形の座標
	int BubleX1, BubleY1, BubleX2, BubleY2; // 左上座標(x1,x2) 右上座標(x2,y2)
	BubleX1 = (int)bubbleX + 15;
	BubleY1 = (int)bubbleY + 15;
	BubleX2 = (int)bubbleX + 50;
	BubleY2 = (int)bubbleY + 50;

	// シャボン玉とプレイヤーの当たり判定
	if (((BubleX1 > px + 18 && BubleX1 < px + 40) || (BubleX1 < px + 18 && BubleX2 > px + 18)) && ((BubleY1 > py + 14 && BubleY1 < py + 64) || (py + 14 > BubleY1 && py + 14 < BubleY2)) && Bubbledetection == 0) {
		BubleScore += 500;
		BubbleX_Old = BubleX1;
		BubbleY_Old = BubleY1;
		BubbleFlg = 1;
		Bubbledetection = 1;
	}
}

void bubble::BubbleScore()
{
	
}


