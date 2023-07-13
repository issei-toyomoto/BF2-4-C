#pragma once
#include"DxLib.h"

//画面サイズ
#define _SCREEN_HEIGHT_ 480	//縦
#define _SCREEN_WIDHT_	640	//横

//色
#define C_RED   GetColor(255,0,0)		//赤
#define C_GREEN GetColor(0,255,0)		//緑
#define C_BLUE  GetColor(0,0,255)		//青
#define C_BLACK GetColor(0,0,0)			//黒
#define C_WHITE GetColor(255,255,255)	//白

//ステージ座標
#define S_Ground_Left_XU 0		//左下の台(全ステージ)
#define S_Ground_Left_YU 420
#define S_Ground_Left_XL 155
#define S_Ground_Left_YL 455

#define S_Ground_Right_XU 460	//右下の台(全ステージ)
#define S_Ground_Right_YU 420
#define S_Ground_Right_XL 640
#define S_Ground_Right_YL 455

#define S_Sky_Ground_0_XU 180	//中央の台(１・２ステージ)
#define S_Sky_Ground_0_YU 250
#define S_Sky_Ground_0_XL 460
#define S_Sky_Ground_0_YL 265