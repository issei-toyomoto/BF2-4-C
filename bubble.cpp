#include"bubble.h"
#include"Dxlib.h"
#include"Common.h"
#include"Player.h"

bubble::bubble() {
	LoadDivGraph("images/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, BubbleImg);//画像読み込み
	bubbleX = 320;
	bubbleY = 480;
	FPSCount = 0;
	px = 0;
	py = 0;
	BubleFlg = 0;
	BubbleFlg = 0;
	BubleScore = 0;
}



void bubble::Update()
{
	FPSCount++;
	// プレイヤーのX座標、Y座標
	px = Player::PlayerX;
	py = Player::PlayerY;

	bubble::BubleCollision();

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

}

void bubble::Draw() const
{
	
	switch (BubleFlg)
	{
	case 0:
		DrawGraph((int)bubbleX, (int)bubbleY, BubbleImg[0], TRUE);
		DrawBox((int)bubbleX + 15, (int)bubbleY + 15, (int)bubbleX + 50, (int)bubbleY + 50, C_RED, FALSE);
		break;
	case 1:
		DrawGraph((int)bubbleX, (int)bubbleY, BubbleImg[3], TRUE);
		DrawFormatString((int)bubbleX, (int)bubbleY -30, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");
		/*DrawGraph((int)bubbleX, (int)bubbleY, BubbleImg[0], TRUE);
		DrawBox((int)bubbleX + 15, (int)bubbleY + 15, (int)bubbleX + 50, (int)bubbleY + 50, C_WHITE, FALSE);*/
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

	// シャボン玉とプレイヤーの当たり判定
	if (((BubleX1 > px + 18 && BubleX1 <  px + 40)||(BubleX1 < px + 18 && BubleX2 > px + 18))&&(( BubleY1 > py + 14 && BubleY1 < py + 64)||(py + 14 > BubleY1 && py + 14 < BubleY2))) {
		BubleFlg = 1;
		BubleScore += 500;
	}
}


