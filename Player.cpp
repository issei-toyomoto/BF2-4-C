#include "DxLib.h"
#include "Player.h"
#include "InputKey.h"
#include "Common.h"

#define DEBUG

Player::Player() 
{
	LoadDivGraph("image/Player/Player_Animation.png", 32, 8, 4, 64, 64, PlayerImg);//�摜�ǂݍ���
	FPSCnt = 0;
	NowPlayerImg = P_Img_Wait_Ballon_2_0;
	BalloonNum = 2;
	PlayerState = P_State_Wait;
	PlayerX = 0;
	PlayerY = 420 - P_Img_Size;
	VectorX = 0;
	VectorY = -1;
	Angle = -1;
	FlyBtnFlg = OFF_FlyBtn;
	GroundFlg = Not_Ground;
}


void Player::Update(int Stage) /***�`��ȊO***/
{
	FPSCnt++;//�t���[���J�E���g

	NowStage = Stage;//���݂̃X�e�[�W

	//�W���C�X�e�b�N���擾
	InputKey::Update();
	GetJoypadAnalogInput(&XStick, &YStick, DX_INPUT_PAD1);
	InputKey::GetJoyStickX(XStick);
	InputKey::GetJoyStickY(YStick);
	//�}�E�X�J�[�\�����擾
	GetMousePoint(&MoX, &MoY);

	UpdateStageCollision();//�v���C���[�ƃX�e�[�W�̓����蔻��

	//X����
	if (FlyBtnFlg == ON_FlyBtn || GroundFlg == Ground) {
		UpdatePlayerX();
	}
	else {
		//��ʒ[��X���W����
		if (PlayerX < -(P_Img_Size)) {//�E�[
			PlayerX = 640 - P_Img_Size;
		}
		else if (PlayerX > 640) {//���[
			PlayerX = 0;
		}

		//�X�e�b�N���X���Ă�������ɃL�����N�^�[�̃A���O����ς��鏈��
		if (XStick > 0) {
			Angle = P_Right;
		}
		else if (XStick < 0) {
			Angle = P_Left;
		}
	}
	PlayerX += VectorX;//X���W�X�V

	//Y����
	UpdatePlayerY();
	PlayerY += VectorY;//Y���W�X�V

	//�摜����
	if (PlayerState == P_State_Wait) {//�ҋ@���
		UpdatePlayerImgWait();
	}
	else if (PlayerState == P_State_Run) {//����
		UpdatePlayerImgRun();
	}
	else if (PlayerState == P_State_Fly) {//���
		UpdatePlayerImgFly();
	}
	else if (PlayerState == P_State_Thunder) {//���ɓ�����
		UpdatePlayerImgThunder();
	}
	else if (PlayerState == P_State_Dead) {//���S���A�j���[�V����
		UpdatePlayerImgDead();
	}


	//�P�b��������t���[���J�E���g���Z�b�g
	if (FPSCnt > 60) {
		FPSCnt = 0;
	}
}

