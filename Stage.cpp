#include "Stage.h"
#include"Common.h"
#include "InputKey.h"
#include "StageImg.h"
#include "Player.h"

gStage::gStage()
{
	gGameImg[0] =  LoadGraph("images/Stage_Footing01.png");      // ステージの足場1
	gGameImg[1] =  LoadGraph("images/Stage_Footing02.png");      // ステージの足場2
	gGameImg[2] =  LoadGraph("images/Stage_Footing03.png");      // ステージの足場3
	gGameImg[3] =  LoadGraph("images/Stage_Footing04.png");      // ステージの足場4
	gGameImg[4] =  LoadGraph("images/Stage_Footing05.png");      // ステージの足場5
	gGameImg[5] =  LoadGraph("images/Stage_Footing06.png");      // ステージの足場6
	gGameImg[6] =  LoadGraph("images/Stage_Footing07.png");      // ステージの足場7
	gGameImg[7] =  LoadGraph("images/Stage_Footing08.png");      // ステージの足場8
	gGameImg[8] =  LoadGraph("images/Stage_Land_Left01.png");    // ステージ左下の足場1
	gGameImg[9] =  LoadGraph("images/Stage_Land_Left02.png");    // ステージ左下の足場2
	gGameImg[10] = LoadGraph("images/Stage_Land_Right01.png");   // ステージ右下の足場1
	gGameImg[11] = LoadGraph("images/Stage_Land_Right02.png");   // ステージ右下の足場2
	gGameImg[12] = LoadGraph("images/Stage_Sea01.png");          // 海の画像
	gGameImg[13] = LoadGraph("images/ningen.png");               // プレイヤー画像
	gSeaImg = LoadGraph("images/Stage_Sea01.png");           // 海の画像
	LoadDivGraph("images-20230711T024428Z-001/images/Stage/Stage_SplashAnimation.png", 3, 3, 1, 64, 32, SeaAnim);
	MousePointx = 0;
	MousePointy = 0;
	gGameState = 0;
	px = 0;
	py = 0;
	SeaPos = 400;
	SeaAnimCount = 0;
	DeathFlg = 0;
	Seax = 0;
	Seay = 0;
}

void gStage::StageState()
{
	//switch (gGameState)
	//{
	//case 0:
	//	DrawStage1();
	//	return;
	//case 1:
	//	DrawStage2();
	//case 2:
	//	DrawStage3();
	//case 3:
	//	DrawStage4();
	//case 4:
	//	DrawStage5();
	//default:
	//	break;
	//}
}

void gStage::Draw() const
{
	DrawFormatString(20, 300, C_RED, "%d", DeathFlg);
	DrawFormatString(40, 300, C_RED, "%d", SeaAnimCount);
	DrawFormatString(60, 300, C_RED, "%d", Seay);
	DrawFormatString(80, 300, C_RED, "%d", Seax);
	DrawFormatString(0, 200, C_RED, "%d", px);
	DrawFormatString(20, 200, C_RED, "%d", py);
	if (SeaAnimCount < 5 && SeaAnimCount > 1 && DeathFlg == 1)
	{
		DrawGraph(Seax, Seay, SeaAnim[0], TRUE);
	}
	else if (SeaAnimCount < 10 && SeaAnimCount > 5 &&  DeathFlg == 1)
	{
		DrawGraph(Seax, Seay, SeaAnim[1], TRUE);
	}
	else if (SeaAnimCount < 15 && SeaAnimCount > 10 &&  DeathFlg == 1)
	{
		DrawGraph(Seax, Seay, SeaAnim[2], TRUE);
	}
}

void gStage::Update()
{
	px = Player::PlayerX;
	py = Player::PlayerY;
	DeathFlg = Player::Death;

	gStage::SeaBottom();

	if (DeathFlg == 1)
	{
		SeaAnimCount++;
	}
	if (SeaAnimCount < 60)
	{
		SeaAnimCount = 0;
		DeathFlg = 0;
	}

}
void gStage::SeaBottom()
{
	int pxL, pyL;
	pxL = (int)px + 18;
	pyL = (int)py + 14;
	if (pyL > SeaPos)
	{
		DeathFlg = 1;
		Seax = pxL;
		Seay = pyL;
	}
}

void gStage::DrawStage1() const
{

}

void gStage::DrawStage2() const
{

}

void gStage::DrawStage3() const
{

}

void gStage::DrawStage4() const
{

}

void gStage::DrawStage5() const
{

}