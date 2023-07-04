#include "Stage.h"
#include"Common.h"
#include "InputKey.h"
#include "StageImg.h"

gStage1::gStage1()
{
	gPlayerImg = LoadGraph("images/ningen.png");
	gFootImg1 = LoadGraph("images/Stage_Footing01.png");     // ステージの足場1
	gFootImg2 = LoadGraph("images/Stage_Footing02.png");     // ステージの足場2
	gFootImg3 = LoadGraph("images/Stage_Footing03.png");     // ステージの足場3
	gFootImg4 = LoadGraph("images/Stage_Footing04.png");     // ステージの足場4
	gFootImg5 = LoadGraph("images/Stage_Footing05.png");     // ステージの足場5
	gFootImg6 = LoadGraph("images/Stage_Footing06.png");     // ステージの足場6
	gFootImg7 = LoadGraph("images/Stage_Footing07.png");     // ステージの足場7
	gFootImg8 = LoadGraph("images/Stage_Footing08.png");     // ステージの足場8
	gLlandImg1 = LoadGraph("images/Stage_Land_Left01.png");  // ステージ左下の足場1
	gLlandImg2 = LoadGraph("images/Stage_Land_Left02.png");  // ステージ左下の足場2
	gRlandImg1 = LoadGraph("images/Stage_Land_Right01.png"); // ステージ右下の足場1
	gRlandImg2 = LoadGraph("images/Stage_Land_Right02.png"); // ステージ右下の足場2
	gSeaImg = LoadGraph("images/Stage_Sea01.png");           // 海の画像
	MousePointx = 0;
	MousePointy = 0;
}

 void gStage1::Update()	
{
	InputKey::Update();

	GetMousePoint(&MousePointx, &MousePointy);


	/*if (CheckHitKey(KEY_INPUT_2)) {
		return 
	}*/
}

void gStage1::Draw() const
{
	gStageImg[0][0] = 100,330;
	DrawFormatString(100, 0, C_RED, "2キーでステージ2へ");
	DrawGraph(100, 330, gPlayerImg, TRUE);
	DrawGraph(150, 450, gSeaImg, FALSE);
	DrawGraph(0, 420, gLlandImg1, FALSE);
	DrawGraph(460, 420, gRlandImg1, FALSE);
	DrawGraph(180, 250, gFootImg1, FALSE);
	DrawFormatString(10, 30, C_RED, "%d %d",MousePointx,MousePointy);
}

