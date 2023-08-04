#include"DxLib.h"
#include"Thunderbolt.h"
#include"Common.h"
#include "InputKey.h"

#define DEBUG

Thunder::Thunder()
{
	for (int i = 0; i < 2; i++) {
		LoadDivGraph("images/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, thunder[i].Img);	//�摜�ǂݍ���
		LoadDivGraph("images/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, Cloud[i].Img);				//�摜�ǂݍ���
	}
	
	for (int i = 0; i < 2; i++) {
		thunder[i].AnimCnt = 0;
		thunder[i].X = 0;
		thunder[i].Y = -50;
		thunder[i].VX = 3;
		thunder[i].VY = 3;
		thunder[i].StateFlg = 0;
	}

	for (int i = 0; i < 2; i++) {
		Cloud[i].AnimCnt = 0;
		Cloud[i].C_NowImg = Cloud[i].Img[0];
		Cloud[i].X = 0;
		Cloud[i].Y = 0;
		Cloud[i].WaitTimeFlg = GetRand(2);
		Cloud[i].WaitTimeCnt = 1;
		Cloud[i].WaitTime = 0;
		Cloud[i].StopAnimCnt = Thunder_Hide;
	}

	ThunderNum = 1;

	InitCloud();
}

void Thunder::Update(int i, int Stage)
{
	InputKey::Update();
	NowStage = Stage;//���݂̃X�e�[�W���X�V
	StageCollision(i);

	thunder[i].AnimCnt++;

	Cloud[i].AnimCnt++;
	if (Cloud[i].WaitTime != Cloud[i].WaitTimeCnt) {
		Cloud[i].WaitTimeCnt++;
	}

	CloudPosition();

	if (thunder[i].StateFlg == Thunder_Display) {
		thunder[i].X += thunder[i].VX;//����X���W
		thunder[i].Y += thunder[i].VY;//����Y���W
	}
	
	ThunderAnim(i);//���̉摜����

	if (thunder[i].AnimCnt >= 8) {
		thunder[i].AnimCnt = 0;
	}

	if (Cloud[i].AnimCnt >= 8) {
		Cloud[i].AnimCnt = 0;
	}

	if (Cloud[i].WaitTime == Cloud[i].WaitTimeCnt) {//�ݒ肵���_�̓_�Ń^�C�����J�E���g�Ɠ����Ȃ�
		Cloud[i].StopAnimCnt++;
		thunder[i].StateFlg = Thunder_Display;
		thunder[i].X = Cloud[i].X;
		thunder[i].Y = Cloud[i].Y;
		if (Cloud[i].StopAnimCnt >= 1.5 * 60) {
			Cloud[i].WaitTimeCnt = 0;
			Cloud[i].WaitTime = 8 * 60;//���ڈȍ~�̓_�Ń^�C��
			Cloud[i].StopAnimCnt = 0;
			Cloud[i].C_NowImg = Cloud[0].Img[0];
		}
		else {
			CloudAnim(i);
		}
	}
}

void Thunder::Draw(int i) const 
{
	DrawCloud();
	if (thunder[i].StateFlg == 1) {
		DrawThunder();
	}

#ifdef DEBUG
	DrawBox(thunder[0].X, thunder[0].Y, thunder[0].X + 32, thunder[0].Y + 32, C_RED, FALSE);
	DrawBox(thunder[1].X, thunder[1].Y, thunder[1].X + 32, thunder[1].Y + 32, C_RED, FALSE);
	DrawBox(thunder[0].X + 4, thunder[0].Y + 4, thunder[0].X + 28, thunder[0].Y + 28, C_GREEN, FALSE);
	DrawBox(thunder[1].X + 4, thunder[1].Y + 4, thunder[1].X + 28, thunder[1].Y + 28, C_GREEN, FALSE);

	SetFontSize(16);
	DrawFormatString(300, 30, C_WHITE, "X:%d Y:%d", thunder[0].X, thunder[0].Y);
	DrawFormatString(300, 50, C_WHITE, "VX:%d VY:%d", thunder[0].VX, thunder[0].VY);
	DrawFormatString(300, 70, C_WHITE, "AminCnt:%d", thunder[0].AnimCnt);
	DrawFormatString(300, 90, C_WHITE, "Flg:%d(0:�\���Ȃ� 1:�\�� 2:�v���C���[�ڐG)",thunder[0].StateFlg);

	DrawFormatString(300, 130, C_WHITE, "X:%d Y:%d", Cloud[0].X, Cloud[0].Y);
	DrawFormatString(300, 150, C_WHITE, "WaitTime:%d", Cloud[0].WaitTime);
	DrawFormatString(300, 170, C_WHITE, "WaitTimeCnt:%d", Cloud[0].WaitTimeCnt);
	DrawFormatString(300, 190, C_WHITE, "StopAnimCnt:%d", Cloud[0].StopAnimCnt);
#endif // DEBUG

}

void Thunder::DrawCloud() const
{
	if (NowStage == 1) {
		DrawGraph(Cloud[0].X, Cloud[0].Y, Cloud[0].C_NowImg, TRUE);
	}
}

void Thunder::DrawThunder() const 
{
	if (ThunderNum == 1) {
		DrawGraph(thunder[0].X, thunder[0].Y, thunder[0].T_NowImg, TRUE);
	}
	else if(ThunderNum == 2){
		DrawGraph(thunder[0].X, thunder[0].Y, thunder[0].T_NowImg, TRUE);
		DrawGraph(thunder[1].X, thunder[1].Y, thunder[1].T_NowImg, TRUE);
	}
	
	
}

//�X�e�[�W�Ƃ̓����蔻��
void Thunder::StageCollision(int i)
{
	//���̋�`
	int TXU_Left, TYU_Left;//����
	int TXL_Right, TYL_Right;//�E��
	TXU_Left = thunder[i].X + 4;//����X
	TYU_Left = thunder[i].Y + 4;//����Y
	TXL_Right = thunder[i].X + 28;//�E��X
	TYL_Right = thunder[i].Y + 28;//�E��Y

	if (NowStage == 1) {//***************�@�P�X�e�[�W�@***************//
		//�����̑�
		if (TXU_Left <= S_Ground_Left_XL && TYL_Right >= S_Ground_Left_YU + PlusPx) {//����
			thunder[i].VX *= -Inversion;
		}
		if (TYL_Right >= S_Ground_Left_YU && TYL_Right <= S_Ground_Left_YU + PlusPx && TXU_Left <= S_Ground_Left_XL) {//���
			thunder[i].VY *= -Inversion;
		}

		//�E���̑�
		if (TXL_Right >= S_Ground_Right_XU && TYL_Right >= S_Ground_Right_YU + PlusPx) {//����
			thunder[i].VX *= -Inversion;
		}
		if (TYL_Right >= S_Ground_Right_YU && TYL_Right <= S_Ground_Right_YU + PlusPx && TXL_Right >= S_Ground_Right_XU) {//���
			thunder[i].VY *= -Inversion;
		}

		//�����̑�
		if (TYL_Right >= S_Sky_Ground_0_YU + PlusPx && TYU_Left <= S_Sky_Ground_0_YL - PlusPx) {//����
			if (TXU_Left <= S_Sky_Ground_0_XL + PlusPx && TXL_Right >= S_Sky_Ground_0_XL) {//�E
				thunder[i].VX *= -Inversion;
			}
			else if (TXL_Right >= S_Sky_Ground_0_XU - PlusPx && TXL_Right <= S_Sky_Ground_0_XU) {//��
				thunder[i].VX *= -Inversion;
			}
		}
		if (TYL_Right >= S_Sky_Ground_0_YU && TYL_Right <= S_Sky_Ground_0_YU + PlusPx && TXU_Left <= S_Sky_Ground_0_XL && TXL_Right >= S_Sky_Ground_0_XU) {//���
			thunder[i].VY *= -Inversion;
		}
		if (TYU_Left <= S_Sky_Ground_0_YL - PlusPx && TYL_Right >= S_Sky_Ground_0_YL) {//��̑�i���Ӂj
			if (TXU_Left <= S_Sky_Ground_0_XL && TXL_Right >= S_Sky_Ground_0_XU) {
				thunder[i].VY *= -Inversion;
			}
		}

		//��ʏ�
		if (TYU_Left <= 0) {
			thunder[i].VY *= -Inversion;
		}

		//��ʉ�
		if (TYL_Right >= _SCREEN_HEIGHT_ + 50) {
			thunder[i].StateFlg = Thunder_Hide;
		}

		//��ʉE
		if (TXL_Right >= _SCREEN_WIDHT_) {
			thunder[i].VX *= -Inversion;
		}

		//��ʍ�
		if (TXU_Left <= 0) {
			thunder[i].VX *= -Inversion;
		}
	}
}

//���̃`�J�`�J�A�j���[�V����
void Thunder::ThunderAnim(int i)
{
	if (thunder[i].AnimCnt >= 0 && thunder[i].AnimCnt <= 2) {
		thunder[i].T_NowImg = thunder[i].Img[0];
	}
	else if (thunder[i].AnimCnt >= 3 && thunder[i].AnimCnt <= 5) {
		thunder[i].T_NowImg = thunder[i].Img[1];
	}
	else if (thunder[i].AnimCnt <= 6 && thunder[i].AnimCnt <= 8) {
		thunder[i].T_NowImg = thunder[i].Img[2];
	}
}

//�_�̃`�J�`�J�A�j���[�V����
void Thunder::CloudAnim(int i) 
{
	if (Cloud[i].AnimCnt >= 0 && Cloud[i].AnimCnt <= 2) {
		Cloud[i].C_NowImg = Cloud[i].Img[0];
	}
	else if (Cloud[i].AnimCnt >= 3 && Cloud[i].AnimCnt <= 5) {
		Cloud[i].C_NowImg = Cloud[i].Img[1];
	}
	else if (Cloud[i].AnimCnt >= 6 && Cloud[i].AnimCnt <= 8) {
		Cloud[i].C_NowImg = Cloud[i].Img[2];
	}
}

void Thunder::InitCloud() 
{
	for (int i = 0; i < 2; i++) {
		if (Cloud[i].WaitTimeFlg == 0) {
			Cloud[i].WaitTime = 25 * 60;//�Q�T�b
		}
		else if (Cloud[i].WaitTimeFlg == 1) {
			Cloud[i].WaitTime = 30 * 60;//�R�O�b
		}
		else if (Cloud[i].WaitTimeFlg == 2) {
			Cloud[i].WaitTime = 35 * 60;//�R�T�b
		}
	}
}

void Thunder::CloudPosition() 
{
	if (NowStage == 1) {
		Cloud[0].X = 380;
		Cloud[0].Y = 90;
	}
}