void Player::Draw() const /***�`��***/
{
	//*��ʓ�*//
	if (Angle == P_Left) {//�������Ɍ����Ă��鎞
		DrawGraph((int)PlayerX, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}
	else if (Angle == P_Right) {//�E�����Ɍ����Ă��鎞
		DrawTurnGraph((int)PlayerX, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}
	else {
		DrawGraph((int)PlayerX, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}

	//*��ʊO*//
	if (PlayerX < 0) {
		if (Angle == P_Left) {
			DrawGraph(640 + (int)PlayerX, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
		}
		else if (Angle == P_Right) {
			DrawTurnGraph(640 + (int)PlayerX, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
		}
	}
	else if (PlayerX > 640 - P_Img_Size) {
		if (Angle == P_Left) {
			DrawGraph((int)PlayerX - 640, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
		}
		else if (Angle == P_Right) {
			DrawTurnGraph((int)PlayerX - 640, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
		}
	}

#ifdef DEBUG
	DrawFormatString(400, 10, C_WHITE, "FPS:%d", FPSCnt);						//�t���[���J�E���g
	DrawFormatString(400, 30, C_WHITE, "XStick:%d YStick:%d", XStick, YStick);  //�X�e�b�N�̒l
	DrawFormatString(400, 50, C_WHITE, "Balloon:%d", BalloonNum);				//���D�̐�
	DrawFormatString(400, 70, C_WHITE, "XV:%.2f YV:%.2f", VectorX, VectorY);	//�����x
	DrawFormatString(400, 90, C_WHITE, "X:%.2f Y:%.2f", PlayerX, PlayerY);		//�v���C���[���W
	DrawFormatString(400, 110, C_WHITE, "Angle:%d(0:�E 1;��)", Angle);			//�����Ă������
	DrawFormatString(400, 130, C_WHITE, "MX:%d MY:%d", MoX, MoY);				//�}�E�X�J�[�\���̍��W
	DrawFormatString(400, 150, C_WHITE, "Stage:%d", NowStage);					//���݂̃X�e�[�W
	DrawFormatString(400, 170, C_WHITE, "FlyBtn:%d(0:off 1:on)", FlyBtnFlg);//��ԃ{�^���������Ă��邩�ǂ���
	DrawFormatString(400, 190, C_WHITE, "GroundFlg:%d(0:not 1:on)", GroundFlg);

	//�v���C���[�摜�T�C�Y
	DrawBox((int)PlayerX, (int)PlayerY, (int)PlayerX + 64, (int)PlayerY + 64, C_RED,FALSE);
	DrawLine((int)PlayerX, (int)PlayerY, (int)PlayerX + 64, (int)PlayerY + 64, C_RED, 1);
	//�v���C���[�T�C�Y
	DrawBox((int)PlayerX + 18, (int)PlayerY + 14, (int)PlayerX + 40, (int)PlayerY + 64, C_WHITE, FALSE);
	//���D
	DrawBox((int)PlayerX + 12, (int)PlayerY + 14, (int)PlayerX + 52, (int)PlayerY + 38, C_GREEN,FALSE);
#endif //DEBUG

}

void Player::UpdatePlayerX() //*�v���C���[��X���W����*//
{
	if (XStick > 0) {//�E
		PlayerState = P_State_Run;	//�v���C���[�̃X�e�[�^�X�𑖂�ɕύX
		Angle = P_Right;				//�����Ă���������E�ɕύX
		VectorX = VectorX + 0.3f;	//���x�{�����x
		if (VectorX >= 3.0f) {		//���x����
			VectorX = 3.0f;
		}
	}
	else if (XStick < 0) {//��
		PlayerState = P_State_Run;	//�v���C���[�̃X�e�[�^�X�𑖂�ɕύX
		Angle = P_Left;				//�����Ă�����������ɕύX
		VectorX = VectorX + -0.3f;	//���x�{�����x
		if (VectorX <= -3.0f) {		//���x����
			VectorX = -3.0f;
		}
	}
	else if (XStick == 0) {//�ҋ@
		VectorX *= 0.89f;			//����
		PlayerState = P_State_Wait;	//�v���C���[�̃X�e�[�^�X��ҋ@�ɕύX
	}

	//��ʒ[��X���W����
	if (PlayerX < -(P_Img_Size)) {//�E�[
		PlayerX = 640 - P_Img_Size;
	}
	else if (PlayerX > 640) {//���[
		PlayerX = 0;
	}
}

void Player::UpdatePlayerY() //*�v���C���[��Y���W����*//
{
	//��������
	if (GroundFlg == Not_Ground) {
		if (PlayerY < _SCREEN_WIDHT_) {
			if (BalloonNum == 1) {//���D�P��
				VectorY = VectorY + 0.4f;
				if (VectorY >= 4.0f) {//���x����
					VectorY = 4.0f;
				}
			}
			else if (BalloonNum == 2) {//���D�Q��
				VectorY =VectorY + 0.4f;
				if (VectorY >= 2.0f) {//���x����
					VectorY = 2.0f;
				}
			}
			PlayerState = P_State_Fly;//�v���C���[�̃X�e�[�^�X���ԂɕύX
		}
	}

	if (InputKey::GetKeyDown(PAD_INPUT_A)) {//A�{�^������������P�񂾂��H�΂���(���P�t���[���������͂�����Ă��Ȃ��j
		FlyBtnFlg = ON_FlyBtn;
		if (PlayerY < 0) {//��ʏ�i�������j
			VectorY = VectorY * 0.8f;
		}
		else {
			VectorY = -5.0f;
		}
	}
	else if (InputKey::GetKey(PAD_INPUT_B)) {//B�{�^�����������牟���Ă���ԉH�΂���
		FlyBtnFlg = ON_FlyBtn;
		if (PlayerY < 0) {//��ʏ�i�������j
			VectorY = VectorY * 0.8f;
		}
		else {
			VectorY = -2.0f;
		}
	}
	else {
		FlyBtnFlg = OFF_FlyBtn;
	}
}

void Player::UpdateStageCollision() //*�v���C���[�ƃX�e�[�W�̓����蔻�菈��*//
{
	//�v���C���[�̋�`�̍��W
	int PXU_Left,  PYU_Left;//����
	int PXL_Right, PYL_Right;//�E��
	PXU_Left  = (int)PlayerX + 18;//����X
	PYU_Left  = (int)PlayerY + 14;//����Y
	PXL_Right = (int)PlayerX + 40;//�E��X
	PYL_Right = (int)PlayerY + 64;//�E��Y

	if (NowStage == 1) {//�X�e�[�W�P�ł̃X�e�[�W�Ƃ̓����蔻��(�n�ʂɖ��܂�o�O����)

		//��̑��ʁ�����//
		if (GroundFlg == Not_Ground) {
			if (PXL_Right >= S_Sky_Ground_0_XU && PXU_Left <= S_Sky_Ground_0_XL) {//�����Ă��钆���̑�i���ʁj
				if (PYU_Left <= S_Sky_Ground_0_YL && PYL_Right > S_Sky_Ground_0_YU) {
					VectorX *= -1.0f;
				}
			}

			if (PYL_Right > S_Ground_Left_YU) {//�����̑�i���ʁj
				if (PXU_Left <= S_Ground_Left_XL) {
					VectorX *= -1;
				}
			}

			if (PYL_Right > S_Ground_Right_YU) {
				if (PXL_Right >= S_Ground_Right_XU) {
					VectorY *= -1;
				}
			}
		}

		//��̏��//
		if (PYL_Right >= S_Ground_Left_YU) {//�����̑�ƉE���̑��Y���W�͈ꏏ
			if (PXL_Right >= -P_Img_Size && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
				GroundFlg = Ground;
				VectorY = 0;
			}
			else if (PXL_Right >= S_Ground_Right_XU && PXU_Left <= S_Ground_Right_XL + P_Img_Size) {//�E���̑�i��Ӂj
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else if (PYL_Right >= S_Sky_Ground_0_YU && PYU_Left <= S_Sky_Ground_0_YL) {//�����Ă��钆���̑�i��Ӂj
			if (PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else {
			GroundFlg = Not_Ground;
		}
		
		
	}
	else if (NowStage == 2) {//�X�e�[�W�P�ł̃X�e�[�W�Ƃ̓����蔻��(������)
		if (PYL_Right >= S_Ground_Left_YU) {
			if (PXL_Right >= -P_Img_Size && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
				GroundFlg = Ground;
				VectorY = 0;
			}
			else if (PXL_Right >= S_Ground_Right_XU && PXU_Left <= S_Ground_Right_XL + P_Img_Size) {//�E���̑�i��Ӂj
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else if (PYL_Right >= S_Sky_Ground_0_YU && PYU_Left <= S_Sky_Ground_0_YL) {//�����Ă��钆���̑�i��Ӂj
			if (PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 3) {//�X�e�[�W�P�ł̃X�e�[�W�Ƃ̓����蔻��
		if (PYL_Right >= S_Ground_Left_YU) {
			if (PXL_Right >= -P_Img_Size && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
				GroundFlg = Ground;
				VectorY = 0;
			}
			else if (PXL_Right >= S_Ground_Right_XU && PXU_Left <= S_Ground_Right_XL + P_Img_Size) {//�E���̑�i��Ӂj
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 4) {//�X�e�[�W�P�ł̃X�e�[�W�Ƃ̓����蔻��
		if (PYL_Right >= S_Ground_Left_YU) {
			if (PXL_Right >= -P_Img_Size && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
				GroundFlg = Ground;
				VectorY = 0;
			}
			else if (PXL_Right >= S_Ground_Right_XU && PXU_Left <= S_Ground_Right_XL + P_Img_Size) {//�E���̑�i��Ӂj
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 5) {//�X�e�[�W�P�ł̃X�e�[�W�Ƃ̓����蔻��
		if (PYL_Right >= S_Ground_Left_YU) {
			if (PXL_Right >= -P_Img_Size && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
				GroundFlg = Ground;
				VectorY = 0;
			}
			else if (PXL_Right >= S_Ground_Right_XU && PXU_Left <= S_Ground_Right_XL + P_Img_Size) {//�E���̑�i��Ӂj
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
}

void Player::UpdatePlayerImgRun()//*����A�j���[�V��������*//
{
	//����i���D�P�j
	if (BalloonNum == 1) {
		if (FPSCnt % 15 == 0 || FPSCnt % 15 == 1 || FPSCnt % 15 == 2 || FPSCnt % 15 == 3 || FPSCnt == 4) {//�T�t���[�����Ƃɉ摜�ύX
			NowPlayerImg = P_Img_Run_Ballon_1_1;
		}
		else if (FPSCnt % 15 == 5 || FPSCnt % 15 == 6 || FPSCnt % 15 == 7 || FPSCnt % 15 == 8 || FPSCnt % 15 == 9) {
			NowPlayerImg = P_Img_Run_Ballon_1_0;
		}
		else if (FPSCnt % 15 == 10 || FPSCnt % 15 == 11 || FPSCnt % 15 == 12 || FPSCnt % 15 == 13 || FPSCnt % 15 == 14) {
			NowPlayerImg = P_Img_Run_Ballon_1_2;
		}
	}

	//����i���D�Q�j
	if (BalloonNum == 2) {
		if (FPSCnt % 15 == 0 || FPSCnt % 15 == 1 || FPSCnt % 15 == 2 || FPSCnt % 15 == 3 || FPSCnt == 4) {//�T�t���[�����Ƃɉ摜�ύX
			NowPlayerImg = P_Img_Run_Ballon_2_1;
		}
		else if (FPSCnt % 15 == 5 || FPSCnt % 15 == 6 || FPSCnt % 15 == 7 || FPSCnt % 15 == 8 || FPSCnt % 15 == 9) {
			NowPlayerImg = P_Img_Run_Ballon_2_0;
		}
		else if (FPSCnt % 15 == 10 || FPSCnt % 15 == 11 || FPSCnt % 15 == 12 || FPSCnt % 15 == 13 || FPSCnt % 15 == 14) {
			NowPlayerImg = P_Img_Run_Ballon_2_2;
		}
	}

	//���Ε����Ɍ������Ƃ��̏���
	if (Angle == P_Right && VectorX < 0) {//�E����
		NowPlayerImg = P_Img_RunStop_Ballon_2_3;
	}
	else if (Angle == P_Left && VectorX > 0) {//������
		NowPlayerImg = P_Img_RunStop_Ballon_2_3;
	}
}

void Player::UpdatePlayerImgFly() //*��ԃA�j���[�V��������*//
{
	//���D�P��
	if (InputKey::GetKeyDown(PAD_INPUT_A) || InputKey::GetKey(PAD_INPUT_B)) {
		if (BalloonNum == 1) {
			if (FPSCnt % 8 == 0 || FPSCnt % 8 == 1) {//�Q�t���[���Ŏ��̉摜
				NowPlayerImg = P_Img_Fly_Ballon_1_0;
			}
			else if (FPSCnt % 8 == 2 || FPSCnt % 8 == 3) {
				NowPlayerImg = P_Img_Fly_Ballon_1_1;
			}
			else if (FPSCnt % 8 == 4 || FPSCnt % 8 == 5) {
				NowPlayerImg = P_Img_Fly_Ballon_1_2;
			}
			else if (FPSCnt % 8 == 6 || FPSCnt % 8 == 7) {
				NowPlayerImg = P_Img_Fly_Ballon_1_3;
			}
		}
	}
	else {
		NowPlayerImg = P_Img_FlyStop_Ballon_1_4;
	}
	
	//���D�Q��
	if (InputKey::GetKeyDown(PAD_INPUT_A) || InputKey::GetKey(PAD_INPUT_B)) {
		if (BalloonNum == 2) {
			if (FPSCnt % 8 == 0 || FPSCnt % 8 == 1) {//�Q�t���[���Ŏ��̉摜
				NowPlayerImg = P_Img_Fly_Ballon_2_0;
			}
			else if (FPSCnt % 8 == 2 || FPSCnt % 8 == 3) {
				NowPlayerImg = P_Img_Fly_Ballon_2_1;
			}
			else if (FPSCnt % 8 == 4 || FPSCnt % 8 == 5) {
				NowPlayerImg = P_Img_Fly_Ballon_2_2;
			}
			else if (FPSCnt % 8 == 6 || FPSCnt % 8 == 7) {
				NowPlayerImg = P_Img_Fly_Ballon_2_3;
			}
		}
	}
	else {
		NowPlayerImg = P_Img_FlyStop_Ballon_2_4;
	}
}

void Player::UpdatePlayerImgWait() //*�ҋ@�A�j���[�V��������*//
{
	//�ҋ@��ԁi���D�P�j
	if (BalloonNum == 1) {
		if (FPSCnt >= 0 && FPSCnt <= 20) {
			NowPlayerImg = P_Img_Wait_Ballon_1_0;
		}
		else if (FPSCnt >= 21 && FPSCnt <= 40) {
			NowPlayerImg = P_Img_Wait_Ballon_1_1;
		}
		else if (FPSCnt >= 41 && FPSCnt <= 60) {
			NowPlayerImg = P_Img_Wait_Ballon_1_2;
		}
	}

	//�ҋ@��ԁi���D�Q�j
	if (BalloonNum == 2) {
		if (FPSCnt > 0 && FPSCnt < 20) {
			NowPlayerImg = P_Img_Wait_Ballon_2_0;
		}
		else if (FPSCnt > 21 && FPSCnt < 40) {
			NowPlayerImg = P_Img_Wait_Ballon_2_1;
		}
		else if (FPSCnt > 41 && FPSCnt < 60) {
			NowPlayerImg = P_Img_Wait_Ballon_2_2;
		}
	}
}

void Player::UpdatePlayerImgThunder() //*���ɓ�����A�j���[�V��������*//
{
	if (FPSCnt % 6 == 0 || FPSCnt % 6 == 1 || FPSCnt % 6 == 2) {//�Q�t���[���ŉ摜�ύX
		NowPlayerImg = P_Img_Thunder_0;
	}
	else if (FPSCnt % 6 == 3 || FPSCnt % 6 == 4 || FPSCnt % 6 ==5) {
		NowPlayerImg = P_Img_Thunder_1;
	}
}

void Player::UpdatePlayerImgDead() //*���S���A�j���[�V��������*//
{
	if (FPSCnt % 9 == 0 || FPSCnt % 9 == 1 || FPSCnt % 9 == 2) {//�Q�t���[���ŉ摜�ύX
		NowPlayerImg = P_Img_Dead_0;
	}
	else if (FPSCnt % 9 == 3 || FPSCnt % 9 == 4 || FPSCnt % 9 == 5) {
		NowPlayerImg = P_Img_Dead_1;
	}
	else if (FPSCnt % 9 == 6 || FPSCnt % 9 == 7 || FPSCnt % 9 == 8) {
		NowPlayerImg = P_Img_Dead_2;
	}
}

float Player::GetPlayerX (){
	float X = PlayerX;
	return X;
}

float Player::GetPlayerY() {
	float Y = PlayerY;
	return Y;
}