#include "Cloud.h"
#include "Thunder.h"
#include "Common.h"

#define DEBUG

bool Cloud::FinAnimFlg[2];

Cloud::Cloud() 
{
	Num = 0;

	LoadDivGraph("images/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, Img);
	for (int i = 0; i < 2; i++) {
		NowImg[i] = Img[0];
		WaitTimeCnt[i] = 0;
		AnimCnt[i] = 0;

		FinAnimFlg[i] = false;
	}

	//アニメーションまでの時間決め
	WaitTimeFlg[0] = GetRand(3);
	WaitTimeFlg[1] = GetRand(3);

	for (int i = 0; i < 2; i++) {
		if (WaitTimeFlg[i] == 0) {
			WaitTime[i] = 20 * Frame;
		}
		else if (WaitTimeFlg[i] == 1) {
			WaitTime[i] = 25 * Frame;
		}
		else if (WaitTimeFlg[i] == 2) {
			WaitTime[i] = 30 * Frame;
		}
		
		else if (WaitTimeFlg[i] == 3) {
			WaitTime[i] = 35 * Frame;
		}
	}
}

void Cloud::Update() 
{
	for (Num = 0; Num < 2; Num++) {
		ThunderState[Num] = Thunder::State[Num];

		if (ThunderState[Num] == NO_USE) {
			WaitTimeCnt[Num]++;
		}
		else if (ThunderState[Num] == USE) {
			WaitTimeCnt[Num] = 0;
			FinAnimFlg[Num] = false;
		}

		if (CloudState[Num] == Anim && ThunderState[Num] == NO_USE /*&& Thunder::InitFlg[Num] == true*/) {//雲のステートがAnimならAnimCntをCntする
			AnimCnt[Num]++;
			//FinAnimFlg[Num] = false;
		}

		if (AnimCnt[Num] > 8) {//AnimCntが８より大きいならAnimCntを０に
			AnimCnt[Num] = 0;
		}

		if (WaitTime[Num] == WaitTimeCnt[Num]) {//設定した時間とCntが同じ時間なら雲のステートをAnimに
			CloudState[Num] = Anim;
		}

		if (WaitTimeCnt[Num] == WaitTime[Num] + StopTime) {//アニメーションを止める
			WaitTimeCnt[Num] = 0;
			CloudState[Num] = No_Anim;
			WaitTime[Num] = 5 * Frame;//次のアニメーションまでの時間設定
			FinAnimFlg[Num] = true;
		}

		//画像処理
		if (CloudState[Num] == No_Anim) {
			NowImg[Num] = Img[0];
		}
		else if (CloudState[Num] == Anim) {
			AnimCloud(Num);
		}
	}
#ifdef DEBUG
	
#endif // DEBUG

}

void Cloud::Draw(int Stage) const 
{
	StageDrawCloud(Stage);

#ifdef DEBUG
	DrawFormatString(200, 40, C_WHITE, "TimeF 0 %d", WaitTimeFlg[0]);
	DrawFormatString(200, 60, C_WHITE, "Time %d", WaitTime[0]);
	DrawFormatString(200, 80, C_WHITE, "TimeC %d", WaitTimeCnt[0]);
	DrawFormatString(200, 100, C_WHITE, "AnimC %d", AnimCnt[0]);
	DrawFormatString(200, 120, C_WHITE, "FinFlg %d", FinAnimFlg[0]);

	DrawFormatString(300, 40, C_WHITE, "TimeF 1 %d", WaitTimeFlg[1]);
	
#endif // DEBUG

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

void Cloud::AnimCloud(int i) 
{
	if (AnimCnt[i] >= 0 && AnimCnt[i] <= 2) {
		NowImg[i] = Img[0];
	}
	else if (AnimCnt[i] >= 3 && AnimCnt[i] <= 5) {
		NowImg[i] = Img[1];
	}
	else if (AnimCnt[i] <= 6 && AnimCnt[i] <= 8) {
		NowImg[i] = Img[2];
	}
}