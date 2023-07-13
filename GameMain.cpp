#include "DxLib.h"
#include "GameMain.h"
#include "Common.h"
#include "stdio.h"
#include "Player.h"
#include"bubble.h"
#include"Thunderbolt.h"
#include"Fish.h"
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
	BUBBLE.UpdateBubble();
	enemy.Update();
	fish.Update();

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
	thunder.Draw();
	BUBBLE.GenerationBubble();
	player.Draw();
	enemy.Draw();
	fish.Draw();

	/*ステージ遷移*/
	switch (gStageState)
	{
	case 1:
		DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(0, 420, gGameImg[8], TRUE);
		DrawGraph(460, 420, gGameImg[10], TRUE);
		DrawGraph(180, 250, gGameImg[0], TRUE);
		DrawGraph(150, 450, gGameImg[12], TRUE);
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		break;
	case 2:
		DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(180, 250, gGameImg[0], TRUE);
		DrawGraph(50, 100, gGameImg[1], TRUE);
		DrawGraph(450, 100, gGameImg[1], TRUE);
		DrawGraph(0, 420, gGameImg[8], TRUE);
		DrawGraph(460, 420, gGameImg[10], TRUE);
		DrawGraph(150, 450, gGameImg[12], TRUE);
		break;
	case 3:
		DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(250, 350, gGameImg[2], TRUE);
		DrawGraph(150, 250, gGameImg[3], TRUE);
		DrawGraph(330, 200, gGameImg[3], TRUE);
		DrawGraph(500, 100, gGameImg[3], TRUE);
		DrawGraph(200, 100, gGameImg[4], TRUE);
		DrawGraph(0, 420, gGameImg[8], TRUE);
		DrawGraph(460, 420, gGameImg[10], TRUE);
		DrawGraph(150, 450, gGameImg[12], TRUE);
		break;
	case 4:
		DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(120, 280, gGameImg[5], TRUE);
		DrawGraph(250, 300, gGameImg[5], TRUE);
		DrawGraph(280, 150, gGameImg[5], TRUE);
		DrawGraph(350, 370, gGameImg[5], TRUE);
		DrawGraph(460, 260, gGameImg[5], TRUE);
		DrawGraph(0, 420, gGameImg[9], TRUE);
		DrawGraph(460, 420, gGameImg[11], TRUE);
		DrawGraph(150, 450, gGameImg[12], TRUE);
		break;
	case 5:
		DrawFormatString(50, 0, C_RED, "各ステージに対応した数字(1～5)キーを押すことで押したキーのステージへ");
		DrawFormatString(10, 30, C_RED, "6キーで強制終了");
		DrawGraph(200, 50, gGameImg[5], TRUE);
		DrawGraph(230, 380, gGameImg[5], TRUE);
		DrawGraph(350, 380, gGameImg[5], TRUE);
		DrawGraph(230, 120, gGameImg[6], TRUE);
		DrawGraph(120, 200, gGameImg[6], TRUE);
		DrawGraph(480, 150, gGameImg[7], TRUE);
		DrawGraph(0, 420, gGameImg[9], TRUE);
		DrawGraph(460, 420, gGameImg[11], TRUE);
		DrawGraph(150, 450, gGameImg[12], TRUE);
		break;
	default:
		break;
	}
	/*gstage.DrawStage1();*/

#ifdef DEBUG
	//ステージの当たり判定(ステージ１)
	if (gStageState == 1) {
		//左下
		DrawBox(0, 420, 155, 455, C_RED, FALSE);
		DrawLine(0, 420, 155, 455, C_RED, 1);
		//中央
		DrawBox(180, 250, 460, 265, C_RED, FALSE);
		DrawLine(180, 250, 460, 265, C_RED, 1);
		//右下
		DrawBox(460, 420, 620, 455, C_RED, FALSE);
		DrawLine(460, 420, 620, 455, C_RED, 1);
	}
	else if (gStageState == 2) {
		//左下
		DrawBox(0, 420, 155, 455, C_RED, FALSE);
		DrawLine(0, 420, 155, 455, C_RED, 1);
		//中央
		DrawBox(180, 250, 460, 265, C_RED, FALSE);
		DrawLine(180, 250, 460, 265, C_RED, 1);
		//右下
		DrawBox(460, 420, 620, 455, C_RED, FALSE);
		DrawLine(460, 420, 620, 455, C_RED, 1);
		//左上
		DrawBox(50, 100, 170, 115, C_RED, FALSE);
		DrawLine(50, 100, 170, 115, C_RED, FALSE);
		//左下
		DrawBox(445, 100, 570, 115, C_RED, FALSE);
		DrawLine(445, 100, 570, 115, C_RED, FALSE);
	}
#endif // DEBUG

}