#include "DxLib.h"
#include "GameMain.h"
#include "Common.h"
#include "stdio.h"
#include "Player.h"
#include"bubble.h"
#include"Thunderbolt.h"
#include"Fish.h"
#include"Stage.h"
#define DEBUG

//GameMain::GameMain() 
//{
//
//}
//
//GameMain::~GameMain() 
//{
//
//}

AbstractScene* GameMain::Update()
{
	player.Update(gStageState);
	BUBBLE.Update();
	enemy.Update();
	fish.Update();
	thunder.Update();

	if (CheckHitKey(KEY_INPUT_1)) {
		gStageState = 1;
	}
	else if (CheckHitKey(KEY_INPUT_2)) {
		gStageState = 2;
	}
	else if (CheckHitKey(KEY_INPUT_3)) {
		gStageState = 3;
	}
	else if (CheckHitKey(KEY_INPUT_4)) {
		gStageState = 4;
	}
	else if (CheckHitKey(KEY_INPUT_5)) {
		gStageState = 5;
	}
	else if (CheckHitKey(KEY_INPUT_6)) {
		return nullptr;

	}
	return this;
}

void GameMain::Draw()const
{
	/*stage.Draw();*/
	thunder.Draw();
	BUBBLE.Draw();
	player.Draw();
	enemy.Draw();
	fish.Draw();
	ui.Draw();

	/*ステージ遷移*/
	switch (gStageState)
	{
	case 1: // ステージ1
		/*DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");*/
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(S_Ground_Left_XU, S_Ground_Left_YU, gGameImg[8], TRUE);
		DrawGraph(S_Ground_Right_XU, S_Ground_Right_YU, gGameImg[10], TRUE);
		DrawGraph(S_Sky_Ground_0_XU, S_Sky_Ground_0_YU, gGameImg[0], TRUE);
		DrawGraph(160, 455, gGameImg[12], TRUE);
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		break;
	case 2: // ステージ2
		/*DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");*/
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(S_Sky_Ground_0_XU, S_Sky_Ground_0_YU, gGameImg[0], TRUE);
		DrawGraph(S2_Sky_Ground_0_XU, S2_Sky_Ground_0_YU, gGameImg[1], TRUE);
		DrawGraph(S2_Sky_Ground_1_XU, S2_Sky_Ground_1_YU, gGameImg[1], TRUE);
		DrawGraph(S_Ground_Left_XU, S_Ground_Left_YU , gGameImg[8], TRUE);
		DrawGraph(S_Ground_Right_XU, S_Ground_Right_YU, gGameImg[10], TRUE);
		DrawGraph(160, 455, gGameImg[12], TRUE);
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
		DrawGraph(160, 455, gGameImg[12], TRUE);
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
		DrawGraph(160, 455, gGameImg[12], TRUE);
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
		DrawGraph(160, 455, gGameImg[12], TRUE);
		break;
	default:
		break;
	}
	/*gstage.DrawStage1();*/

#ifdef DEBUG
	//ステージの当たり判定(ステージ１)
	if (gStageState == 1) {
		//左下
		DrawBox(S_Ground_Left_XU, S_Ground_Left_YU, S_Ground_Left_XL, S_Ground_Left_YL, C_RED, FALSE);
		DrawLine(S_Ground_Left_XU, S_Ground_Left_YU, S_Ground_Left_XL, S_Ground_Left_YL, C_RED);
		//中央
		DrawBox(S_Sky_Ground_0_XU, S_Sky_Ground_0_YU, S_Sky_Ground_0_XL, S_Sky_Ground_0_YL, C_RED, FALSE);
		DrawLine(S_Sky_Ground_0_XU, S_Sky_Ground_0_YU, S_Sky_Ground_0_XL, S_Sky_Ground_0_YL, C_RED);
		//右下
		DrawBox(S_Ground_Right_XU, S_Ground_Right_YU, S_Ground_Right_XL, S_Ground_Right_YL, C_RED, FALSE);
		DrawLine(S_Ground_Right_XU, S_Ground_Right_YU, S_Ground_Right_XL, S_Ground_Right_YL, C_RED);
	}
	else if (gStageState == 2) {
		//左下
		DrawBox(S_Ground_Left_XU, S_Ground_Left_YU, S_Ground_Left_XL, S_Ground_Left_YL, C_RED, FALSE);
		DrawLine(S_Ground_Left_XU, S_Ground_Left_YU, S_Ground_Left_XL, S_Ground_Left_YL, C_RED);
		//中央
		DrawBox(S_Sky_Ground_0_XU, S_Sky_Ground_0_YU, S_Sky_Ground_0_XL, S_Sky_Ground_0_YL, C_RED, FALSE);
		DrawLine(S_Sky_Ground_0_XU, S_Sky_Ground_0_YU, S_Sky_Ground_0_XL, S_Sky_Ground_0_YL, C_RED);
		//右下
		DrawBox(S_Ground_Right_XU, S_Ground_Right_YU, S_Ground_Right_XL, S_Ground_Right_YL, C_RED, FALSE);
		DrawLine(S_Ground_Right_XU, S_Ground_Right_YU, S_Ground_Right_XL, S_Ground_Right_YL, C_RED);
		//左
		DrawBox(S2_Sky_Ground_0_XU, S2_Sky_Ground_0_YU, S2_Sky_Ground_0_XL, S2_Sky_Ground_0_YL, C_RED, FALSE);
		DrawLine(S2_Sky_Ground_0_XU, S2_Sky_Ground_0_YU, S2_Sky_Ground_0_XL, S2_Sky_Ground_0_YL, C_RED);
		//左下
		DrawBox(S2_Sky_Ground_1_XU, S2_Sky_Ground_1_YU, S2_Sky_Ground_1_XL, S2_Sky_Ground_1_YL, C_RED, FALSE);
		DrawLine(S2_Sky_Ground_1_XU, S2_Sky_Ground_1_YU, S2_Sky_Ground_1_XL , S2_Sky_Ground_1_YL, C_RED);
	}
	else if(gStageState == 3) {
		// 左下
		DrawBox(S_Ground_Left_XU, S_Ground_Left_YU, S_Ground_Left_XL, S_Ground_Left_YL, C_RED, FALSE);
		DrawLine(S_Ground_Left_XU, S_Ground_Left_YU, S_Ground_Left_XL, S_Ground_Left_YL, C_RED);
		//右下
		DrawBox(S_Ground_Right_XU, S_Ground_Right_YU, S_Ground_Right_XL, S_Ground_Right_YL, C_RED, FALSE);
		DrawLine(S_Ground_Right_XU, S_Ground_Right_YU, S_Ground_Right_XL, S_Ground_Right_YL, C_RED);
		// 左鍾乳石
		DrawBox(S3_Sky_SGround_0_XU, S3_Sky_SGround_0_YU, S3_Sky_SGround_0_XL, S3_Sky_SGround_0_YL, C_RED, FALSE);
		DrawLine(S3_Sky_SGround_0_XU, S3_Sky_SGround_0_YU, S3_Sky_SGround_0_XL, S3_Sky_SGround_0_YL, C_RED);
		DrawBox(S3_Sky_SStone_0_XU, S3_Sky_SStone_0_YU, S3_Sky_SStone_0_XL, S3_Sky_SStone_0_YL, C_RED, FALSE);
		DrawLine(S3_Sky_SStone_0_XU, S3_Sky_SStone_0_YU, S3_Sky_SStone_0_XL, S3_Sky_SStone_0_YL, C_RED);
		// 中央鍾乳石
		DrawBox(S3_Sky_SGround_1_XU, S3_Sky_SGround_1_YU, S3_Sky_SGround_1_XL, S3_Sky_SGround_1_YL, C_RED, FALSE);
		DrawLine(S3_Sky_SGround_1_XU, S3_Sky_SGround_1_YU, S3_Sky_SGround_1_XL, S3_Sky_SGround_1_YL, C_RED);
		DrawBox(S3_Sky_SStone_1_XU, S3_Sky_SStone_1_YU, S3_Sky_SStone_1_XL, S3_Sky_SStone_1_YL, C_RED, FALSE);
		DrawLine(S3_Sky_SStone_1_XU, S3_Sky_SStone_1_YU, S3_Sky_SStone_1_XL, S3_Sky_SStone_1_YL, C_RED);
		// 右鍾乳石
		DrawBox(S3_Sky_SGround_2_XU, S3_Sky_SGround_2_YU, S3_Sky_SGround_2_XL, S3_Sky_SGround_2_YL, C_RED, FALSE);
		DrawLine(S3_Sky_SGround_2_XU, S3_Sky_SGround_2_YU, S3_Sky_SGround_2_XL, S3_Sky_SGround_2_YL, C_RED);
		DrawBox(S3_Sky_SStone_2_XU, S3_Sky_SStone_2_YU, S3_Sky_SStone_2_XL, S3_Sky_SStone_2_YL, C_RED, FALSE);
		DrawLine(S3_Sky_SStone_2_XU, S3_Sky_SStone_2_YU, S3_Sky_SStone_2_XL, S3_Sky_SStone_2_YL, C_RED);
		// 上空中床
		DrawBox(S3_Sky_Ground_0_XU, S3_Sky_Ground_0_YU, S3_Sky_Ground_0_XL, S3_Sky_Ground_0_YL, C_RED, FALSE);
		DrawLine(S3_Sky_Ground_0_XU, S3_Sky_Ground_0_YU, S3_Sky_Ground_0_XL, S3_Sky_Ground_0_YL, C_RED);
		// 下空中床
		DrawBox(S3_Sky_Ground_1_XU, S3_Sky_Ground_1_YU, S3_Sky_Ground_1_XL, S3_Sky_Ground_1_YL, C_RED, FALSE);
		DrawLine(S3_Sky_Ground_1_XU, S3_Sky_Ground_1_YU, S3_Sky_Ground_1_XL, S3_Sky_Ground_1_YL, C_RED);
	}
	else if (gStageState == 4) {
		// 左下
		DrawBox(S_Ground_Left_XU, S_Ground_Left_YU, S_Ground_Left_XL, S_Ground_Left_YL, C_RED, FALSE);
		DrawLine(S_Ground_Left_XU, S_Ground_Left_YU, S_Ground_Left_XL, S_Ground_Left_YL, C_RED);
		//右下
		DrawBox(S_Ground_Right_XU, S_Ground_Right_YU, S_Ground_Right_XL, S_Ground_Right_YL, C_RED, FALSE);
		DrawLine(S_Ground_Right_XU, S_Ground_Right_YU, S_Ground_Right_XL, S_Ground_Right_YL, C_RED);
		// 台1
		DrawBox(S4_Sky_Ground_0_XU, S4_Sky_Ground_0_YU, S4_Sky_Ground_0_XL, S4_Sky_Ground_0_YL, C_RED, FALSE);
		DrawLine(S4_Sky_Ground_0_XU, S4_Sky_Ground_0_YU, S4_Sky_Ground_0_XL, S4_Sky_Ground_0_YL, C_RED);
		// 台2
		DrawBox(S4_Sky_Ground_1_XU, S4_Sky_Ground_1_YU, S4_Sky_Ground_1_XL, S4_Sky_Ground_1_YL, C_RED, FALSE);
		DrawLine(S4_Sky_Ground_1_XU, S4_Sky_Ground_1_YU, S4_Sky_Ground_1_XL, S4_Sky_Ground_1_YL, C_RED);
		// 台3
		DrawBox(S4_Sky_Ground_2_XU, S4_Sky_Ground_2_YU, S4_Sky_Ground_2_XL, S4_Sky_Ground_2_YL, C_RED, FALSE);
		DrawLine(S4_Sky_Ground_2_XU, S4_Sky_Ground_2_YU, S4_Sky_Ground_2_XL, S4_Sky_Ground_2_YL, C_RED);
		// 台4
		DrawBox(S4_Sky_Ground_3_XU, S4_Sky_Ground_3_YU, S4_Sky_Ground_3_XL, S4_Sky_Ground_3_YL, C_RED, FALSE);
		DrawLine(S4_Sky_Ground_3_XU, S4_Sky_Ground_3_YU, S4_Sky_Ground_3_XL, S4_Sky_Ground_3_YL, C_RED);
		// 台5
		DrawBox(S4_Sky_Ground_4_XU, S4_Sky_Ground_4_YU, S4_Sky_Ground_4_XL, S4_Sky_Ground_4_YL, C_RED, FALSE);
		DrawLine(S4_Sky_Ground_4_XU, S4_Sky_Ground_4_YU, S4_Sky_Ground_4_XL, S4_Sky_Ground_4_YL, C_RED);
	}
	else if(gStageState == 5) {
		// 左下
		DrawBox(S_Ground_Left_XU, S_Ground_Left_YU, S_Ground_Left_XL, S_Ground_Left_YL, C_RED, FALSE);
		DrawLine(S_Ground_Left_XU, S_Ground_Left_YU, S_Ground_Left_XL, S_Ground_Left_YL, C_RED);
		//右下
		DrawBox(S_Ground_Right_XU, S_Ground_Right_YU, S_Ground_Right_XL, S_Ground_Right_YL, C_RED, FALSE);
		DrawLine(S_Ground_Right_XU, S_Ground_Right_YU, S_Ground_Right_XL, S_Ground_Right_YL, C_RED);
		// 鍾乳石1
		DrawBox(S5_Sky_SGround_0_XU, S5_Sky_SGround_0_YU, S5_Sky_SGround_0_XL, S5_Sky_SGround_0_YL, C_RED, FALSE);
		DrawLine(S5_Sky_SGround_0_XU, S5_Sky_SGround_0_YU, S5_Sky_SGround_0_XL, S5_Sky_SGround_0_YL, C_RED);
		// 鍾乳石2
		DrawBox(S5_Sky_SGround_1_XU, S5_Sky_SGround_1_YU, S5_Sky_SGround_1_XL, S5_Sky_SGround_1_YL, C_RED, FALSE);
		DrawLine(S5_Sky_SGround_1_XU, S5_Sky_SGround_1_YU, S5_Sky_SGround_1_XL, S5_Sky_SGround_1_YL, C_RED);
		// 鍾乳石3
		DrawBox(S5_Sky_SGround_2_XU, S5_Sky_SGround_2_YU, S5_Sky_SGround_2_XL, S5_Sky_SGround_2_YL, C_RED, FALSE);
		DrawLine(S5_Sky_SGround_2_XU, S5_Sky_SGround_2_YU, S5_Sky_SGround_2_XL, S5_Sky_SGround_2_YL, C_RED);
		// 台1
		DrawBox(S5_Sky_Ground_0_XU, S5_Sky_Ground_0_YU, S5_Sky_Ground_0_XL, S5_Sky_Ground_0_YL, C_RED, FALSE);
		DrawLine(S5_Sky_Ground_0_XU, S5_Sky_Ground_0_YU, S5_Sky_Ground_0_XL, S5_Sky_Ground_0_YL, C_RED);
		// 台2
		DrawBox(S5_Sky_Ground_1_XU, S5_Sky_Ground_1_YU, S5_Sky_Ground_1_XL, S5_Sky_Ground_1_YL, C_RED, FALSE);
		DrawLine(S5_Sky_Ground_1_XU, S5_Sky_Ground_1_YU, S5_Sky_Ground_1_XL, S5_Sky_Ground_1_YL, C_RED);
		// 台3
		DrawBox(S5_Sky_Ground_2_XU, S5_Sky_Ground_2_YU, S5_Sky_Ground_2_XL, S5_Sky_Ground_2_YL, C_RED, FALSE);
		DrawLine(S5_Sky_Ground_2_XU, S5_Sky_Ground_2_YU, S5_Sky_Ground_2_XL, S5_Sky_Ground_2_YL, C_RED);

	}
#endif // DEBUG

}