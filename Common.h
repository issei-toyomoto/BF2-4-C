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

//ステージ座標   〇〇(ステージ)_〇〇(足場の種類)_〇〇(左右)_〇〇(場所:UはUpper、LはLower)

/*全ステージ*/
#define S_Ground_Left_XU 0		//左下の台(全ステージ)
#define S_Ground_Left_YU 420
#define S_Ground_Left_XL 155
#define S_Ground_Left_YL 455

#define S_Ground_Right_XU 480	//右下の台(全ステージ)
#define S_Ground_Right_YU 420
#define S_Ground_Right_XL 640
#define S_Ground_Right_YL 455

#define S_Sky_Ground_0_XU 180	//中央の台(１・２ステージ)
#define S_Sky_Ground_0_YU 250
#define S_Sky_Ground_0_XL 460
#define S_Sky_Ground_0_YL 265

/*ステージ2*/
#define S2_Sky_Ground_0_XU 50   // 左上の空中床(2ステージ)
#define S2_Sky_Ground_0_YU 100
#define S2_Sky_Ground_0_XL 170
#define S2_Sky_Ground_0_YL 115

#define S2_Sky_Ground_1_XU 445 // 右上の空中床(2ステージ)
#define S2_Sky_Ground_1_YU 100
#define S2_Sky_Ground_1_XL 570
#define S2_Sky_Ground_1_YL 115

/*ステージ3*/
#define S3_Sky_SGround_0_XU 150 // 左鍾乳石(ステージ3)
#define S3_Sky_SGround_0_YU 250
#define S3_Sky_SGround_0_XL 210
#define S3_Sky_SGround_0_YL 265
#define S3_Sky_SStone_0_XU 170
#define S3_Sky_SStone_0_YU 265
#define S3_Sky_SStone_0_XL 190
#define S3_Sky_SStone_0_YL 315

#define S3_Sky_SGround_1_XU 330 // 中央鍾乳石(ステージ3)
#define S3_Sky_SGround_1_YU 220
#define S3_Sky_SGround_1_XL 390
#define S3_Sky_SGround_1_YL 235
#define S3_Sky_SStone_1_XU 350
#define S3_Sky_SStone_1_YU 235
#define S3_Sky_SStone_1_XL 370
#define S3_Sky_SStone_1_YL 285

#define S3_Sky_SGround_2_XU 500 // 右鍾乳石(ステージ3)
#define S3_Sky_SGround_2_YU 95
#define S3_Sky_SGround_2_XL 560
#define S3_Sky_SGround_2_YL 110
#define S3_Sky_SStone_2_XU 520
#define S3_Sky_SStone_2_YU 115
#define S3_Sky_SStone_2_XL 540
#define S3_Sky_SStone_2_YL 165

#define S3_Sky_Ground_0_XU 200 // 上空中床(ステージ3)
#define S3_Sky_Ground_0_YU 100
#define S3_Sky_Ground_0_XL 240
#define S3_Sky_Ground_0_YL 115

#define S3_Sky_Ground_1_XU 250 // 下空中床(ステージ3)
#define S3_Sky_Ground_1_YU 350
#define S3_Sky_Ground_1_XL 330
#define S3_Sky_Ground_1_YL 365

/*ステージ4*/  // xが小さい順に台の座標を記入
#define S4_Sky_Ground_0_XU 120 // 台1
#define S4_Sky_Ground_0_YU 280 
#define S4_Sky_Ground_0_XL 180
#define S4_Sky_Ground_0_YL 295

#define S4_Sky_Ground_1_XU 250 // 台2
#define S4_Sky_Ground_1_YU 300
#define S4_Sky_Ground_1_XL 310
#define S4_Sky_Ground_1_YL 315

#define S4_Sky_Ground_2_XU 280 // 台3
#define S4_Sky_Ground_2_YU 150
#define S4_Sky_Ground_2_XL 340
#define S4_Sky_Ground_2_YL 165

#define S4_Sky_Ground_3_XU 350 // 台4
#define S4_Sky_Ground_3_YU 370
#define S4_Sky_Ground_3_XL 410
#define S4_Sky_Ground_3_YL 385

#define S4_Sky_Ground_4_XU 460 // 台5
#define S4_Sky_Ground_4_YU 260
#define S4_Sky_Ground_4_XL 520
#define S4_Sky_Ground_4_YL 275

/*ステージ5*/   // xが小さい順に台の座標を記入
#define S5_Sky_SGround_0_XU 120 // 左鍾乳石(ステージ5)
#define S5_Sky_SGround_0_YU 200
#define S5_Sky_SGround_0_XL 140
#define S5_Sky_SGround_0_YL 250

#define S5_Sky_SGround_1_XU 230 // 中央鍾乳石(ステージ5)
#define S5_Sky_SGround_1_YU 120
#define S5_Sky_SGround_1_XL 250
#define S5_Sky_SGround_1_YL 170

#define S5_Sky_SGround_2_XU 480 // 右鍾乳石(ステージ5)
#define S5_Sky_SGround_2_YU 150
#define S5_Sky_SGround_2_XL 500
#define S5_Sky_SGround_2_YL 215

#define S5_Sky_Ground_0_XU 200 // 台1(ステージ5)
#define S5_Sky_Ground_0_YU 50
#define S5_Sky_Ground_0_XL 260
#define S5_Sky_Ground_0_YL 65

#define S5_Sky_Ground_1_XU 230 // 台2(ステージ5)
#define S5_Sky_Ground_1_YU 380
#define S5_Sky_Ground_1_XL 290
#define S5_Sky_Ground_1_YL 395

#define S5_Sky_Ground_2_XU 350 // 台3(ステージ5)
#define S5_Sky_Ground_2_YU 380
#define S5_Sky_Ground_2_XL 410
#define S5_Sky_Ground_2_YL 395