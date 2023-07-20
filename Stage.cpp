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

void gStage::Draw() const
{

}

void gStage::Update()
{
	InputKey::Update();

	GetMousePoint(&MousePointx, &MousePointy);

}

//*�֐��̒�`���Ȃ��R���p�C���G���[���͂��Ă����̂Œǉ����܂����B�i�L���ꐬ�j*//
void gStage::DrawStage1() const
{

}

void gStage::DrawStage2() const
{

}

void gStage::DrawStage3() const
{

}

void gStage::DrawStage4() const
{

}

void gStage::DrawStage5() const
{

}