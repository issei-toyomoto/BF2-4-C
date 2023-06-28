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

#ifdef DEBUG
	if (CheckHitKey(KEY_INPUT_9)) {
		return new gStage1();
	}
#endif // DEBUG
	return this;
}

void GameMain::Draw()const 
{
	player.Draw();
	BUBBLE.GenerationBubble();

#ifdef DEBUG
	DrawFormatString(10, 30, C_RED, "9キーでプログラム終了");
#endif // DEBUG
}