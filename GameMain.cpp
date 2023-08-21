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
#include "Soundstorage.h"
#include "UI.h"

//#define DEBUG

int GameMain::GameOverFont;
int GameMain::GameOverFlg;
int GameMain::PauseWTime;
int GameMain::GameOverWTime;
int GameMain::PauseFlg;
bool GameMain::SoundFlg;
int GameMain::gStageState = 1;

AbstractScene* GameMain::Update()
{
	FPSCount++;
	if (FPSCount == 60) {
		FPSCount = 0;
	}
	if (SoundFlg == 0) {
		PlaySoundMem(ss.gStartSE, DX_PLAYTYPE_BACK, TRUE);
		SoundFlg = 1;
	}
	++PauseWTime;
	if (PhaseCount < 320) {
		PhaseFlg = 0;
		PhaseCount++;
	}
	else {
		PhaseFlg = 1;
	}
	// ポーズ状態、ゲームオーバー状態ではない間行う処理
	if (PauseFlg == 0 && GameOverFlg == 0 && ClearFlg == 0) {
		player.Update(gStageState);
		BUBBLE.Update(GameOverFlg);
		enemy.Update(gStageState);
		fish.Update();
		thunderbolt.Update(gStageState);
		cloud.Update();
		thunder.Update(gStageState);
		ui.Update(GameOverFlg);
		stage.Update();
	}
	// ポーズ状態に遷移する処理(startボタン)
	if (InputKey::GetKey(PAD_INPUT_8) == TRUE && PauseFlg == 0 && PauseWTime > 20) { // STARTが押された  // まだ一度もPause状態になってないなら
		PauseFlg = 1; // Pause状態になるというフラグ
		PauseWTime = 0;
		}
		else if(inputkey.GetKey(PAD_INPUT_8) == TRUE && PauseFlg == 1 && PauseWTime > 20) {
		PauseWTime = 0;
		PauseFlg = 0;
		}
	if (PauseFlg == 1) {
		Pause();
	}
	if (GameOverFlg == 0 && player.Life < 0) { // ゲームオーバーフラグが立っていないかつプレイヤーのライフが0を下回った時
		StopSoundMem(ss.gStartSE);
		StopSoundMem(ss.gSplashSE);
		PlaySoundMem(ss.GameOverSE, DX_PLAYTYPE_BACK, TRUE);
		GameOverFlg = 1; // GameOvereになるというフラグ
	}
	if (GameOverFlg == 1) {
		if (GameOverWTime < 540) {
			++GameOverWTime;
		}
		else { // 540カウントを超えた時行う処理
			ui.Update(GameOverFlg);
			BUBBLE.Update(GameOverFlg);
			GameOverFlg = 0;
			GameOverWTime = 0;
			return new Title();
		}
	}
#ifdef DEBUG
	if (ClearWTime < 150 && ClearFlg == 1) {
		++ClearWTime;
	}
	else  if(ClearWTime >=  150 && ClearFlg == 1) {
		if (gStageState > 4) {
			ui.Update(ClearFlg);
			BUBBLE.Update(ClearFlg);
			ClearWTime = 0;
			ClearFlg = 0;
			SoundFlg = 0;
			return new Title();
		}
		ClearWTime = 0;
		gStageState++;
		ClearFlg = 0;
		PhaseCount = 0;
	}
	if (inputkey.GetKeyDown(PAD_INPUT_7) && ClearFlg == 0 && gStageState < 6) {
		SoundFlg = 1;
		StopSoundMem(ss.gStartSE);
		PlaySoundMem(ss.gStageClearSE, DX_PLAYTYPE_BACK, TRUE);
		ClearFlg = 1;
	}
	else if (CheckHitKey(KEY_INPUT_6)) {
		return nullptr;
	}
	return this;
#endif // DEBUG
}

void GameMain::Draw()const
{
	if (FPSCount > 30 && PhaseFlg == 0) {
		DrawGraph(250, 50, PhaseUI, TRUE);
		DrawGraph(370, 42, UINumber[gStageState], TRUE);
	}
	stage.Draw(gStageState);
	ui.Draw();
	// ポーズ状態でなければ描画する
	if (PauseFlg == 0) {
		thunderbolt.Draw(gStageState);
		cloud.Draw(gStageState);
		thunder.Draw();
		BUBBLE.Draw();
		enemy.Draw();
		fish.Draw();
		player.Draw();
	}
	// ポーズフラグが立った時描画する
	if (PauseFlg == 1) {
		DrawString(220, 320, "--- ポーズ中 ---", C_WHITE);
	}
	// ゲームオーバーフラグが立った時描画する
	if (GameOverFlg == 1) {
		DrawGraph(210, 200, GameOverFont, TRUE);
	}
	DrawGraph(160, 455, SeaImg, TRUE);//海の表示
	DrawGraph(0, 455, SeaImg, TRUE);
	DrawGraph(480, 455, SeaImg, TRUE);
#ifdef _DEBUG
	DrawString(250, 280, "BACKボタンでステージ遷移", C_RED);
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
	/*WaitTime++;*/
}
// ポーズ画面
void GameMain::Pause()
{
}