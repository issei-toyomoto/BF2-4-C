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
			State[Num] = USE;
		}

		if (State[Num] == USE) {
			X[Num] += VectorX[Num];
			Y[Num] += VectorY[Num];
			ThunderCollision(Num, Stage);
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
		if (Position[i] == 0) {//左上
			X[i] = Stage_1_X + 30;
			Y[i] = Stage_1_Y - 60;
			VectorX[i] = -1;
			VectorY[i] = -1;

			InitFlg[i] = true;
		}
		else if (Position[i] == 1) {//右上
			X[i] = Stage_1_X + 90;
			Y[i] = Stage_1_Y - 70;
			VectorX[i] = 1;
			VectorY[i] = -1;

			InitFlg[i] = true;
		}
		else if (Position[i] == 2) {//左下
			X[i] = Stage_1_X;
			Y[i] = Stage_1_Y + 85;
			VectorX[i] = -1;
			VectorY[i] = 1;

			InitFlg[i] = true;
		}
		else if (Position[0] == 3) {//右下
			X[i] = Stage_1_X + 64;
			Y[i] = Stage_1_Y + 75;
			VectorX[i] = 1;
			VectorY[i] = 1;

			InitFlg[i] = true;
		}
	}
}

void Thunder::ThunderCollision(int i, int Stage) 
{
	int XU = X[i] + 4;
	int YU = Y[i] + 4;
	int XL = X[i] + 28;
	int YL = Y[i] + 28;

	if (Stage == 1) {
		//
		if (XU <= S_Ground_Left_XL && YL >= S_Ground_Left_YU + PlusPx) {//
			VectorX[i] *= -1;
		}
		if (YL >= S_Ground_Left_YU && YL <= S_Ground_Left_YU + PlusPx && XU <= S_Ground_Left_XL) {//
			VectorY[i] *= -1;
		}

		//
		if (XL >= S_Ground_Right_XU && YL >= S_Ground_Right_YU + PlusPx) {//
			VectorX[i] *= -1;
		}
		if (YL >= S_Ground_Right_YU && YL <= S_Ground_Right_YU + PlusPx && XL >= S_Ground_Right_XU) {//
			VectorY[i] *= -1;
		}

		//
		if (YL >= S_Sky_Ground_0_YU + PlusPx && YU <= S_Sky_Ground_0_YL - PlusPx) {//
			if (XU <= S_Sky_Ground_0_XL + PlusPx && XL >= S_Sky_Ground_0_XL) {//
				VectorX[i] *= -1;
			}
			else if (XL >= S_Sky_Ground_0_XU - PlusPx && XL <= S_Sky_Ground_0_XU) {//
				VectorX[i] *= -1;
			}
		}
		if (YL >= S_Sky_Ground_0_YU && YL <= S_Sky_Ground_0_YU + PlusPx && XU <= S_Sky_Ground_0_XL && XL >= S_Sky_Ground_0_XU) {//���
			VectorY[i] *= -1;
		}
		if (YU <= S_Sky_Ground_0_YL - PlusPx && YL >= S_Sky_Ground_0_YL) {//
			if (XU <= S_Sky_Ground_0_XL && XL >= S_Sky_Ground_0_XU) {
				VectorY[i] *= -1;
			}
		}

		//
		if (YU <= 0) {
			VectorY[i] *= -1;
		}

		//
		if (YL >= _SCREEN_HEIGHT_ + 50) {
			State[i] = NO_USE;
			InitFlg[i] = false;
		}

		//
		if (XL >= _SCREEN_WIDHT_) {
			VectorX[i] *= -1;
		}

		//
		if (XU <= 0) {
			VectorX[i] *= -1;
		}
	}
}