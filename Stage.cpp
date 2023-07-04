#include "Stage.h"
#include"Common.h"
#include "InputKey.h"
#include "StageImg.h"

gStage::gStage()
{
	gGameImg[0] =  LoadGraph("images/Stage_Footing01.png");      // �X�e�[�W�̑���1
	gGameImg[1] =  LoadGraph("images/Stage_Footing02.png");      // �X�e�[�W�̑���2
	gGameImg[2] =  LoadGraph("images/Stage_Footing03.png");      // �X�e�[�W�̑���3
	gGameImg[3] =  LoadGraph("images/Stage_Footing04.png");      // �X�e�[�W�̑���4
	gGameImg[4] =  LoadGraph("images/Stage_Footing05.png");      // �X�e�[�W�̑���5
	gGameImg[5] =  LoadGraph("images/Stage_Footing06.png");      // �X�e�[�W�̑���6
	gGameImg[6] =  LoadGraph("images/Stage_Footing07.png");      // �X�e�[�W�̑���7
	gGameImg[7] =  LoadGraph("images/Stage_Footing08.png");      // �X�e�[�W�̑���8
	gGameImg[8] =  LoadGraph("images/Stage_Land_Left01.png");    // �X�e�[�W�����̑���1
	gGameImg[9] =  LoadGraph("images/Stage_Land_Left02.png");    // �X�e�[�W�����̑���2
	gGameImg[10] = LoadGraph("images/Stage_Land_Right01.png");   // �X�e�[�W�E���̑���1
	gGameImg[11] = LoadGraph("images/Stage_Land_Right02.png");   // �X�e�[�W�E���̑���2
	gGameImg[12] = LoadGraph("images/Stage_Sea01.png");          // �C�̉摜
	gGameImg[13] = LoadGraph("images/ningen.png");               // �v���C���[�摜
	//gPlayerImg = LoadGraph("images/ningen.png");
	//gFootImg1 = LoadGraph("images/Stage_Footing01.png");     // �X�e�[�W�̑���1
	//gFootImg2 = LoadGraph("images/Stage_Footing02.png");     // �X�e�[�W�̑���2
	//gFootImg3 = LoadGraph("images/Stage_Footing03.png");     // �X�e�[�W�̑���3
	//gFootImg4 = LoadGraph("images/Stage_Footing04.png");     // �X�e�[�W�̑���4
	//gFootImg5 = LoadGraph("images/Stage_Footing05.png");     // �X�e�[�W�̑���5
	//gFootImg6 = LoadGraph("images/Stage_Footing06.png");     // �X�e�[�W�̑���6
	//gFootImg7 = LoadGraph("images/Stage_Footing07.png");     // �X�e�[�W�̑���7
	//gFootImg8 = LoadGraph("images/Stage_Footing08.png");     // �X�e�[�W�̑���8
	//gLlandImg1 = LoadGraph("images/Stage_Land_Left01.png");  // �X�e�[�W�����̑���1
	//gLlandImg2 = LoadGraph("images/Stage_Land_Left02.png");  // �X�e�[�W�����̑���2
	//gRlandImg1 = LoadGraph("images/Stage_Land_Right01.png"); // �X�e�[�W�E���̑���1
	//gRlandImg2 = LoadGraph("images/Stage_Land_Right02.png"); // �X�e�[�W�E���̑���2
	gSeaImg = LoadGraph("images/Stage_Sea01.png");           // �C�̉摜
	MousePointx = 0;
	MousePointy = 0;
	gGameState = 0;
}

void gStage::StageState()
{
	switch (gGameState)
	{
	case 0:
		DrawStage1();
		return;
	case 1:
		DrawStage2();
	case 2:
		DrawStage3();
	case 3:
		DrawStage4();
	case 4:
		DrawStage5();
	default:
		break;
	}
}

 void gStage::Update()	
{
	InputKey::Update();

	GetMousePoint(&MousePointx, &MousePointy);

}

void gStage::DrawStage1() const
{
	DrawFormatString(100, 0, C_RED, "2�L�[�ŃX�e�[�W2��");
	DrawGraph(0, 420, gGameImg[8], FALSE);
	DrawGraph(460, 420, gGameImg[10], FALSE);
	DrawGraph(180, 250, gGameImg[0], FALSE);
	DrawGraph(150, 450, gGameImg[12], FALSE);
	DrawGraph(100, 330, gGameImg[13], TRUE);
	DrawFormatString(10, 30, C_RED, "%d %d",MousePointx,MousePointy);

	if (CheckHitKey(KEY_INPUT_1)) {
		DrawStage2();
	}
	/*else if (CheckHitKey(KEY_INPUT_2)) {
		DrawStage2();
	}
	else if (CheckHitKey(KEY_INPUT_3)) {
		gGameState == 2;
	}
	else if (CheckHitKey(KEY_INPUT_4)) {
		gGameState == 3;
	}
	else if (CheckHitKey(KEY_INPUT_5)) {
		gGameState == 4;
	}*/
}
void gStage::DrawStage2() const
{
	//DrawFormatString(100, 0, C_RED, "3�L�[�ŃX�e�[�W3��");
	///*DrawGraph(100, 330, gPlayerImg, TRUE);*/
	//DrawGraph(150, 450, gSeaImg, FALSE);
	//DrawGraph(0, 420, gLlandImg1, FALSE);
	//DrawGraph(460, 420, gRlandImg1, FALSE);
	//DrawGraph(180, 250, gFootImg1, FALSE);
	//DrawGraph(50, 100, gFootImg2, FALSE);
	//DrawGraph(450, 100, gFootImg2, FALSE);
	//DrawFormatString(10, 30, C_RED, "%d %d", MousePointx, MousePointy);
}

