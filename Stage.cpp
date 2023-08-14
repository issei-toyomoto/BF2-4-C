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
	SeaAnimCount = 0;
	DeathFlg = 0;
	Seax = 0;
	Seay = 430;
	SeaAnimFlg = 0;
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

void gStage::Draw(int gStageState) const
{
	/*ステージ遷移*/
	switch (gStageState)
	{
	case 1: // ステージ1
		/*DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");*/
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(S_Ground_Left_XU, S_Ground_Left_YU, gGameImg[8], TRUE);
		DrawGraph(S_Ground_Right_XU, S_Ground_Right_YU, gGameImg[10], TRUE);
		DrawGraph(S_Sky_Ground_0_XU, S_Sky_Ground_0_YU, gGameImg[0], TRUE);
		
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		break;
	case 2: // ステージ2
		/*DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");*/
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(S_Sky_Ground_0_XU, S_Sky_Ground_0_YU, gGameImg[0], TRUE);
		DrawGraph(S2_Sky_Ground_0_XU, S2_Sky_Ground_0_YU, gGameImg[1], TRUE);
		DrawGraph(S2_Sky_Ground_1_XU, S2_Sky_Ground_1_YU, gGameImg[1], TRUE);
		DrawGraph(S_Ground_Left_XU, S_Ground_Left_YU, gGameImg[8], TRUE);
		DrawGraph(S_Ground_Right_XU, S_Ground_Right_YU, gGameImg[10], TRUE);

		break;
	case 3: // ステージ3
		/*DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");*/
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(S3_Sky_Ground_1_XU, S3_Sky_Ground_1_YU, gGameImg[2], TRUE);
		DrawGraph(S3_Sky_SGround_0_XU, S3_Sky_SGround_0_YU, gGameImg[3], TRUE);
		DrawGraph(S3_Sky_SGround_1_XU, S3_Sky_SGround_1_YU, gGameImg[3], TRUE);
		DrawGraph(S3_Sky_SGround_2_XU, S3_Sky_SGround_2_YU, gGameImg[3], TRUE);
		DrawGraph(S3_Sky_Ground_0_XU, S3_Sky_Ground_0_YU, gGameImg[4], TRUE);
		DrawGraph(S_Ground_Left_XU, S_Ground_Left_YU, gGameImg[8], TRUE);
		DrawGraph(S_Ground_Right_XU, S_Ground_Right_YU, gGameImg[10], TRUE);

		break;
	case 4: // ステージ4
		/*DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");*/
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(S4_Sky_Ground_0_XU, S4_Sky_Ground_0_YU, gGameImg[5], TRUE);
		DrawGraph(S4_Sky_Ground_1_XU, S4_Sky_Ground_1_YU, gGameImg[5], TRUE);
		DrawGraph(S4_Sky_Ground_2_XU, S4_Sky_Ground_2_YU, gGameImg[5], TRUE);
		DrawGraph(S4_Sky_Ground_3_XU, S4_Sky_Ground_3_YU, gGameImg[5], TRUE);
		DrawGraph(S4_Sky_Ground_4_XU, S4_Sky_Ground_4_YU, gGameImg[5], TRUE);
		DrawGraph(S_Ground_Left_XU, S_Ground_Left_YU, gGameImg[9], TRUE);
		DrawGraph(S_Ground_Right_XU, S_Ground_Right_YU, gGameImg[11], TRUE);

		break;
	case 5: // ステージ5
		/*DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");*/
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(S5_Sky_Ground_0_XU, S5_Sky_Ground_0_YU, gGameImg[5], TRUE);
		DrawGraph(S5_Sky_Ground_1_XU, S5_Sky_Ground_1_YU, gGameImg[5], TRUE);
		DrawGraph(S5_Sky_Ground_2_XU, S5_Sky_Ground_2_YU, gGameImg[5], TRUE);
		DrawGraph(S5_Sky_SGround_0_XU, S5_Sky_SGround_0_YU, gGameImg[6], TRUE);
		DrawGraph(S5_Sky_SGround_1_XU, S5_Sky_SGround_1_YU, gGameImg[6], TRUE);
		DrawGraph(S5_Sky_SGround_2_XU, S5_Sky_SGround_2_YU, gGameImg[7], TRUE);
		DrawGraph(S_Ground_Left_XU, S_Ground_Left_YU, gGameImg[9], TRUE);
		DrawGraph(S_Ground_Right_XU, S_Ground_Right_YU, gGameImg[11], TRUE);

		break;
	default:
		break;
	}

	/*DrawFormatString(20, 300, C_RED, "%d", DeathFlg);*/
	DrawFormatString(80, 300, C_RED, "%d", SeaAnimCount);
	/*DrawFormatString(60, 300, C_RED, "%d", Seay);
	DrawFormatString(80, 300, C_RED, "%d", Seax);*/
	DrawFormatString(0, 200, C_RED, "%d", px);
	DrawFormatString(20, 300, C_RED, "%d", py);
	if (SeaAnimCount < 15 && SeaAnimCount > 0 && SeaAnimFlg == 1)
	{
		DrawGraph(Seax, Seay, SeaAnim[0], TRUE);
	}
	else if (SeaAnimCount < 30 && SeaAnimCount > 15 &&  SeaAnimFlg  == 1)
	{
		DrawGraph(Seax, Seay, SeaAnim[1], TRUE);
	}
	else if (SeaAnimCount < 45 && SeaAnimCount > 30 &&  SeaAnimFlg == 1)
	{
		DrawGraph(Seax, Seay, SeaAnim[2], TRUE);
	}
}

void gStage::Update()
{
	px = (int)Player::PlayerX;
	py = (int)Player::PlayerY;
	DeathFlg = Player::Death;

	gStage::SeaBottom();
	if (DeathFlg == 1)
	{
		SeaAnimFlg = 1;
	}
	if (SeaAnimFlg == 1)
	{
		++SeaAnimCount;
	}
	if (SeaAnimCount > 60)
	{
		SeaAnimCount = 0;
		DeathFlg = 0;
		SeaAnimFlg = 0;
	}

}
void gStage::SeaBottom()
{
	int pxL, pyL;
	pxL = (int)px;
	pyL = (int)py;
	if (pyL > Seay && DeathFlg == 0)
	{
		DeathFlg = 1;
		Seax = pxL;
		Seay = 400;
		/*Seay = pyL;*/
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