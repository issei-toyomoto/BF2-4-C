#include"bubble.h"
#include"Dxlib.h"
#include"Common.h"
#include"Player.h"

bubble::bubble() {
	LoadDivGraph("images/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, BubbleImg);//画像読み込み
	px = 0;
	py = 0;
	BubleAnim = 0;
}



void bubble::Update()
{
	FPSCount++;
	// プレイヤーのX座標、Y座標
	px = Player::PlayerX;
	py = Player::PlayerY;

	bubbleY -= 0.25;


	if (FPSCount <= 29) {
		bubbleX -= 1.5;
	}
	if (FPSCount >= 30 && FPSCount <= 60) {
		bubbleX += 1.5;
	}

	if (FPSCount == 60) {
		FPSCount = 0;
	}
	if (px == bubbleX && py == bubbleY) {
		BubleAnim = 1;
	}


}

void bubble::Draw() const
{
	
	switch (BubleAnim)
	{
	case 0:
		DrawGraph((int)bubbleX, (int)bubbleY, BubbleImg[0], TRUE);
		DrawBox((int)bubbleX + 15, (int)bubbleY + 15, (int)bubbleX + 50, (int)bubbleY + 50, C_RED, FALSE);
		break;
	case 1:
		/*DrawGraph((int)bubbleX, (int)bubbleY, BubbleImg[3], TRUE);*/
		/*DrawGraph((int)bubbleX, (int)bubbleY, BubbleImg[0], TRUE);*/
		DrawBox((int)bubbleX + 15, (int)bubbleY + 15, (int)bubbleX + 50, (int)bubbleY + 50, C_WHITE, FALSE);
		break;
	default:
		break;
	}
	
	
	//DrawBox((int)bubbleXY, (int)bubbleY, (int)bubbleX+10, (int)bubbleY +10, GetColor(255, 0, 0), TRUE);
	//DrawFormatString(10, 100, C_WHITE, "%d", bubbleX);
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

	if (BubleX1 <= Player::PlayerX + 18 && BubleY1 <=  Player::PlayerY +14  && BubleX2 >= Player::PlayerX + 40 && BubleY2 >=  Player::PlayerY + 64 ) {
		BubleAnim = 1;
	}
}


