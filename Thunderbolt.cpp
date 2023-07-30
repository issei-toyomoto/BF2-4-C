#include"DxLib.h"
#include"Thunderbolt.h"
#include"Common.h"
#include "InputKey.h"

#define DEBUG

Thunder::Thunder()
{
	for (int i = 0; i < 2; i++) {
		LoadDivGraph("images/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, thunder[i].Img);	//�摜�ǂݍ���
		LoadDivGraph("images/Stage_CloudAnimation.png", 3, 3, 1, 32, 32, Cloud[i].Img);				//�摜�ǂݍ���
	}
	
	for (int i = 0; i < 2; i++) {
		thunder[i].AnimCnt = 0;
		thunder[i].X = 0;
		thunder[i].Y = 0;
		thunder[i].VX = 3;
		thunder[i].VY = 3;
	}

	for (int i = 0; i < 2; i++) {
		Cloud[i].AnimCnt = 0;
		Cloud[i].X = 0;
		Cloud[i].Y = 0;
	}
}

void Thunder::Update(int Stage)
{
	InputKey::Update();

	NowStage = Stage;
	thunder[0].AnimCnt++;
	thunder[1].AnimCnt++;

	Cloud[0].AnimCnt++;

	StageCollision();

	thunder[0].X += thunder[0].VX;	
	thunder[1].X += thunder[1].VX;

	thunder[0].Y += thunder[0].VY;
	thunder[1].Y += thunder[1].VY;

	ThunderAnim();//�摜����

	if (thunder[0].AnimCnt >= 8) {
		thunder[0].AnimCnt = 0;
	}
	if (thunder[1].AnimCnt >= 8) {
		thunder[1].AnimCnt = 0;
	}

	if (Cloud[0].AnimCnt >= 8) {
		Cloud[0].AnimCnt = 0;
	}
}

void Thunder::Draw() const 
{
	DrawCloud();
	DrawThunder();

#ifdef DEBUG
	DrawBox(thunder[0].X, thunder[0].Y, thunder[0].X + 32, thunder[0].Y + 32, C_RED, FALSE);
	DrawBox(thunder[1].X, thunder[1].Y, thunder[1].X + 32, thunder[1].Y + 32, C_RED, FALSE);
	DrawBox(thunder[1].X + 4, thunder[1].Y + 4, thunder[1].X + 28, thunder[1].Y + 28, C_GREEN, FALSE);
	DrawBox(thunder[1].X + 4, thunder[1].Y + 4, thunder[1].X + 28, thunder[1].Y + 28, C_GREEN, FALSE);

	SetFontSize(16);
	int i = 0;
	if (InputKey::GetKeyDown(PAD_INPUT_1) == TRUE) {
		i++;
	}
	DrawFormatString(400, 10, C_WHITE, "i:%d", i);
	DrawFormatString(400, 30, C_WHITE, "X:%d Y:%d", thunder[i].X, thunder[i].Y);
	DrawFormatString(400, 50, C_WHITE, "VX:%d VY:%d", thunder[i].VX, thunder[i].VY);
	DrawFormatString(400, 70, C_WHITE, "AminCnt:%d", thunder[i].AnimCnt);
#endif // DEBUG

}

void Thunder::DrawCloud() const
{
	if (NowStage == 1) {
		DrawGraph(Cloud[0].X, Cloud[0].Y, C_NowImg, TRUE);
	}
}

void Thunder::DrawThunder() const 
{
	DrawGraph(thunder[0].X, thunder[0].Y, T_NowImg, TRUE);
	DrawGraph(thunder[1].X, thunder[1].Y, T_NowImg, TRUE);
}

void Thunder::StageCollision()
{
	for (int i = 0; i < 2; i++) {
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
			if (TYL_Right >= _SCREEN_HEIGHT_) {
				thunder[i].VY *= -Inversion;
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
}

void Thunder::ThunderAnim()
{
	for (int i = 0; i < 2; i++) {
		if (thunder[i].AnimCnt >= 0 && thunder[i].AnimCnt <= 2) {
			T_NowImg = thunder[i].Img[0];
		}
		else if (thunder[i].AnimCnt >= 3 && thunder[i].AnimCnt <= 5) {
			T_NowImg = thunder[i].Img[1];
		}
		else if (thunder[i].AnimCnt <= 6 && thunder[i].AnimCnt <= 8) {
			T_NowImg = thunder[i].Img[2];
		}
	}
}

void Thunder::CloudAnim() 
{
	for (int i = 0; i < 2; i++) {
		if (Cloud[i].AnimCnt >= 0 && Cloud[i].AnimCnt <= 2) {
			C_NowImg = Cloud[i].Img[0];
		}
		else if (Cloud[i].AnimCnt >= 3 && Cloud[i].AnimCnt <= 5) {
			C_NowImg = Cloud[i].Img[1];
		}
		else if (Cloud[i].AnimCnt >= 6 && Cloud[i].AnimCnt <= 8) {
			C_NowImg = Cloud[i].Img[2];
		}
	}
}