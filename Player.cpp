#include "DxLib.h"
#include "Player.h"
#include "InputKey.h"
#include "Common.h"

#define DEBUG
#define DEBUG_Flg

int Player::OldFraem;
int Player::NowFraem;

float Player::PlayerX;
float Player::PlayerY;

Player::Player() 
{
	LoadDivGraph("image/Player/Player_Animation.png", 32, 8, 4, 64, 64, PlayerImg);//�摜�ǂݍ���
	FPSCnt = 0;
	AbtnFPSCnt = 1;
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
	TouchFlg = Not_Touch;
	Abtn = false;
	NowFraem = 0;
	OldFraem = 0;
}

void Player::Update(int Stage) /***�`��ȊO***/
{
	if (Abtn == false) {//A�{�^���������Ă���[AbtnIntervalFream]���t���[������������Abtn���e�`�k�r�d�ɖ߂�����
		Anti_AbtnCnt++;
	}
	else if (Abtn == true) {
		if (Anti_AbtnCnt == AbtnFPSCnt) {
			Abtn = false;
		}
	}

	FPSCnt++;//�t���[���J�E���g
	AbtnFPSCnt++;

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

	//*�t���[���J�E���g���Z�b�g*//
	if (FPSCnt > 60) {//�P�b��������t���[���J�E���g���Z�b�g
		FPSCnt = 0;
	}

	if (Anti_AbtnCnt > AbtnIntervalFream) {
		Anti_AbtnCnt = 0;
	}

	if (AbtnFPSCnt > AbtnIntervalFream) {
		AbtnFPSCnt = 0;
	}
	//**************************//
#ifdef DEBUG
	if (InputKey::GetKeyDown(PAD_INPUT_10) == TRUE) {//�X�y�[�X�L�[���������畗�D�̐����P���炷
		BalloonNum--;
	}
#endif // DEBUG

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
	DrawFormatString(400, 110, C_WHITE, "Angle:%d(1;�� 0:�E)", Angle);			//�����Ă������
	DrawFormatString(400, 130, C_WHITE, "MX:%d MY:%d", MoX, MoY);				//�}�E�X�J�[�\���̍��W
	DrawFormatString(400, 150, C_WHITE, "Stage:%d", NowStage);					//���݂̃X�e�[�W
	DrawFormatString(400, 250, C_WHITE, "Anti_AbtnCnt:%d",Anti_AbtnCnt);		//
	DrawFormatString(400, 270, C_WHITE, "AbtnFPS:%d", AbtnFPSCnt);				//

	//�v���C���[�摜�T�C�Y
	DrawBox((int)PlayerX, (int)PlayerY, (int)PlayerX + 64, (int)PlayerY + 64, C_RED,FALSE);
	DrawLine((int)PlayerX, (int)PlayerY, (int)PlayerX + 64, (int)PlayerY + 64, C_RED, 1);
	//�v���C���[�T�C�Y
	DrawBox((int)PlayerX + 18, (int)PlayerY + 14, (int)PlayerX + 40, (int)PlayerY + 64, C_WHITE, FALSE);
	//�v���C���[�̉���
	DrawLine((int)PlayerX + 14, (int)PlayerY + 64, (int)PlayerX + 40, (int)PlayerY + 64, C_GREEN, 2);
	//���D
	DrawBox((int)PlayerX + 12, (int)PlayerY + 14, (int)PlayerX + 52, (int)PlayerY + 38, C_GREEN,FALSE);
#endif //DEBUG

#ifdef DEBUG_Flg
	DrawFormatString(400, 170, C_WHITE, "FlyBtn:%d(0:off 1:on)", FlyBtnFlg);	//��ԃ{�^���������Ă��邩
	DrawFormatString(400, 190, C_WHITE, "GroundFlg:%d(0:not 1:on)", GroundFlg);	//�n�ʂɐG��Ă��邩
	DrawFormatString(400, 210, C_WHITE, "TouchFlg;%d(0:not 1:on)", TouchFlg);	//�n�ʈȊO�ɐG��Ă���
	DrawFormatString(400, 230, C_WHITE, "Abtn;%d(0:not 1:on)", Abtn);			//A�{�^���������Ă��邩
#endif // DEBUG_Flg

}

