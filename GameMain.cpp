#include "DxLib.h"
#include "GameMain.h"
#include "Common.h"
#include "stdio.h"
#include "Player.h"
#include "Stage.h"

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
	player.Update();
	BUBBLE.UpdateBubble();
	enemy.Update();

#ifdef DEBUG
	
	if (CheckHitKey(KEY_INPUT_1)) {

		return new gStage1();
	}

AbstractScene* GameMain::Update()
{
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
#endif // DEBUG
	return this;
}

void GameMain::Draw()const
{


	player.Draw();
	BUBBLE.GenerationBubble();
	enemy.Draw();
	thunder.Draw();
#ifdef DEBUG
	DrawFormatString(10, 30, C_RED, "1キーでステージ１へ");
#endif // DEBUG	
}

	/*ステージ遷移*/
	switch (gStageState)
	{
	case 1:
		DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(0, 420, gGameImg[8], FALSE);
		DrawGraph(460, 420, gGameImg[10], FALSE);
		DrawGraph(180, 250, gGameImg[0], FALSE);
		DrawGraph(150, 450, gGameImg[12], FALSE);
		DrawGraph(100, 330, gGameImg[13], TRUE);
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		break;
	case 2:
		DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(180, 250, gGameImg[0], FALSE);
		DrawGraph(50, 100, gGameImg[1], FALSE);
		DrawGraph(450, 100, gGameImg[1], FALSE);
		DrawGraph(0, 420, gGameImg[8], FALSE);
		DrawGraph(460, 420, gGameImg[10], FALSE);
		DrawGraph(150, 450, gGameImg[12], FALSE);
		DrawGraph(100, 330, gGameImg[13], TRUE);
		break;
	case 3:
		DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(250, 350, gGameImg[2], FALSE);
		DrawGraph(150, 250, gGameImg[3], FALSE);
		DrawGraph(330, 200, gGameImg[3], FALSE);
		DrawGraph(500, 100, gGameImg[3], FALSE);
		DrawGraph(200, 100, gGameImg[4], FALSE);
		DrawGraph(0, 420, gGameImg[8], FALSE);
		DrawGraph(460, 420, gGameImg[10], FALSE);
		DrawGraph(150, 450, gGameImg[12], FALSE);
		DrawGraph(100, 330, gGameImg[13], TRUE);
		break;
	case 4:
		DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(120, 280, gGameImg[5], FALSE);
		DrawGraph(250, 300, gGameImg[5], FALSE);
		DrawGraph(280, 150, gGameImg[5], FALSE);
		DrawGraph(350, 370, gGameImg[5], FALSE);
		DrawGraph(460, 260, gGameImg[5], FALSE);
		DrawGraph(0, 420, gGameImg[9], FALSE);
		DrawGraph(460, 420, gGameImg[11], FALSE);
		DrawGraph(150, 450, gGameImg[12], FALSE);
		DrawGraph(100, 330, gGameImg[13], TRUE);
		break;
	case 5:
		DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(200, 50, gGameImg[5], FALSE);
		DrawGraph(230, 380, gGameImg[5], FALSE);
		DrawGraph(350, 380, gGameImg[5], FALSE);
		DrawGraph(230, 120, gGameImg[6], FALSE);
		DrawGraph(120, 200, gGameImg[6], FALSE);
		DrawGraph(480, 150, gGameImg[7], FALSE);
		DrawGraph(0, 420, gGameImg[9], FALSE);
		DrawGraph(460, 420, gGameImg[11], FALSE);
		DrawGraph(150, 450, gGameImg[12], FALSE);
		DrawGraph(100, 330, gGameImg[13], TRUE);
		break;
	default:
		break;
	}
	/*gstage.DrawStage1();*/
}