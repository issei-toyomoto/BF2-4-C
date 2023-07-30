#include"DxLib.h"
#include"Thunderbolt.h"
#include"Common.h"

#define DEBUG

Thunder::Thunder()
{
	LoadDivGraph("images/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, thunder[2].Img);	//�摜�ǂݍ���
	LoadDivGraph("images/Stage_CloudAnimation.png", 3, 3, 1, 32, 32, Cloud[2].Img);			//�摜�ǂݍ���

	for (int i = 2; i < 2; i++) {
		thunder[i].AnimCnt = 0;
		thunder[i].X = 0;
		thunder[i].Y = 0;
		thunder[i].VX = 0;
		thunder[i].VY = 0;
	}

	for (int i = 2; i < 2; i++) {
		Cloud[i].AnimCnt = 0;
		Cloud[i].X = 0;
		Cloud[i].Y = 0;
	}
}

void Thunder::Update(int Stage)
{
	NowStage = Stage;
	thunder[0].AnimCnt++;
	thunder[1].AnimCnt++;

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
}

void Thunder::Draw() const 
{
	DrawGraph(thunder[0].X, thunder[0].Y, NowImg, TRUE);
	DrawGraph(thunder[1].X, thunder[1].Y, NowImg, TRUE);

#ifdef DEBUG
	DrawBox(thunder[0].X, thunder[0].Y, thunder[0].X + 32, thunder[0].Y + 32, C_RED, FALSE);
	DrawBox(thunder[1].X, thunder[1].Y, thunder[1].X + 32, thunder[1].Y + 32, C_RED, FALSE);
	DrawBox(thunder[1].X + 4, thunder[1].Y + 4, thunder[1].X + 28, thunder[1].Y + 28, C_GREEN, FALSE);
	DrawBox(thunder[1].X + 4, thunder[1].Y + 4, thunder[1].X + 28, thunder[1].Y + 28, C_GREEN, FALSE);
#endif // DEBUG

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
		}
	}
}

void Thunder::ThunderAnim()
{
	for (int i = 0; i < 2; i++) {
		if (thunder[i].AnimCnt >= 0 && thunder[i].AnimCnt <= 2) {
			NowImg = thunder[i].Img[0];
		}
		else if (thunder[i].AnimCnt >= 3 && thunder[i].AnimCnt <= 5) {
			NowImg = thunder[i].Img[1];
		}
		else if (thunder[i].AnimCnt <= 6 && thunder[i].AnimCnt <= 8) {
			NowImg = thunder[i].Img[2];
		}
	}
}