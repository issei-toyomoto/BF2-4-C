#include "DxLib.h"
#include "GameMain.h"
#include "Common.h"
#include "stdio.h"

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

	if (CheckHitKey(KEY_INPUT_9)) {
		return nullptr;
	}
	return this;
}

void GameMain::Draw()const 
{
	DrawFormatString(10, 30, C_RED, "9キーでプログラム終了");
}