void Player::UpdatePlayerX() //*�v���C���[��X���W����*//
{
	if (XStick > 0) {//�E
		PlayerState = P_State_Run;	//�v���C���[�̃X�e�[�^�X�𑖂�ɕύX
		Angle = P_Right;				//�����Ă���������E�ɕύX
		if (GroundFlg == Ground) {//�n��
			VectorX = VectorX + 0.3f;	//���x�{�����x
			if (VectorX >= 3.0f) {		//���x����
				VectorX = 3.0f;
			}
		}
		else if (GroundFlg == Not_Ground) {//��
			if (Abtn == true) {
				VectorX = VectorX + 0.8f;	//���x�{�����x
				if (VectorX >= 3.0f) {		//���x����
					VectorX = 3.0f;
				}
			}
			else {
				VectorX = VectorX + 0.1f;	//���x�{�����x
				if (VectorX >= 3.0f) {		//���x����
					VectorX = 3.0f;
				}
			}
		}
	}
	else if (XStick < 0) {//��
		PlayerState = P_State_Run;	//�v���C���[�̃X�e�[�^�X�𑖂�ɕύX
		Angle = P_Left;				//�����Ă�����������ɕύX
		if (GroundFlg == Ground) {//�n��
			VectorX = VectorX + -0.3f;	//���x�{�����x
			if (VectorX <= -3.0f) {		//���x����
				VectorX = -3.0f;
			}
		}
		else if (GroundFlg == Not_Ground) {//��
			if (Abtn == true) {
				VectorX = VectorX + -0.8f;	//���x�{�����x
				if (VectorX <= -3.0f) {		//���x����
					VectorX = -3.0f;
				}
			}
			else {
				VectorX = VectorX + -0.1f;	//���x�{�����x
				if (VectorX <= -3.0f) {		//���x����
					VectorX = -3.0f;
				}
			}
		}
	}
	else if (XStick == 0) {//�ҋ@
		if (GroundFlg == Ground) {
			VectorX *= 0.89f;			//����
		}
		else if (GroundFlg == Not_Ground) {
			VectorX = VectorX;
		}
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
	if (GroundFlg == Not_Ground) {//�n�ʂ̏�ɗ����Ă��Ȃ���
		/*if (PlayerY < _SCREEN_WIDHT_) {
					
		}*/
		if (BalloonNum == 1) {//���D�P��
			VectorY = VectorY + 0.04f;
			if (VectorY >= 6.0f) {//���x����
				VectorY = 6.0f;
			}
		}
		else if (BalloonNum == 2) {//���D�Q��
			VectorY = VectorY + 0.04f;
			if (VectorY >= 4.0f) {//���x����
				VectorY = 4.0f;
			}
		}
	}
	else if (GroundFlg == Ground) {//�n�ʂ̏�Ȃ痎�����Ȃ��悤�ɂ���
		VectorY = 0;
	}

	if (FlyBtnFlg == ON_FlyBtn || GroundFlg == Not_Ground) {//A�AB�{�^�����n�ʂ̏�ɗ����Ă��Ȃ���
		PlayerState = P_State_Fly;//�v���C���[�̃X�e�[�^�X���ԂɕύX
	}

	if (InputKey::GetKeyDown(PAD_INPUT_A) == TRUE) {//A�{�^������������P�񂾂��H�΂���
		if (Abtn == false) {			//A�{�^���̃C���^�[�o���p�̏���
			FlyBtnFlg = ON_FlyBtn;
			VectorY = VectorY + -0.8f;	//�����x�{�����x�i�㏸�j
			if (VectorY <= -3.0f) {		//���x����
				VectorY = -3.0f;
			}
			Abtn = true;
		}
	}
	else if (InputKey::GetKey(PAD_INPUT_B) == TRUE) {//B�{�^�����������牟���Ă���ԉH�΂���
		FlyBtnFlg = ON_FlyBtn;
		VectorY = VectorY + -0.1f;	//�����x�{�����x�i�㏸�j
		if (VectorY <= -3.0f) {		//���x����
			VectorY = -3.0f;
		}
	}
	else {//A�AB�{�^���������Ă��Ȃ���
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

	if (NowStage == 1) {//�X�e�[�W�P�ł̃X�e�[�W�Ƃ̓����蔻��(�n�ʂɖ��܂違�n�ʂɈ���������o�O����)
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PYL_Right >= S_Sky_Ground_0_YU - PlusPx && PYU_Left <= S_Sky_Ground_0_YL) {//��̑�i���ʁj
				if (PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XL) {//��̑�̍�
					TouchFlg = Touch;
					VectorX *= COR;
					if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						VectorX += 0.9f;
					}
				}
				else if (PXL_Right >= S_Sky_Ground_0_XU - PlusPx && PXL_Right <= S_Sky_Ground_0_XU) {//��̑�̉E
					TouchFlg = Touch;
					VectorX *= COR;
					if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
						VectorX -= 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}

			if (PYU_Left <= S_Sky_Ground_0_YL - PlusPx && PYL_Right >= S_Sky_Ground_0_YU + PlusPx) {//��̑�i���Ӂj
				if (PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {
					TouchFlg = Touch;
					VectorY *= COR;
					if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						VectorY += 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}
			
			if (PYU_Left <= 0) {//��ʏ�̓����蔻��
				VectorY *= COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
		}

		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if(PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU){//�E���̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Sky_Ground_0_YU && PYL_Right <= S_Sky_Ground_0_YU + PlusPx && PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {//�����Ă��钆���̑�i��Ӂj
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 2) {//�X�e�[�W�Q�ł̃X�e�[�W�Ƃ̓����蔻��(������)
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -0.8f;//�����W���H
			}
			else if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -0.8f;
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 3) {//�X�e�[�W�R�ł̃X�e�[�W�Ƃ̓����蔻��
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -0.8f;//�����W���H
			}
			else if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -0.8f;
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 4) {//�X�e�[�W�S�ł̃X�e�[�W�Ƃ̓����蔻��
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -0.8f;//�����W���H
			}
			else if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -0.8f;
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 5) {//�X�e�[�W�T�ł̃X�e�[�W�Ƃ̓����蔻��
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -0.8f;//�����W���H
			}
			else if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -0.8f;
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			GroundFlg = Ground;
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
	if (InputKey::GetKey(PAD_INPUT_B) == TRUE) {
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
	else if (Abtn == TRUE) {
		if (BalloonNum == 2) {
			for (int i = 0; i <= 60; i++) {
				if (i % 8 == 0 || i % 8 == 1) {//�Q�t���[���Ŏ��̉摜
					NowPlayerImg = P_Img_Fly_Ballon_2_0;
				}
				else if (i % 8 == 2 || i % 8 == 3) {
					NowPlayerImg = P_Img_Fly_Ballon_2_1;
				}
				else if (i % 8 == 4 || i % 8 == 5) {
					NowPlayerImg = P_Img_Fly_Ballon_2_2;
				}
				else if (i % 8 == 6 || i % 8 == 7) {
					NowPlayerImg = P_Img_Fly_Ballon_2_3;
				}
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
		NowPlayerImg = P_Img_Dead_0;
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
	static float X = PlayerX;
	return X;
}

float Player::GetPlayerY() {
	static float Y = PlayerY;
	return Y;
}