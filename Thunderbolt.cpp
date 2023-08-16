#include "DxLib.h"
#include "Thunderbolt.h"
#include "Cloud.h"
#include "Common.h"
#include "Thunder.h"

#define PI    3.1415926535897932384626433832795f

//#define DEBUG

bool Thunderbolt::FinAnimFlg[2];
int Thunderbolt::Position[2];

Thunderbolt::Thunderbolt()
{
	LoadDivGraph("images/Stage_ThunderAnimation.png", 6, 6, 1, 64, 64, Img);
	for (int i = 0; i < 2; i++) {
		FinCloudAnimFlg[i] = false;
		AnimCnt[i] = 0;
		FinAnimFlg[i] = false;
	}

	Position[0] = GetRand(3);
	Position[1] = GetRand(3);
}

void Thunderbolt::Update(int Stage)
{
	for (Num = 0; Num < 2; Num++) {
		if (Thunder::ThunderUnderSea[Num] == true) {
			Position[Num] = GetRand(3);
			Thunder::ThunderUnderSea[Num] = false;
		}

		ThunderboltPosition(Num, Stage);//雷の位置決め
		FinCloudAnimFlg[Num] = Cloud::FinAnimFlg[Num];//Cloudからの変数を受け取る
		if (FinCloudAnimFlg[Num] == true && FinAnimFlg[Num] == false && Thunder::State[Num] == NO_USE) {
			ThunderboltAnim(Num);
			AnimCnt[Num]++;
		}

		/*if (FinCloudAnimFlg[Num] == false) {
			FinAnimFlg[Num] = false;
		}*/

		if (FinAnimFlg[Num] == true) {
			Cloud::FinAnimFlg[Num] = false;
		}

		if (AnimCnt[Num] > 48) {
			AnimCnt[Num] = 0;
			FinAnimFlg[Num] = true;
		}
	}
	
}

void Thunderbolt::Draw(int Stage) const
{
	if (Stage == 1) {
		if (Thunder::State[0] == NO_USE) {
			if (FinCloudAnimFlg[0] == true && FinAnimFlg[0] == false) {
				if (Position[0] == 0 || Position[0] == 1) {
					DrawRotaGraph(X[0], Y[0], 1.0f, PI, NowImg[0], TRUE);
				}
				else if (Position[0] == 2 || Position[0] == 3) {
					DrawGraph(X[0], Y[0], NowImg[0], TRUE);
				}
			}
		}
		
		/*if (Thunder::State[1] == NO_USE) {
			if (FinCloudAnimFlg[1] == true && FinAnimFlg[1] == false) {
				if (Position[1] == 0 || Position[1] == 1) {
					DrawRotaGraph(X[1], Y[1], 1.0f, PI, NowImg[1], TRUE);
				}
				else if (Position[1] == 2 || Position[1] == 3) {
					DrawGraph(X[1], Y[1], NowImg[1], TRUE);
				}
			}
		}*/
	}

#ifdef DEBUG
	DrawFormatString(100, 40, C_WHITE, "FinFlg %d", FinCloudAnimFlg[0]);
	DrawFormatString(100, 60, C_WHITE, "X %d", X[0]);
	DrawFormatString(100, 80, C_WHITE, "Y %d", Y[0]);
	DrawFormatString(100, 100, C_WHITE, "Posi %d", Position[0]);
	DrawFormatString(100, 120, C_WHITE, "AnimCnt %d", AnimCnt[0]);
#endif // DEBUG

}

//雷が出るときのアニメーション
void Thunderbolt::ThunderboltAnim(int i)
{
	if (AnimCnt[i] >= 0 && AnimCnt[i] <= 7) {
		NowImg[i] = Img[0];
	}
	else if (AnimCnt[i] >= 8 && AnimCnt[i] <= 15) {
		NowImg[i] = Img[1];
	}
	else if (AnimCnt[i] >= 16 && AnimCnt[i] <= 23) {
		NowImg[i] = Img[2];
	}
	else if (AnimCnt[i] >= 24 && AnimCnt[i] <= 31) {
		NowImg[i] = Img[3];
	}
	else if (AnimCnt[i] >= 32 && AnimCnt[i] <= 39) {
		NowImg[i] = Img[4];
	}
	else if (AnimCnt[i] >= 40 && AnimCnt[i] <= 47) {
		NowImg[i] = Img[5];
	}
}

void Thunderbolt::ThunderboltPosition(int i, int Stage)
{
	if (Stage == 1) {
		if (Position[0] == 0) {//左上
			X[0] = Stage_1_X + 40;
			Y[0] = Stage_1_Y - 25;
		}
		else if (Position[0] == 1) {//右上
			X[0] = Stage_1_X + 100;
			Y[0] = Stage_1_Y - 20;
		}
		else if (Position[0] == 2) {//左下
			X[0] = Stage_1_X;
			Y[0] = Stage_1_Y + 55;
		}
		else if (Position[0] == 3) {//右上
			X[0] = Stage_1_X + 64;
			Y[0] = Stage_1_Y + 45;
		}
	}
	else if (Stage == 2) {
		if (Position[0] == 0) {//左上

		}
		else if (Position[0] == 1) {//右上

		}
		else if (Position[0] == 2) {//左下

		}
		else if (Position[0] == 3) {//右上

		}

		if (Position[1] == 0) {//左上

		}
		else if (Position[1] == 1) {//右上

		}
		else if (Position[1] == 2) {//左下

		}
		else if (Position[1] == 3) {//右上

		}
	}
	else if (Stage == 3) {
		if (Position[0] == 0) {//左上

		}
		else if (Position[0] == 1) {//右上

		}
		else if (Position[0] == 2) {//左下

		}
		else if (Position[0] == 3) {//右上

		}

		if (Position[1] == 0) {//左上

		}
		else if (Position[1] == 1) {//右上

		}
		else if (Position[1] == 2) {//左下

		}
		else if (Position[1] == 3) {//右上

		}
	}
	else if (Stage == 4) {
		if (Position[0] == 0) {//左上

		}
		else if (Position[0] == 1) {//右上

		}
		else if (Position[0] == 2) {//左下

		}
		else if (Position[0] == 3) {//右上

		}

		if (Position[1] == 0) {//左上

		}
		else if (Position[1] == 1) {//右上

		}
		else if (Position[1] == 2) {//左下

		}
		else if (Position[1] == 3) {//右上

		}
	}
	else if (Stage == 5) {
		if (Position[0] == 0) {//左上

		}
		else if (Position[0] == 1) {//右上

		}
		else if (Position[0] == 2) {//左下

		}
		else if (Position[0] == 3) {//右上

		}

		if (Position[1] == 0) {//左上

		}
		else if (Position[1] == 1) {//右上

		}
		else if (Position[1] == 2) {//左下

		}
		else if (Position[1] == 3) {//右上

		}
	}
}