#include "DxLib.h"
#include "GameMain.h"
#include "Common.h"
#include "stdio.h"

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


#ifdef DEBUG
	if (CheckHitKey(KEY_INPUT_9)) {
		return nullptr;
	}
#endif // DEBUG
	return this;
}

void GameMain::Draw()const 
{


#ifdef DEBUG
	DrawFormatString(10, 30, C_RED, "9キーでプログラム終了");
#endif // DEBUG
}