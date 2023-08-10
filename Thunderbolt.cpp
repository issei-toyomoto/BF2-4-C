#include "DxLib.h"
#include "Thunderbolt.h"
#include "Common.h"
#include "InputKey.h"
#include "Player.h"

//#define DEBUG

Thunder::Thunder()
{
	
}

void Thunder::Update(int Stage)
{
	
}

void Thunder::Draw() const 
{
	
}

//雷のチカチカアニメーション
void Thunder::ThunderAnim(int i)
{
	if (thunder[i].AnimCnt >= 0 && thunder[i].AnimCnt <= 2) {
		thunder[i].T_NowImg = thunder[i].Img[0];
	}
	else if (thunder[i].AnimCnt >= 3 && thunder[i].AnimCnt <= 5) {
		thunder[i].T_NowImg = thunder[i].Img[1];
	}
	else if (thunder[i].AnimCnt <= 6 && thunder[i].AnimCnt <= 8) {
		thunder[i].T_NowImg = thunder[i].Img[2];
	}
}

//雷が出るときのアニメーション
void Thunder::OutThunderAnim(int i) 
{
	if (OutThunder[i].OTAnimCnt >= 0 && OutThunder[i].OTAnimCnt <= 7) {
		OutThunder[i].Now_Img = OutThunder[i].Img[0];
	}
	else if (OutThunder[i].OTAnimCnt >= 8 && OutThunder[i].OTAnimCnt <= 15) {
		OutThunder[i].Now_Img = OutThunder[i].Img[1];
	}
	else if (OutThunder[i].OTAnimCnt >= 16 && OutThunder[i].OTAnimCnt <= 23) {
		OutThunder[i].Now_Img = OutThunder[i].Img[2];
	}
	else if (OutThunder[i].OTAnimCnt >= 24 && OutThunder[i].OTAnimCnt <= 31) {
		OutThunder[i].Now_Img = OutThunder[i].Img[3];
	}
	else if (OutThunder[i].OTAnimCnt >= 32 && OutThunder[i].OTAnimCnt <= 39) {
		OutThunder[i].Now_Img = OutThunder[i].Img[4];
	}
	else if (OutThunder[i].OTAnimCnt >= 40 && OutThunder[i].OTAnimCnt <= 47) {
		OutThunder[i].Now_Img = OutThunder[i].Img[5];
	}
}