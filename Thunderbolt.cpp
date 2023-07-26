#include"DxLib.h"
#include"Thunderbolt.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"bubble.h"
#include"Common.h"
#include<stdio.h>
#include"Player.h"
Thunder::Thunder(){
	if (LoadDivGraph("images/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, gThunderImg) == -1) {
	}//âÊëúì«Ç›çûÇ›

	ThunderX = 100;
	ThunderY = 100;// óãÇÃç¿ïW

	ThunderMoveX = 3;
	ThunderMoveY = 3;
	FPSCount = 0;
	
}



void Thunder::MoveThunderX() 
{
	if (ThunderX <= 0) {
		ThunderMoveX *= -1;
	}
	else if (ThunderX >= _SCREEN_WIDHT_) {
		ThunderMoveX *= -1;
	}

	
}

void Thunder::MoveThunderY() 
{
	if (ThunderY <= 0) {
		ThunderMoveY *= -1;
	}
	else if (ThunderY >= _SCREEN_HEIGHT_) {
		ThunderMoveY *= -1;
	}
}

void Thunder::Update()
{
	
	FPSCount++;

	

	MoveThunderX();
	ThunderX += ThunderMoveX;
	MoveThunderY();
	ThunderY += ThunderMoveY;

}


void Thunder::Draw() const {
	/*if (FlgY < 5) {
		DrawGraph(100, 100, gCloudImg, TRUE);
	}*/
	
	// ÇTâÒÇÃÇ§ÇøÇQâÒï\é¶Ç∑ÇÈÅB
	
	/*count = (count + 1) % 5;
	if (count < 2) {
		DrawGraph(100, 100, gCloudImg, TRUE);
	}*/
	

	switch (FPSCount%2)
	{
	default:
		DrawGraph(ThunderX, ThunderY, gThunderImg[2], TRUE);
		break;
	case 0:
		DrawGraph(ThunderX, ThunderY, gThunderImg[0], TRUE);
		break;
	case 1:
		DrawGraph(ThunderX, ThunderY, gThunderImg[1], TRUE);
		break;

	}
	

}








	
	
	



