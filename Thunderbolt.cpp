#include"DxLib.h"
#include"Thunderbolt.h"
#include"Common.h"

#define DEBUG

Thunder::Thunder()
{
	LoadDivGraph("images/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, gThunderImg);	//�摜�ǂݍ���
	LoadDivGraph("images/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, gCloudImg);			//�摜�ǂݍ���

	ThunderX = 100;//���̍��W
	ThunderY = 100;
	CloudX = 100; // �_�̍��W
	CloudY = 100;
	VectorX = 3;
	VectorY = 3;
	ThunderAnimCnt = 0;
	CloudAnimCount = 0;
	gWaitTime = 0;
}

void Thunder::Update(int Stage)
{

	NowStage = Stage;
	ThunderAnimCnt++;
	CloudAnimCount++;
	gWaitTime++;
	//StageCollision();
	if (gWaitTime >= 1500) {
		MoveThunderX();
		ThunderX += VectorX;
		MoveThunderY();
		ThunderY += VectorY;
	}
	ThunderAnim();//�摜����

	if (ThunderAnimCnt >= 8) {
		ThunderAnimCnt = 0;
	}	

	CloudAnim();

	if (CloudAnimCount >= 8) {
		CloudAnimCount = 0;
	}
	
}

void Thunder::Draw() const 
{
	if (gWaitTime >= 1500) { 
		DrawGraph(ThunderX, ThunderY, NowImg, TRUE);
	}
	DrawGraph(CloudX, CloudY, CNowImg, TRUE);
#ifdef DEBUG
	if (gWaitTime >= 1500) {
		DrawBox(ThunderX, ThunderY, ThunderX + 32, ThunderY + 32, C_RED, FALSE);
		DrawBox(ThunderX + 4, ThunderY + 4, ThunderX + 28, ThunderY + 28, C_GREEN, FALSE);
	}
	
#endif // DEBUG

}

void Thunder::MoveThunderX()
{
	if (ThunderX <= 0) {
		VectorX *= -1;
	}
	else if (ThunderX >= _SCREEN_WIDHT_) {
		VectorX *= -1;
	}
}

void Thunder::MoveThunderY()
{
	if (ThunderY <= 0) {
		VectorY *= -1;
	}
	else if (ThunderY >= _SCREEN_HEIGHT_) {
		VectorY *= -1;
	}
}

void Thunder::StageCollision() 
{
	//���̋�`
	int TXU_Left, TYU_Left;//����
	int TXL_Right, TYL_Right;//�E��
	TXU_Left = ThunderX;//����X
	TYU_Left = ThunderX;//����Y
	TXL_Right = ThunderX;//�E��X
	TYL_Right = ThunderX;//�E��Y

	if (NowStage == 1) {//***************�@�P�X�e�[�W�@***************//
		/*******************************************************************************************************************************/
				//���ʂ̓����蔻��//
		/*******************************************************************************************************************************/
		
		if (TXU_Left <= S_Ground_Left_XL && TYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
			VectorX *= -COR;
		}

		if (TXL_Right >= S_Ground_Right_XU && TYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
			VectorX *= -COR;
		}

		if (TYL_Right >= S_Sky_Ground_0_YU + PlusPx && TYU_Left <= S_Sky_Ground_0_YL - PlusPx) {//��̑�i���ʁj
			if (TXU_Left <= S_Sky_Ground_0_XL + PlusPx && TXL_Right >= S_Sky_Ground_0_XL) {//��̑�̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S_Sky_Ground_0_XU - PlusPx && TXL_Right <= S_Sky_Ground_0_XU) {//��̑�̍�
				VectorX *= -COR;
			}
		}
		/*******************************************************************************************************************************/
				//���ӂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (TYU_Left <= S_Sky_Ground_0_YL - PlusPx && TYL_Right >= S_Sky_Ground_0_YL) {//��̑�i���Ӂj
			if (TXU_Left <= S_Sky_Ground_0_XL && TXL_Right >= S_Sky_Ground_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= 0) {//��ʏ�̓����蔻��
			VectorY *= -COR;
		}
		

		if (TYU_Left > Sea_Level) {//�C��

		}
		/*******************************************************************************************************************************/
				//��ӂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (TYL_Right >= S_Ground_Left_YU && TYL_Right <= S_Ground_Left_YU + PlusPx && TXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S_Ground_Right_YU && TYL_Right <= S_Ground_Right_YU + PlusPx && TXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S_Sky_Ground_0_YU && TYL_Right <= S_Sky_Ground_0_YU + PlusPx && TXU_Left <= S_Sky_Ground_0_XL && TXL_Right >= S_Sky_Ground_0_XU) {//�����Ă��钆���̑�i��Ӂj
			VectorY *= -COR;
		}
	}
	else if (NowStage == 2) {//***************�@�Q�X�e�[�W�@***************//
		/*******************************************************************************************************************************/
				//���ʂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (TXU_Left <= S_Ground_Left_XL && TYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
			VectorX *= -COR;
		}

		if (TXL_Right >= S_Ground_Right_XU && TYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
			VectorX *= -COR;
		}

		if (TYL_Right >= S_Sky_Ground_0_YU + PlusPx && TYU_Left <= S_Sky_Ground_0_YL - PlusPx) {//��̑�i���ʁj
			if (TXU_Left <= S_Sky_Ground_0_XL + PlusPx && TXL_Right >= S_Sky_Ground_0_XL) {//��̑�̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S_Sky_Ground_0_XU - PlusPx && TXL_Right <= S_Sky_Ground_0_XU) {//��̑�̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S2_Sky_Ground_0_YU + PlusPx && TYU_Left <= S2_Sky_Ground_0_YL - PlusPx) {//����̑�i���ʁj
			if (TXU_Left <= S2_Sky_Ground_0_XL + PlusPx && TXL_Right >= S2_Sky_Ground_0_XL) {//����̑�̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S2_Sky_Ground_0_XU - PlusPx && TXL_Right <= S2_Sky_Ground_0_XU) {//����̑�̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S2_Sky_Ground_1_YU + PlusPx && TYU_Left <= S2_Sky_Ground_1_YL - PlusPx) {//�E��̑�i���ʁj
			if (TXU_Left <= S2_Sky_Ground_1_XL + PlusPx && TXL_Right >= S2_Sky_Ground_1_XL) {//�E��̑�̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S2_Sky_Ground_1_XU - PlusPx && TXL_Right <= S2_Sky_Ground_1_XU) {//�E��̑�̍�
				VectorX *= -COR;
			}
		}
		/*******************************************************************************************************************************/
				//���ӂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (TYU_Left <= S_Sky_Ground_0_YL - PlusPx && TYL_Right >= S_Sky_Ground_0_YL) {//��̑�i���Ӂj
			if (TXU_Left <= S_Sky_Ground_0_XL && TXL_Right >= S_Sky_Ground_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S2_Sky_Ground_0_YL - PlusPx && TYL_Right >= S2_Sky_Ground_0_YL) {//����̑�i���Ӂj
			if (TXU_Left <= S2_Sky_Ground_0_XL && TXL_Right >= S2_Sky_Ground_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S2_Sky_Ground_1_YL - PlusPx && TYL_Right >= S2_Sky_Ground_1_YL) {//�E��̑�i���Ӂj
			if (TXU_Left <= S2_Sky_Ground_1_XL && TXL_Right >= S2_Sky_Ground_1_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= 0) {//��ʏ�̓����蔻��
			VectorY *= -COR;
		}

		if (TYU_Left > Sea_Level) {//�C��

		}
		
		/*******************************************************************************************************************************/
				//��ӂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (TYL_Right >= S_Ground_Left_YU && TYL_Right <= S_Ground_Left_YU + PlusPx && TXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S_Ground_Right_YU && TYL_Right <= S_Ground_Right_YU + PlusPx && TXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S_Sky_Ground_0_YU && TYL_Right <= S_Sky_Ground_0_YU + PlusPx && TXU_Left <= S_Sky_Ground_0_XL && TXL_Right >= S_Sky_Ground_0_XU) {//�����Ă��钆���̑�i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S2_Sky_Ground_0_YU && TYL_Right <= S2_Sky_Ground_0_YU + PlusPx && TXU_Left <= S2_Sky_Ground_0_XL && TXL_Right >= S2_Sky_Ground_0_XU) {//�����Ă��鍶��̑�i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S2_Sky_Ground_1_YU && TYL_Right <= S2_Sky_Ground_1_YU + PlusPx && TXU_Left <= S2_Sky_Ground_1_XL && TXL_Right >= S2_Sky_Ground_1_XU) {//�����Ă��鍶��̑�i��Ӂj
			VectorY *= -COR;
		}
	}
	else if (NowStage == 3) {//***************�@�R�X�e�[�W�@***************//
		/*******************************************************************************************************************************/
				//���ʂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (TXU_Left <= S_Ground_Left_XL && TYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
			VectorX *= -COR;
		}

		if (TXL_Right >= S_Ground_Right_XU && TYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
			VectorX *= -COR;
		}

		if (TYL_Right >= S3_Sky_SGround_0_YU + PlusPx && TYU_Left <= S3_Sky_SGround_0_YL - PlusPx) {//���ߓ��΁i�n�ʁj
			if (TXU_Left <= S3_Sky_SGround_0_XL + PlusPx && TXL_Right >= S3_Sky_SGround_0_XL) {//���ߓ��΂̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_SGround_0_XU - PlusPx && TXL_Right <= S3_Sky_SGround_0_XU) {//���ߓ��΂̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_SStone_0_YU + PlusPx && TYU_Left <= S3_Sky_SStone_0_YL - PlusPx) {//���ߓ��΁i�΁j
			if (TXU_Left <= S3_Sky_SStone_0_XL + PlusPx && TXL_Right >= S3_Sky_SStone_0_XL) {//���ߓ��΂̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_SStone_0_XU - PlusPx && TXL_Right <= S3_Sky_SStone_0_XU) {//���ߓ��΂̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_SGround_1_YU + PlusPx && TYU_Left <= S3_Sky_SGround_1_YL - PlusPx) {//�����ߓ��΁i�n�ʁj
			if (TXU_Left <= S3_Sky_SGround_1_XL + PlusPx && TXL_Right >= S3_Sky_SGround_1_XL) {//�����ߓ��΂̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_SGround_1_XU - PlusPx && TXL_Right <= S3_Sky_SGround_1_XU) {//�����ߓ��΂̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_SStone_1_YU + PlusPx && TYU_Left <= S3_Sky_SStone_1_YL - PlusPx) {//�����ߓ��΁i�΁j
			if (TXU_Left <= S3_Sky_SStone_1_XL + PlusPx && TXL_Right >= S3_Sky_SStone_1_XL) {//�����ߓ��΂̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_SStone_1_XU - PlusPx && TXL_Right <= S3_Sky_SStone_1_XU) {//�����ߓ��΂̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_SGround_2_YU + PlusPx && TYU_Left <= S3_Sky_SGround_2_YL - PlusPx) {//�E�ߓ��΁i�n�ʁj
			if (TXU_Left <= S3_Sky_SGround_2_XL + PlusPx && TXL_Right >= S3_Sky_SGround_2_XL) {//�E�ߓ��΂̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_SGround_2_XU - PlusPx && TXL_Right <= S3_Sky_SGround_2_XU) {//�E�ߓ��΂̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_SStone_2_YU + PlusPx && TYU_Left <= S3_Sky_SStone_2_YL - PlusPx) {//�E�ߓ��΁i�΁j
			if (TXU_Left <= S3_Sky_SStone_2_XL + PlusPx && TXL_Right >= S3_Sky_SStone_2_XL) {//�E�ߓ��΂̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_SStone_2_XU - PlusPx && TXL_Right <= S3_Sky_SStone_2_XU) {//�E�ߓ��΂̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_Ground_0_YU + PlusPx && TYU_Left <= S3_Sky_Ground_0_YL - PlusPx) {//��󒆏�
			if (TXU_Left <= S3_Sky_Ground_0_XL + PlusPx && TXL_Right >= S3_Sky_Ground_0_XL) {//��󒆏��̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_Ground_0_XU - PlusPx && TXL_Right <= S3_Sky_Ground_0_XU) {//��󒆏��̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S3_Sky_Ground_1_YU + PlusPx && TYU_Left <= S3_Sky_Ground_1_YL - PlusPx) {//���󒆏�
			if (TXU_Left <= S3_Sky_Ground_1_XL + PlusPx && TXL_Right >= S3_Sky_Ground_1_XL) {//���󒆏��̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S3_Sky_Ground_1_XU - PlusPx && TXL_Right <= S3_Sky_Ground_1_XU) {//���󒆏��̍�
				VectorX *= -COR;
			}
		}
		/*******************************************************************************************************************************/
				//���ӂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (TYU_Left <= S3_Sky_SGround_0_YL - PlusPx && TYL_Right >= S3_Sky_SGround_0_YL) {//���ߓ��΁i�n�ʁj�i���Ӂj
			if (TXU_Left <= S3_Sky_SGround_0_XL && TXL_Right >= S3_Sky_SGround_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_SStone_0_YL - PlusPx && TYL_Right >= S3_Sky_SStone_0_YL) {//���ߓ��΁i�΁j�i���Ӂj
			if (TXU_Left <= S3_Sky_SStone_0_XL && TXL_Right >= S3_Sky_SStone_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_SGround_1_YL - PlusPx && TYL_Right >= S3_Sky_SGround_1_YL) {//�����ߓ��΁i�n�ʁj�i���Ӂj
			if (TXU_Left <= S3_Sky_SGround_1_XL && TXL_Right >= S3_Sky_SGround_1_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_SStone_1_YL - PlusPx && TYL_Right >= S3_Sky_SStone_1_YL) {//�����ߓ��΁i�΁j�i���Ӂj
			if (TXU_Left <= S3_Sky_SStone_1_XL && TXL_Right >= S3_Sky_SStone_1_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_SGround_2_YL - PlusPx && TYL_Right >= S3_Sky_SGround_2_YL) {//���ߓ��΁i�n�ʁj�i���Ӂj
			if (TXU_Left <= S3_Sky_SGround_2_XL && TXL_Right >= S3_Sky_SGround_2_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_SStone_2_YL - PlusPx && TYL_Right >= S3_Sky_SStone_2_YL) {//���ߓ��΁i�΁j�i���Ӂj
			if (TXU_Left <= S3_Sky_SStone_2_XL && TXL_Right >= S3_Sky_SStone_2_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_Ground_0_YL - PlusPx && TYL_Right >= S3_Sky_Ground_0_YL) {//��󒆏��i���Ӂj
			if (TXU_Left <= S3_Sky_Ground_0_XL && TXL_Right >= S3_Sky_Ground_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S3_Sky_Ground_1_YL - PlusPx && TYL_Right >= S3_Sky_Ground_1_YL) {//���󒆏��i���Ӂj
			if (TXU_Left <= S3_Sky_Ground_1_XL && TXL_Right >= S3_Sky_Ground_1_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= 0) {//��ʏ�̓����蔻��
			VectorY *= -COR;
		}

		if (TYU_Left > Sea_Level) {//�C��

		}
		/*******************************************************************************************************************************/
				//��ӂ̓����蔻��//
		/*******************************************************************************************************************************/

		if (TYL_Right >= S_Ground_Left_YU && TYL_Right <= S_Ground_Left_YU + PlusPx && TXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S_Ground_Right_YU && TYL_Right <= S_Ground_Right_YU + PlusPx && TXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S3_Sky_SGround_0_YU && TYL_Right <= S3_Sky_SGround_0_YU + PlusPx && TXU_Left <= S3_Sky_SGround_0_XL && TXL_Right >= S3_Sky_SGround_0_XU) {//���ߓ��΁i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S3_Sky_SGround_1_YU && TYL_Right <= S3_Sky_SGround_1_YU + PlusPx && TXU_Left <= S3_Sky_SGround_1_XL && TXL_Right >= S3_Sky_SGround_1_XU) {//�����ߓ��΁i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S3_Sky_SGround_2_YU && TYL_Right <= S3_Sky_SGround_2_YU + PlusPx && TXU_Left <= S3_Sky_SGround_2_XL && TXL_Right >= S3_Sky_SGround_2_XU) {//�E�ߓ��΁i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S3_Sky_Ground_0_YU && TYL_Right <= S3_Sky_Ground_0_YU + PlusPx && TXU_Left <= S3_Sky_Ground_0_XL && TXL_Right >= S3_Sky_Ground_0_XU) {//��󒆏��i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S3_Sky_Ground_1_YU && TYL_Right <= S3_Sky_Ground_1_YU + PlusPx && TXU_Left <= S3_Sky_Ground_1_XL && TXL_Right >= S3_Sky_Ground_1_XU) {//���󒆏��i��Ӂj
			VectorY *= -COR;
		}

	}
	else if (NowStage == 4) {//***************�@�S�X�e�[�W�@***************//
		/*******************************************************************************************************************************/
				//���ʂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (TXU_Left <= S_Ground_Left_XL && TYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
			VectorX *= -COR;
		}

		if (TXL_Right >= S_Ground_Right_XU && TYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
			VectorX *= -COR;
		}
	}

	if (TYL_Right >= S4_Sky_Ground_0_YU + PlusPx && TYU_Left <= S4_Sky_Ground_0_YL - PlusPx) {//�P�ԍ�
		if (TXU_Left <= S4_Sky_Ground_0_XL + PlusPx && TXL_Right >= S4_Sky_Ground_0_XL) {//�P�ԍ��̉E
			VectorX *= -COR;
		}
		else if (TXL_Right >= S4_Sky_Ground_0_XU - PlusPx && TXL_Right <= S4_Sky_Ground_0_XU) {//�P�ԍ��̍�
			VectorX *= -COR;
		}
	}

	if (TYL_Right >= S4_Sky_Ground_1_YU + PlusPx && TYU_Left <= S4_Sky_Ground_1_YL - PlusPx) {//������Q�Ԗ�
		if (TXU_Left <= S4_Sky_Ground_1_XL + PlusPx && TXL_Right >= S4_Sky_Ground_1_XL) {//������Q�Ԗڂ̉E
			VectorX *= -COR;
		}
		else if (TXL_Right >= S4_Sky_Ground_1_XU - PlusPx && TXL_Right <= S4_Sky_Ground_1_XU) {//������Q�Ԗڂ̍�
			VectorX *= -COR;
		}
	}

	if (TYL_Right >= S4_Sky_Ground_2_YU + PlusPx && TYU_Left <= S4_Sky_Ground_2_YL - PlusPx) {//�P�ԏ�
		if (TXU_Left <= S4_Sky_Ground_2_XL + PlusPx && TXL_Right >= S4_Sky_Ground_2_XL) {//�P�ԏ�̉E
			VectorX *= -COR;
		}
		else if (TXL_Right >= S4_Sky_Ground_2_XU - PlusPx && TXL_Right <= S4_Sky_Ground_2_XU) {//�P�ԏ�̍�
			VectorX *= -COR;
		}
	}

	if (TYL_Right >= S4_Sky_Ground_3_YU + PlusPx && TYU_Left <= S4_Sky_Ground_3_YL - PlusPx) {//�P�ԉ�
		if (TXU_Left <= S4_Sky_Ground_3_XL + PlusPx && TXL_Right >= S4_Sky_Ground_3_XL) {//�P�ԉ��̉E
			VectorX *= -COR;
		}
		else if (TXL_Right >= S4_Sky_Ground_3_XU - PlusPx && TXL_Right <= S4_Sky_Ground_3_XU) {//�P�ԉ��̍�
			VectorX *= -COR;
		}
	}

	if (TYL_Right >= S4_Sky_Ground_4_YU + PlusPx && TYU_Left <= S4_Sky_Ground_4_YL - PlusPx) {//�P�ԉE
		if (TXU_Left <= S4_Sky_Ground_4_XL + PlusPx && TXL_Right >= S4_Sky_Ground_4_XL) {//�P�ԉE�̉E
			VectorX *= -COR;
		}
		else if (TXL_Right >= S4_Sky_Ground_4_XU - PlusPx && TXL_Right <= S4_Sky_Ground_4_XU) {//�P�ԉE�̍�
			VectorX *= -COR;
		}
	}
	/*******************************************************************************************************************************/
			//���ӂ̓����蔻��//
	/*******************************************************************************************************************************/
	if (TYU_Left <= S4_Sky_Ground_0_YL - PlusPx && TYL_Right >= S4_Sky_Ground_0_YL) {//�P�ԍ�
		if (TXU_Left <= S4_Sky_Ground_0_XL && TXL_Right >= S4_Sky_Ground_0_XU) {
			VectorY *= -COR;
		}
	}

	if (TYU_Left <= S4_Sky_Ground_1_YL - PlusPx && TYL_Right >= S4_Sky_Ground_1_YL) {//������Q�Ԗ�
		if (TXU_Left <= S4_Sky_Ground_1_XL && TXL_Right >= S4_Sky_Ground_1_XU) {
			VectorY *= -COR;
		}
	}

	if (TYU_Left <= S4_Sky_Ground_2_YL - PlusPx && TYL_Right >= S4_Sky_Ground_2_YL) {//�P�ԏ�
		if (TXU_Left <= S4_Sky_Ground_2_XL && TXL_Right >= S4_Sky_Ground_2_XU) {
			VectorY *= -COR;
		}
	}

	if (TYU_Left <= S4_Sky_Ground_3_YL - PlusPx && TYL_Right >= S4_Sky_Ground_3_YL) {//�P�ԉ�
		if (TXU_Left <= S4_Sky_Ground_3_XL && TXL_Right >= S4_Sky_Ground_3_XU) {
			VectorY *= -COR;
		}
	}

	if (TYU_Left <= S4_Sky_Ground_4_YL - PlusPx && TYL_Right >= S4_Sky_Ground_4_YL) {//�P�ԉE
		if (TXU_Left <= S4_Sky_Ground_4_XL && TXL_Right >= S4_Sky_Ground_4_XU) {
			VectorY *= -COR;
		}
	}

	if (TYU_Left <= 0) {//��ʏ�̓����蔻��
		VectorY *= -COR;
	}

	if (TYU_Left > Sea_Level) {//�C��

	}
	/*******************************************************************************************************************************/
			//��ӂ̓����蔻��//
	/*******************************************************************************************************************************/

	if (TYL_Right >= S_Ground_Left_YU && TYL_Right <= S_Ground_Left_YU + PlusPx && TXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
		VectorY *= -COR;
	}
	else if (TYL_Right >= S_Ground_Right_YU && TYL_Right <= S_Ground_Right_YU + PlusPx && TXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
		VectorY *= -COR;
	}
	else if (TYL_Right >= S4_Sky_Ground_0_YU && TYL_Right <= S4_Sky_Ground_0_YU + PlusPx && TXU_Left <= S4_Sky_Ground_0_XL && TXL_Right >= S4_Sky_Ground_0_XU) {//�P�ԍ��̑�
		VectorY *= -COR;
	}
	else if (TYL_Right >= S4_Sky_Ground_1_YU && TYL_Right <= S4_Sky_Ground_1_YU + PlusPx && TXU_Left <= S4_Sky_Ground_1_XL && TXL_Right >= S4_Sky_Ground_1_XU) {//������Q�Ԗڂ̑�
		VectorY *= -COR;
	}
	else if (TYL_Right >= S4_Sky_Ground_2_YU && TYL_Right <= S4_Sky_Ground_2_YU + PlusPx && TXU_Left <= S4_Sky_Ground_2_XL && TXL_Right >= S4_Sky_Ground_2_XU) {//�P�ԏ�̑�
		VectorY *= -COR;
	}
	else if (TYL_Right >= S4_Sky_Ground_3_YU && TYL_Right <= S4_Sky_Ground_3_YU + PlusPx && TXU_Left <= S4_Sky_Ground_3_XL && TXL_Right >= S4_Sky_Ground_3_XU) {//�P�ԉ��̑�
		VectorY *= -COR;
	}
	else if (TYL_Right >= S4_Sky_Ground_4_YU && TYL_Right <= S4_Sky_Ground_4_YU + PlusPx && TXU_Left <= S4_Sky_Ground_4_XL && TXL_Right >= S4_Sky_Ground_4_XU) {//�P�ԉE�̑�
		VectorY *= -COR;
	}
	else if (NowStage == 5) {//***************�@�T�X�e�[�W�@***************//
		/*******************************************************************************************************************************/
				//���ʂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (TXU_Left <= S_Ground_Left_XL && TYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
			VectorX *= -COR;
		}

		if (TXL_Right >= S_Ground_Right_XU && TYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
			VectorX *= -COR;
		}	

		if (TYL_Right >= S5_Sky_SGround_0_YU + PlusPx && TYU_Left <= S5_Sky_SGround_0_YL - PlusPx) {//���ߓ���
			if (TXU_Left <= S5_Sky_SGround_0_XL + PlusPx && TXL_Right >= S5_Sky_SGround_0_XL) {//���ߓ��΂̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S5_Sky_SGround_0_XU - PlusPx && TXL_Right <= S5_Sky_SGround_0_XU) {//���ߓ��΂̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S5_Sky_SGround_1_YU + PlusPx && TYU_Left <= S5_Sky_SGround_1_YL - PlusPx) {//�����ߓ���
			if (TXU_Left <= S5_Sky_SGround_1_XL + PlusPx && TXL_Right >= S5_Sky_SGround_1_XL) {//�����ߓ��΂̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S5_Sky_SGround_1_XU - PlusPx && TXL_Right <= S5_Sky_SGround_1_XU) {//�����ߓ��΂̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S5_Sky_SGround_2_YU + PlusPx && TYU_Left <= S5_Sky_SGround_2_YL - PlusPx) {//�E�ߓ���
			if (TXU_Left <= S5_Sky_SGround_2_XL + PlusPx && TXL_Right >= S5_Sky_SGround_2_XL) {//�E�ߓ��΂̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S5_Sky_SGround_2_XU - PlusPx && TXL_Right <= S5_Sky_SGround_2_XU) {//�E�ߓ��΂̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S5_Sky_Ground_0_YU + PlusPx && TYU_Left <= S5_Sky_Ground_0_YL - PlusPx) {//�P�ԏ�
			if (TXU_Left <= S5_Sky_Ground_0_XL + PlusPx && TXL_Right >= S5_Sky_Ground_0_XL) {//�P�ԏ�̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S5_Sky_Ground_0_XU - PlusPx && TXL_Right <= S5_Sky_Ground_0_XU) {//�P�ԏ�̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S5_Sky_Ground_1_YU + PlusPx && TYU_Left <= S5_Sky_Ground_1_YL - PlusPx) {//���̉E
			if (TXU_Left <= S5_Sky_Ground_1_XL + PlusPx && TXL_Right >= S5_Sky_Ground_1_XL) {//���̉E�̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S5_Sky_Ground_1_XU - PlusPx && TXL_Right <= S5_Sky_Ground_1_XU) {//���̉E�̍�
				VectorX *= -COR;
			}
		}

		if (TYL_Right >= S5_Sky_Ground_2_YU + PlusPx && TYU_Left <= S5_Sky_Ground_2_YL - PlusPx) {//���̍�
			if (TXU_Left <= S5_Sky_Ground_2_XL + PlusPx && TXL_Right >= S5_Sky_Ground_2_XL) {//���̍��̉E
				VectorX *= -COR;
			}
			else if (TXL_Right >= S5_Sky_Ground_2_XU - PlusPx && TXL_Right <= S5_Sky_Ground_2_XU) {//���̍��̍�
				VectorX *= -COR;
			}
		}
		/*******************************************************************************************************************************/
				//���ӂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (TYU_Left <= S5_Sky_SGround_0_YL - PlusPx && TYL_Right >= S5_Sky_SGround_0_YL) {//�E�ߓ���
			if (TXU_Left <= S5_Sky_SGround_0_XL && TXL_Right >= S5_Sky_SGround_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S5_Sky_SGround_1_YL - PlusPx && TYL_Right >= S5_Sky_SGround_1_YL) {//�����ߓ���
			if (TXU_Left <= S5_Sky_SGround_1_XL && TXL_Right >= S5_Sky_SGround_1_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S5_Sky_SGround_2_YL - PlusPx && TYL_Right >= S5_Sky_SGround_2_YL) {//�E�ߓ���
			if (TXU_Left <= S5_Sky_SGround_2_XL && TXL_Right >= S5_Sky_SGround_2_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S5_Sky_Ground_0_YL - PlusPx && TYL_Right >= S5_Sky_Ground_0_YL) {//�P�ԏ�
			if (TXU_Left <= S5_Sky_Ground_0_XL && TXL_Right >= S5_Sky_Ground_0_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S5_Sky_Ground_1_YL - PlusPx && TYL_Right >= S5_Sky_Ground_1_YL) {//���̉E
			if (TXU_Left <= S5_Sky_Ground_1_XL && TXL_Right >= S5_Sky_Ground_1_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= S5_Sky_Ground_2_YL - PlusPx && TYL_Right >= S5_Sky_Ground_2_YL) {//���̍�
			if (TXU_Left <= S5_Sky_Ground_2_XL && TXL_Right >= S5_Sky_Ground_2_XU) {
				VectorY *= -COR;
			}
		}

		if (TYU_Left <= 0) {//��ʏ�̓����蔻��
			VectorY *= -COR;
		}

		if (TYU_Left > Sea_Level) {//�C��\

		}
		/*******************************************************************************************************************************/
				//��ӂ̓����蔻��//
		/*******************************************************************************************************************************/

		if (TYL_Right >= S_Ground_Left_YU && TYL_Right <= S_Ground_Left_YU + PlusPx && TXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S_Ground_Right_YU && TYL_Right <= S_Ground_Right_YU + PlusPx && TXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			VectorY *= -COR;
		}
		else if (TYL_Right >= S5_Sky_SGround_0_YU && TYL_Right <= S5_Sky_SGround_0_YU + PlusPx && TXU_Left <= S5_Sky_SGround_0_XL && TXL_Right >= S5_Sky_SGround_0_XU) {//���ߓ���
			VectorY *= -COR;
		}
		else if (TYL_Right >= S5_Sky_SGround_1_YU && TYL_Right <= S5_Sky_SGround_1_YU + PlusPx && TXU_Left <= S5_Sky_SGround_1_XL && TXL_Right >= S5_Sky_SGround_1_XU) {//�����ߓ���
			VectorY *= -COR;
		}
		else if (TYL_Right >= S5_Sky_SGround_2_YU && TYL_Right <= S5_Sky_SGround_2_YU + PlusPx && TXU_Left <= S5_Sky_SGround_2_XL && TXL_Right >= S5_Sky_SGround_2_XU) {//�E�ߓ���
			VectorY *= -COR;
		}
		else if (TYL_Right >= S5_Sky_Ground_0_YU && TYL_Right <= S5_Sky_Ground_0_YU + PlusPx && TXU_Left <= S5_Sky_Ground_0_XL && TXL_Right >= S5_Sky_Ground_0_XU) {//��ԏ�
			VectorY *= -COR;
		}
		else if (TYL_Right >= S5_Sky_Ground_1_YU && TYL_Right <= S5_Sky_Ground_1_YU + PlusPx && TXU_Left <= S5_Sky_Ground_1_XL && TXL_Right >= S5_Sky_Ground_1_XU) {//���̍�
			VectorY *= -COR;
		}
		else if (TYL_Right >= S5_Sky_Ground_2_YU && TYL_Right <= S5_Sky_Ground_2_YU + PlusPx && TXU_Left <= S5_Sky_Ground_2_XL && TXL_Right >= S5_Sky_Ground_2_XU) {//���̉E
			VectorY *= -COR;
		}
	}
	
}

void Thunder::ThunderAnim()
{
	if (ThunderAnimCnt >= 0 && ThunderAnimCnt <= 2) {
		NowImg = gThunderImg[0];
	}
	else if (ThunderAnimCnt >= 3 && ThunderAnimCnt <= 5) {
		NowImg = gThunderImg[1];
	}
	else if (ThunderAnimCnt <= 6 && ThunderAnimCnt <= 8) {
		NowImg = gThunderImg[2];
	}
}

void Thunder::CloudAnim()
{

	if (CloudAnimCount >= 0 && CloudAnimCount <= 2) {
		CNowImg = gCloudImg[0];
	}
	else if (gWaitTime >= 1500) {

		if (CloudAnimCount >= 3 && CloudAnimCount <= 5) {
			CNowImg = gCloudImg[1];
		}
		else if (CloudAnimCount <= 6 && CloudAnimCount <= 8) {
			CNowImg = gCloudImg[2];
		}
	}
}