//gStage2::gStage2()
//{
//	gPlayerImg = LoadGraph("images/ningen.png");
//	gFootImg1 = LoadGraph("images/Stage_Footing01.png");     // ステージの足場1
//	gFootImg2 = LoadGraph("images/Stage_Footing02.png");     // ステージの足場2
//	gFootImg3 = LoadGraph("images/Stage_Footing03.png");     // ステージの足場3
//	gFootImg4 = LoadGraph("images/Stage_Footing04.png");     // ステージの足場4
//	gFootImg5 = LoadGraph("images/Stage_Footing05.png");     // ステージの足場5
//	gFootImg6 = LoadGraph("images/Stage_Footing06.png");     // ステージの足場6
//	gFootImg7 = LoadGraph("images/Stage_Footing07.png");     // ステージの足場7
//	gFootImg8 = LoadGraph("images/Stage_Footing08.png");     // ステージの足場8
//	gLlandImg1 = LoadGraph("images/Stage_Land_Left01.png");  // ステージ左下の足場1
//	gLlandImg2 = LoadGraph("images/Stage_Land_Left02.png");  // ステージ左下の足場2
//	gRlandImg1 = LoadGraph("images/Stage_Land_Right01.png"); // ステージ右下の足場1
//	gRlandImg2 = LoadGraph("images/Stage_Land_Right02.png"); // ステージ右下の足場2
//	gSeaImg = LoadGraph("images/Stage_Sea01.png");           // 海の画像
//	MousePointx = 0;
//	MousePointy = 0;
//}
//
//AbstractScene* gStage2::Update()
//{
//	InputKey::Update();
//
//	GetMousePoint(&MousePointx, &MousePointy);
//
//	if (CheckHitKey(KEY_INPUT_3)) {
//		return new gStage3();
//	}
//	return this;
//}
//
//void gStage2::Draw() const
//{
//	DrawFormatString(100, 0, C_RED, "3キーでステージ3へ");
//	DrawGraph(100, 330, gPlayerImg, TRUE);
//	DrawGraph(150, 450, gSeaImg, FALSE);
//	DrawGraph(0, 420, gLlandImg1, FALSE);
//	DrawGraph(460, 420, gRlandImg1, FALSE);
//	DrawGraph(180, 250, gFootImg1, FALSE);
//	DrawGraph(50, 100, gFootImg2, FALSE);
//	DrawGraph(450, 100, gFootImg2, FALSE);
//	DrawFormatString(10, 30, C_RED, "%d %d", MousePointx, MousePointy);
//}
//
//gStage3::gStage3()
//{
//	gPlayerImg = LoadGraph("images/ningen.png");
//	gFootImg1 = LoadGraph("images/Stage_Footing01.png");     // ステージの足場1
//	gFootImg2 = LoadGraph("images/Stage_Footing02.png");     // ステージの足場2
//	gFootImg3 = LoadGraph("images/Stage_Footing03.png");     // ステージの足場3
//	gFootImg4 = LoadGraph("images/Stage_Footing04.png");     // ステージの足場4
//	gFootImg5 = LoadGraph("images/Stage_Footing05.png");     // ステージの足場5
//	gFootImg6 = LoadGraph("images/Stage_Footing06.png");     // ステージの足場6
//	gFootImg7 = LoadGraph("images/Stage_Footing07.png");     // ステージの足場7
//	gFootImg8 = LoadGraph("images/Stage_Footing08.png");     // ステージの足場8
//	gLlandImg1 = LoadGraph("images/Stage_Land_Left01.png");  // ステージ左下の足場1
//	gLlandImg2 = LoadGraph("images/Stage_Land_Left02.png");  // ステージ左下の足場2
//	gRlandImg1 = LoadGraph("images/Stage_Land_Right01.png"); // ステージ右下の足場1
//	gRlandImg2 = LoadGraph("images/Stage_Land_Right02.png"); // ステージ右下の足場2
//	gSeaImg = LoadGraph("images/Stage_Sea01.png");           // 海の画像
//	MousePointx = 0;
//	MousePointy = 0;
//}
//
//AbstractScene* gStage3::Update()
//{
//	InputKey::Update();
//
//	GetMousePoint(&MousePointx, &MousePointy);
//
//	if (CheckHitKey(KEY_INPUT_4)) {
//		return new gStage4();
//	}
//	return this;
//}
//
//void gStage3::Draw() const
//{
//	DrawFormatString(100,0, C_RED, "4キーでステージ4へ");
//	DrawGraph(100, 330, gPlayerImg, TRUE);
//	DrawGraph(150, 450, gSeaImg, FALSE);
//	DrawGraph(0, 420, gLlandImg1, FALSE);
//	DrawGraph(460, 420, gRlandImg1, FALSE);
//	DrawGraph(250, 350, gFootImg3, FALSE);
//	DrawGraph(150, 250, gFootImg4, FALSE);
//	DrawGraph(330, 200, gFootImg4, FALSE);
//	DrawGraph(500, 100, gFootImg4, FALSE);
//	DrawGraph(200, 100, gFootImg5, FALSE);
//	DrawFormatString(10, 30, C_RED, "%d %d", MousePointx, MousePointy);
//}
//
//gStage4::gStage4()
//{
//	gPlayerImg = LoadGraph("images/ningen.png");
//	gFootImg1 = LoadGraph("images/Stage_Footing01.png");     // ステージの足場1
//	gFootImg2 = LoadGraph("images/Stage_Footing02.png");     // ステージの足場2
//	gFootImg3 = LoadGraph("images/Stage_Footing03.png");     // ステージの足場3
//	gFootImg4 = LoadGraph("images/Stage_Footing04.png");     // ステージの足場4
//	gFootImg5 = LoadGraph("images/Stage_Footing05.png");     // ステージの足場5
//	gFootImg6 = LoadGraph("images/Stage_Footing06.png");     // ステージの足場6
//	gFootImg7 = LoadGraph("images/Stage_Footing07.png");     // ステージの足場7
//	gFootImg8 = LoadGraph("images/Stage_Footing08.png");     // ステージの足場8
//	gLlandImg1 = LoadGraph("images/Stage_Land_Left01.png");  // ステージ左下の足場1
//	gLlandImg2 = LoadGraph("images/Stage_Land_Left02.png");  // ステージ左下の足場2
//	gRlandImg1 = LoadGraph("images/Stage_Land_Right01.png"); // ステージ右下の足場1
//	gRlandImg2 = LoadGraph("images/Stage_Land_Right02.png"); // ステージ右下の足場2
//	gSeaImg = LoadGraph("images/Stage_Sea01.png");           // 海の画像
//	MousePointx = 0;
//	MousePointy = 0;
//}
//
//AbstractScene* gStage4::Update()
//{
//	InputKey::Update();
//
//	GetMousePoint(&MousePointx, &MousePointy);
//
//	if (CheckHitKey(KEY_INPUT_5)) {
//		return new gStage5();
//	}
//	return this;
//}
//
//void gStage4::Draw() const
//{
//	DrawFormatString(100, 0, C_RED, "5キーでステージ5へ");
//	DrawGraph(100, 330, gPlayerImg, TRUE);
//	DrawGraph(150, 450, gSeaImg, FALSE);
//	DrawGraph(0, 420, gLlandImg2, FALSE);
//	DrawGraph(460, 420, gRlandImg2, FALSE);
//	DrawGraph(120, 280, gFootImg6, FALSE);
//	DrawGraph(250, 300, gFootImg6, FALSE);
//	DrawGraph(280, 150, gFootImg6, FALSE);
//	DrawGraph(350, 370, gFootImg6, FALSE);
//	DrawGraph(460, 260, gFootImg6, FALSE);
//	DrawFormatString(10, 30, C_RED, "%d %d", MousePointx, MousePointy);
//}
//
//gStage5::gStage5()
//{
//	gPlayerImg = LoadGraph("images/ningen.png");
//	gFootImg1 = LoadGraph("images/Stage_Footing01.png");     // ステージの足場1
//	gFootImg2 = LoadGraph("images/Stage_Footing02.png");     // ステージの足場2
//	gFootImg3 = LoadGraph("images/Stage_Footing03.png");     // ステージの足場3
//	gFootImg4 = LoadGraph("images/Stage_Footing04.png");     // ステージの足場4
//	gFootImg5 = LoadGraph("images/Stage_Footing05.png");     // ステージの足場5
//	gFootImg6 = LoadGraph("images/Stage_Footing06.png");     // ステージの足場6
//	gFootImg7 = LoadGraph("images/Stage_Footing07.png");     // ステージの足場7
//	gFootImg8 = LoadGraph("images/Stage_Footing08.png");     // ステージの足場8
//	gLlandImg1 = LoadGraph("images/Stage_Land_Left01.png");  // ステージ左下の足場1
//	gLlandImg2 = LoadGraph("images/Stage_Land_Left02.png");  // ステージ左下の足場2
//	gRlandImg1 = LoadGraph("images/Stage_Land_Right01.png"); // ステージ右下の足場1
//	gRlandImg2 = LoadGraph("images/Stage_Land_Right02.png"); // ステージ右下の足場2
//	gSeaImg = LoadGraph("images/Stage_Sea01.png");           // 海の画像
//	MousePointx = 0;
//	MousePointy = 0;
//}
//
//AbstractScene* gStage5::Update()
//{
//	InputKey::Update();
//
//	GetMousePoint(&MousePointx, &MousePointy);
//
//	if (CheckHitKey(KEY_INPUT_6)) {
//		return nullptr;
//	}
//	return this;
//}
//
//void gStage5::Draw() const
//{
//	DrawFormatString(100, 0, C_RED, "6キーでプログラム終了");
//	DrawGraph(100, 330, gPlayerImg, TRUE);
//	DrawGraph(150, 450, gSeaImg, FALSE);
//	DrawGraph(0, 420, gLlandImg2, FALSE);
//	DrawGraph(460, 420, gRlandImg2, FALSE);
//	DrawGraph(120, 200, gFootImg7, FALSE);
//	DrawGraph(200, 50, gFootImg6, FALSE);
//	DrawGraph(230, 120, gFootImg7, FALSE);
//	DrawGraph(230, 380, gFootImg6, FALSE);
//	DrawGraph(350, 380, gFootImg6, FALSE);
//	DrawGraph(480, 150, gFootImg8, FALSE);
//	DrawFormatString(10, 30, C_RED, "%d %d", MousePointx, MousePointy);
//}
