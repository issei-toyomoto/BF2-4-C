#include"Fish.h"
#include"DxLib.h"
#include<math.h>

//�R���X�g���N�^
Fish::Fish() {
	/*FishImage = LoadImage();*/
	WaitTime=0;
	f_PosX=0;
	f_PosY=0;
	Count = 0;
	Second = 0;
	FishRand = 0;
	FishFlg = FALSE;
	f_Count = 60;
}

//������(Draw)
void Fish::CreateFish() {
	if (f_Count < 60) {
		DrawBox;	//���摜
		/*DrawGraph()*/
	}
}

//�o���G���A(Update)
void Fish::FishArea() {

	////�o���G���A����
	//if (playerY > 610 || enemyY > 610) {
	//	while (playerY < 610 && enemyY<610) {
	//		Count++;
	//		Second = Count / 60;
	//		if (Second >= 3 && FishFlg == FALSE) {
	//			FishRand = GetRand(99);
	//			Count = 0;
	//			Second = 0;
	//			if (FishRand <= 29) {
	//				FishFlg = TRUE;
	//			}
	//		}
	//		if (FishFlg == TRUE) {
	//			MoveFish();
	//		}
	//	}
	//	if (FishFlg == TRUE&&f_Count<60) {
	//		MoveFish();
	//	}
	//}
}

//���ړ�
void Fish::MoveFish() {
	/*
	if (enemyY > 610) {
		f_PosX = enemyX;
		f_PosY = enemyY - f_Count;
		f_Count = f_Count - 1;
	}
	else if (playerY > 610) {
		f_PosX = playerX;
		f_PosY = playerY - f_Count;
		f_Count = f_Count - 1;
	}
	else if (playerY < 610 && enemyY < 610) {
		f_PosY = f_PosY + f_Count;
		f_Count = f_Count + 1;
	}*/
}