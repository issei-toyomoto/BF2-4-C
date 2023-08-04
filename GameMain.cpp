#include "DxLib.h"
#include "GameMain.h"
#include "Common.h"
#include "stdio.h"
#include "Player.h"
#include "bubble.h"
#include "Thunderbolt.h"
#include "Fish.h"
#include "TitleScene.h"
#include "Stage.h"
#include "InputKey.h"

//#define DEBUG

int GameMain::GameOverFont;
int GameMain::GameoverFlg;
int GameMain::WaitTime;

AbstractScene* GameMain::Update()
{
	InputKey::Update();
	player.Update(gStageState);
	BUBBLE.Update();
	enemy.Update();
	fish.Update();
	thunder.Update(gStageState);
	ui.Update();
	stage.Update();
	

	if (InputKey::GetKey(PAD_INPUT_1) == TRUE) { // STARTが押されたとき
		if (GameoverFlg == 0) { // まだ一度もPause状態になってないなら
			GameoverFlg = 1; // Pause状態になるというフラグ
		}
		else {
			GameoverFlg = 0;
		}
	}
	if (GameoverFlg == 1) {
		GameOver();
	}
	if (WaitTime > 180) {
		WaitTime = 0;
		return new Title();
	}

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
	stage.Draw(gStageState);
	thunder.Draw();
	BUBBLE.Draw();
	enemy.Draw();
	fish.Draw();
	ui.Draw();
	player.Draw();

	DrawGraph(160, 455, gGameImg[12], TRUE);//海の表示
	DrawGraph(0, 455, gGameImg[12], TRUE);
	DrawGraph(480, 455, gGameImg[12], TRUE);
	DrawFormatString(200, 300, C_RED, "%d", GameoverFlg);
	if (GameoverFlg == 1) {
		DrawGraph(200, 200, GameOverFont, TRUE);
	}

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
// ゲームオーバー画面
void GameMain::GameOver()
{
	WaitTime++;
}