#include"DxLib.h"
#include"Thunderbolt.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"bubble.h"
#include"Common.h"

Thunder::Thunder(){
	if (LoadDivGraph("images/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, gThunderImg) == -1) {
	}//âÊëúì«Ç›çûÇ›

	ThunderX = 100;
	ThunderY = 200;// óãÇÃç¿ïW

	ThunderMoveX = 3;
	ThunderMoveY = 3;
}

//void Thunder::ChangeAngle()
//{
//	float rad = ThunderAngle * (float)M_PI * 2;
//	ThunderMoveX = (int)(Speed * cosf(rad));
//	ThunderMoveY = (int)(Speed * sinf(rad));
//}

void Thunder::MoveThunderX() 
{
	if (ThunderX <= 0) {
		ThunderMoveX *= -1;
	}
	else if (ThunderX >= _SCREEN_WIDHT_) {
		ThunderMoveX *= -1;
	}

	//if (ThunderFlg != 2) {

	//	ThunderX += ThunderMoveX;
	//	ThunderY += ThunderMoveY;
	//}
	//else {
	//	ThunderX += ThunderMoveX + 30;
	//	ThunderY += ThunderMoveY - 6;

	//}


	//// ï«ÅEìVà‰Ç≈ÇÃîΩéÀ
	//if (ThunderX < 4 || ThunderX>640 - 4) {  //â°ÇÃï«
	//	if (ThunderX < 4) {
	//		ThunderX = 4;
	//	}
	//	else {
	//		ThunderX = 640 - 4;
	//	}
	//	ThunderAngle = (1 - ThunderAngle) + 0.5f;
	//	if (ThunderAngle > 1)ThunderAngle -= 1.0f;
	//	ChangeAngle();
	//}
	//if (ThunderY < 8) { // è„ÇÃï«
	//	ThunderAngle = (1 - ThunderAngle);
	//	ChangeAngle();
	//}
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
	//ChangeAngle();

	MoveThunderX();
	ThunderX += ThunderMoveX;
	MoveThunderY();
	ThunderY += ThunderMoveY;

}


void Thunder::Draw() const {
	DrawGraph(100, 100, gCloudImg, TRUE);
	
	DrawGraph(ThunderX, ThunderY, gThunderImg[0], TRUE);
}





	
	
	



