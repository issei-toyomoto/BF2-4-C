#include"DxLib.h"
#include"Thunderbolt.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"bubble.h"
#include"Common.h"

Thunder::Thunder(){
	if (LoadDivGraph("images/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, gThunderImg) == -1) {
	}//�摜�ǂݍ���
}

void Thunder::Update()
{
	ChangeAngle();

	MoveThunder();

}


void Thunder::Draw() const {
	DrawGraph(100, 100, gCloudImg, TRUE);
	
	DrawGraph(100, 200, gThunderImg[0], TRUE);

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


	// �ǁE�V��ł̔���
	if (ThunderX < 4 || ThunderX>640 - 4) {  //���̕�
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
	if (ThunderY < 8) { // ��̕�
		ThunderAngle = (1 - ThunderAngle);
		ChangeAngle();
	}
}


	
	
	



