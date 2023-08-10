#include "Cloud.h"
#include "Common.h"

Cloud::Cloud() 
{
	Num = 0;

	LoadDivGraph("images/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, Img);
	for (int i = 0; i < 2; i++) {
		NowImg[i] = Img[0];
	}

	//アニメーションまでの時間決め
	WaitTimeFlg[0] = GetRand(3);
	WaitTimeFlg[1] = GetRand(3);
}

void Cloud::Update() 
{
	if (Num > 2) {
		Num = 0;
	}

	AnimCnt[Num]++;



	if (AnimCnt[Num] > 8) {
		AnimCnt[Num] = 0;
	}

	Num++;
}

void Cloud::Draw(int Stage) const 
{
	StageDrawCloud(Stage);
}

void Cloud::StageDrawCloud(int Stage) const 
{
	if (Stage == 1) {
		DrawGraph(Stage_1_X, Stage_1_Y, NowImg[0], TRUE);
	}
	else if (Stage == 2) {
		DrawGraph(Stage_2_X_0, Stage_2_Y_0, NowImg[0], TRUE);
		DrawGraph(Stage_2_X_1, Stage_2_Y_1, NowImg[1], TRUE);
	}
}

void Cloud::AnimCloud() 
{
	
}