void gStage::DrawStage3() const
{
	/*DrawFormatString(100, 0, C_RED, "4�L�[�ŃX�e�[�W4��");
	DrawGraph(100, 330, gPlayerImg, TRUE);
	DrawGraph(150, 450, gSeaImg, FALSE);
	DrawGraph(0, 420, gLlandImg1, FALSE);
	DrawGraph(460, 420, gRlandImg1, FALSE);
	DrawGraph(250, 350, gFootImg3, FALSE);
	DrawGraph(150, 250, gFootImg4, FALSE);
	DrawGraph(330, 200, gFootImg4, FALSE);
	DrawGraph(500, 100, gFootImg4, FALSE);
	DrawGraph(200, 100, gFootImg5, FALSE);
	DrawFormatString(10, 30, C_RED, "%d %d", MousePointx, MousePointy);*/
}

void gStage::DrawStage4() const
{
	/*DrawFormatString(100, 0, C_RED, "5�L�[�ŃX�e�[�W5��");
	DrawGraph(100, 330, gPlayerImg, TRUE);
	DrawGraph(150, 450, gSeaImg, FALSE);
	DrawGraph(0, 420, gLlandImg2, FALSE);
	DrawGraph(460, 420, gRlandImg2, FALSE);
	DrawGraph(120, 280, gFootImg6, FALSE);
	DrawGraph(250, 300, gFootImg6, FALSE);
	DrawGraph(280, 150, gFootImg6, FALSE);
	DrawGraph(350, 370, gFootImg6, FALSE);
	DrawGraph(460, 260, gFootImg6, FALSE);
	DrawFormatString(10, 30, C_RED, "%d %d", MousePointx, MousePointy);*/
}

void gStage::DrawStage5() const
{
	/*DrawFormatString(100, 0, C_RED, "6�L�[�Ńv���O�����I��");
	DrawGraph(100, 330, gPlayerImg, TRUE);
	DrawGraph(150, 450, gSeaImg, FALSE);
	DrawGraph(0, 420, gLlandImg2, FALSE);
	DrawGraph(460, 420, gRlandImg2, FALSE);
	DrawGraph(120, 200, gFootImg7, FALSE);
	DrawGraph(200, 50, gFootImg6, FALSE);
	DrawGraph(230, 120, gFootImg7, FALSE);
	DrawGraph(230, 380, gFootImg6, FALSE);
	DrawGraph(350, 380, gFootImg6, FALSE);
	DrawGraph(480, 150, gFootImg8, FALSE);
	DrawFormatString(10, 30, C_RED, "%d %d", MousePointx, MousePointy);*/
}


