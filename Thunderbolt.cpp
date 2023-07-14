#include"DxLib.h"
#include"Thunderbolt.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"bubble.h"

void Thunder::Draw() const {
	DrawGraph(100, 100, gCloudImg, TRUE);
	DrawGraph(150, 150, gThunderImg, TRUE);
	DrawBox((int)ThunderX, (int)ThunderY, (int)ThunderX + 10, (int)ThunderY + 10, GetColor(255, 0, 0), TRUE);

}

void Thunder::Update()
{

}

void Thunder::ChangeAngle()
{
	float rad = ThunderAngle * (float)M_PI * 2;
	ThunderMoveX = (int)(Speed * cosf(rad));
	ThunderMoveY = (int)(Speed * sinf(rad));
}

void Thunder::MoveThunder() {
	ThunderX += 1;
	ThunderY += 1; 

	if(ThunderFlg != 2) {

		ThunderX += ThunderMoveX;
		ThunderY += ThunderMoveY;
	}
	else {
		ThunderX += ThunderMoveX + 30;
		ThunderY += ThunderMoveY - 6;

	}


	// ï«ÅEìVà‰Ç≈ÇÃîΩéÀ
	if (ThunderX < 4 || ThunderX>640 - 4) {  //â°ÇÃï«
		if (ThunderX < 4) {
			ThunderX = 4;
		}
		else {
			ThunderX = 640 - 4;
		}
		ThunderAngle = (1 - ThunderAngle) + 0.5f;
		if (ThunderAngle > 1)ThunderAngle -= 1.0f;
		ChangeAngle();
	}
	if (ThunderY < 8) { // è„ÇÃï«
		ThunderAngle = (1 - ThunderAngle);
		ChangeAngle();
	}
}


	
	
	



