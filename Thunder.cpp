#include "Thunder.h"
#include "Thunderbolt.h"
#include "Common.h"

Thunder::Thunder() 
{
	Num = 0;

	LoadDivGraph("images/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, Img);
	for (int i = 0; i < 2; i++) {
		NowImg[i] = Img[0];
		AnimCnt[i] = 0;
	}
}

//描画以外の更新を実装する
void Thunder::Update() 
{
	for (Num = 0; Num < 2; Num++) {
		FinThunderboltAnimFlg[Num] = Thunderbolt::FinAnimFlg[Num];
		if (FinThunderboltAnimFlg[Num] == true) {
			ThunderAnim(Num);
			AnimCnt[Num]++;
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