//gStage2::gStage2()
//{
//	gPlayerImg = LoadGraph("images/ningen.png");
//	gFootImg1 = LoadGraph("images/Stage_Footing01.png");     // �X�e�[�W�̑���1
//	gFootImg2 = LoadGraph("images/Stage_Footing02.png");     // �X�e�[�W�̑���2
//	gFootImg3 = LoadGraph("images/Stage_Footing03.png");     // �X�e�[�W�̑���3
//	gFootImg4 = LoadGraph("images/Stage_Footing04.png");     // �X�e�[�W�̑���4
//	gFootImg5 = LoadGraph("images/Stage_Footing05.png");     // �X�e�[�W�̑���5
//	gFootImg6 = LoadGraph("images/Stage_Footing06.png");     // �X�e�[�W�̑���6
//	gFootImg7 = LoadGraph("images/Stage_Footing07.png");     // �X�e�[�W�̑���7
//	gFootImg8 = LoadGraph("images/Stage_Footing08.png");     // �X�e�[�W�̑���8
//	gLlandImg1 = LoadGraph("images/Stage_Land_Left01.png");  // �X�e�[�W�����̑���1
//	gLlandImg2 = LoadGraph("images/Stage_Land_Left02.png");  // �X�e�[�W�����̑���2
//	gRlandImg1 = LoadGraph("images/Stage_Land_Right01.png"); // �X�e�[�W�E���̑���1
//	gRlandImg2 = LoadGraph("images/Stage_Land_Right02.png"); // �X�e�[�W�E���̑���2
//	gSeaImg = LoadGraph("images/Stage_Sea01.png");           // �C�̉摜
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
//	DrawFormatString(100, 0, C_RED, "3�L�[�ŃX�e�[�W3��");
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
//	gFootImg1 = LoadGraph("images/Stage_Footing01.png");     // �X�e�[�W�̑���1
//	gFootImg2 = LoadGraph("images/Stage_Footing02.png");     // �X�e�[�W�̑���2
//	gFootImg3 = LoadGraph("images/Stage_Footing03.png");     // �X�e�[�W�̑���3
//	gFootImg4 = LoadGraph("images/Stage_Footing04.png");     // �X�e�[�W�̑���4
//	gFootImg5 = LoadGraph("images/Stage_Footing05.png");     // �X�e�[�W�̑���5
//	gFootImg6 = LoadGraph("images/Stage_Footing06.png");     // �X�e�[�W�̑���6
//	gFootImg7 = LoadGraph("images/Stage_Footing07.png");     // �X�e�[�W�̑���7
//	gFootImg8 = LoadGraph("images/Stage_Footing08.png");     // �X�e�[�W�̑���8
//	gLlandImg1 = LoadGraph("images/Stage_Land_Left01.png");  // �X�e�[�W�����̑���1
//	gLlandImg2 = LoadGraph("images/Stage_Land_Left02.png");  // �X�e�[�W�����̑���2
//	gRlandImg1 = LoadGraph("images/Stage_Land_Right01.png"); // �X�e�[�W�E���̑���1
//	gRlandImg2 = LoadGraph("images/Stage_Land_Right02.png"); // �X�e�[�W�E���̑���2
//	gSeaImg = LoadGraph("images/Stage_Sea01.png");           // �C�̉摜
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
//	DrawFormatString(100,0, C_RED, "4�L�[�ŃX�e�[�W4��");
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
//	gFootImg1 = LoadGraph("images/Stage_Footing01.png");     // �X�e�[�W�̑���1
//	gFootImg2 = LoadGraph("images/Stage_Footing02.png");     // �X�e�[�W�̑���2
//	gFootImg3 = LoadGraph("images/Stage_Footing03.png");     // �X�e�[�W�̑���3
//	gFootImg4 = LoadGraph("images/Stage_Footing04.png");     // �X�e�[�W�̑���4
//	gFootImg5 = LoadGraph("images/Stage_Footing05.png");     // �X�e�[�W�̑���5
//	gFootImg6 = LoadGraph("images/Stage_Footing06.png");     // �X�e�[�W�̑���6
//	gFootImg7 = LoadGraph("images/Stage_Footing07.png");     // �X�e�[�W�̑���7
//	gFootImg8 = LoadGraph("images/Stage_Footing08.png");     // �X�e�[�W�̑���8
//	gLlandImg1 = LoadGraph("images/Stage_Land_Left01.png");  // �X�e�[�W�����̑���1
//	gLlandImg2 = LoadGraph("images/Stage_Land_Left02.png");  // �X�e�[�W�����̑���2
//	gRlandImg1 = LoadGraph("images/Stage_Land_Right01.png"); // �X�e�[�W�E���̑���1
//	gRlandImg2 = LoadGraph("images/Stage_Land_Right02.png"); // �X�e�[�W�E���̑���2
//	gSeaImg = LoadGraph("images/Stage_Sea01.png");           // �C�̉摜
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
//	DrawFormatString(100, 0, C_RED, "5�L�[�ŃX�e�[�W5��");
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
//	gFootImg1 = LoadGraph("images/Stage_Footing01.png");     // �X�e�[�W�̑���1
//	gFootImg2 = LoadGraph("images/Stage_Footing02.png");     // �X�e�[�W�̑���2
//	gFootImg3 = LoadGraph("images/Stage_Footing03.png");     // �X�e�[�W�̑���3
//	gFootImg4 = LoadGraph("images/Stage_Footing04.png");     // �X�e�[�W�̑���4
//	gFootImg5 = LoadGraph("images/Stage_Footing05.png");     // �X�e�[�W�̑���5
//	gFootImg6 = LoadGraph("images/Stage_Footing06.png");     // �X�e�[�W�̑���6
//	gFootImg7 = LoadGraph("images/Stage_Footing07.png");     // �X�e�[�W�̑���7
//	gFootImg8 = LoadGraph("images/Stage_Footing08.png");     // �X�e�[�W�̑���8
//	gLlandImg1 = LoadGraph("images/Stage_Land_Left01.png");  // �X�e�[�W�����̑���1
//	gLlandImg2 = LoadGraph("images/Stage_Land_Left02.png");  // �X�e�[�W�����̑���2
//	gRlandImg1 = LoadGraph("images/Stage_Land_Right01.png"); // �X�e�[�W�E���̑���1
//	gRlandImg2 = LoadGraph("images/Stage_Land_Right02.png"); // �X�e�[�W�E���̑���2
//	gSeaImg = LoadGraph("images/Stage_Sea01.png");           // �C�̉摜
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
//	DrawFormatString(100, 0, C_RED, "6�L�[�Ńv���O�����I��");
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
