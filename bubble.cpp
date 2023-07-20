#include"bubble.h"
#include"Dxlib.h"
#include"Common.h"
#include"Player.h"

bubble::bubble() {
	LoadDivGraph("images/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, BubbleImg);//âÊëúì«Ç›çûÇ›
	px = 0;
	py = 0;
}



void bubble::Update()
{
	FPSCount++;

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

}

void bubble::Draw() 
{
	DrawGraph((int)bubbleX, (int)bubbleY, BubbleImg[0], TRUE);

	if (Player::PlayerX, Player::PlayerY == bubbleX, bubbleY) {
		DrawGraph((int)bubbleX, (int)bubbleY, BubbleImg[3], TRUE);
	}
	
	//DrawBox((int)bubbleX, (int)bubbleY, (int)bubbleX+10, (int)bubbleY +10, GetColor(255, 0, 0), TRUE);
	//DrawFormatString(10, 100, C_WHITE, "%d", bubbleX);
}


