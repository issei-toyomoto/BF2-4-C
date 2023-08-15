#include "Thunder.h"
#include "Thunderbolt.h"
#include "Common.h"

#define DEBUG

bool Thunder::State[2];

Thunder::Thunder() 
{
	Num = 0;

	LoadDivGraph("images/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, Img);
	for (int i = 0; i < 2; i++) {
		NowImg[i] = Img[0];
		AnimCnt[i] = 0;
		X[i] = 0;
		Y[i] = 0;
		VectorX[i] = 0;
		VectorY[i] = 0;
		InitFlg[i] = false;
	}
}

//描画以外の更新を実装する
void Thunder::Update(int Stage) 
{
	for (Num = 0; Num < 2; Num++) {
		FinThunderboltAnimFlg[Num] = Thunderbolt::FinAnimFlg[Num];
		Position[Num] = Thunderbolt::Position[Num];

		if (InitFlg[Num] == false) {
			ThunderPosition(Num, Stage);
		}

		if (FinThunderboltAnimFlg[Num] == true) {
			ThunderAnim(Num);
			AnimCnt[Num]++;
			X[Num] += VectorX[Num];
			Y[Num] += VectorY[Num];
			State[Num] = USE;
		}

		

		if (AnimCnt[Num] > 8) {
			AnimCnt[Num] = 0;
		}
	}
}

//描画の更新を実装する
void Thunder::Draw() const 
{
	if (State[0] == USE) {
		DrawGraph(X[0], Y[0], NowImg[0], TRUE);
	}

#ifdef DEBUG
	DrawFormatString(0, 40, C_WHITE, "X %d", X[0]);
	DrawFormatString(0, 60, C_WHITE, "Y %d", Y[0]);
	DrawFormatString(0, 80, C_WHITE, "VX %d", VectorX[0]);
	DrawFormatString(0, 100, C_WHITE, "VY %d", VectorY[0]);
	DrawFormatString(0, 120, C_WHITE, "State %d", State[0]);
	DrawFormatString(0, 140, C_WHITE, "Flg %d", InitFlg[0]);
	DrawFormatString(0, 160, C_WHITE, "AnimCnt %d", AnimCnt[0]);
#endif // DEBUG

}

void Thunder::ThunderAnim(int i)
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

void Thunder::ThunderPosition(int i, int Stage) 
{
	if (Stage == 1) {
		if (Position[0] == 0) {//左上
			X[0] = Stage_1_X + 40;
			Y[0] = Stage_1_Y - 25;
			VectorX[0] = -1;
			VectorY[0] = -1;

			InitFlg[0] = true;
		}
		else if (Position[0] == 1) {//右上
			X[0] = Stage_1_X + 100;
			Y[0] = Stage_1_Y - 20;
			VectorX[0] = 1;
			VectorY[0] = -1;

			InitFlg[0] = true;
		}
		else if (Position[0] == 2) {//左下
			X[0] = Stage_1_X;
			Y[0] = Stage_1_Y + 55;
			VectorX[0] = -1;
			VectorY[0] = 1;

			InitFlg[0] = true;
		}
		else if (Position[0] == 3) {//右下
			X[0] = Stage_1_X + 64;
			Y[0] = Stage_1_Y + 45;
			VectorX[0] = 1;
			VectorY[0] = 1;

			InitFlg[0] = true;
		}
	}
}

void Thunder::ThunderCollision(int i, int Stage) 
{

}