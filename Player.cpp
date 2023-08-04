#include "DxLib.h"
#include "Player.h"
#include "InputKey.h"
#include "Common.h"
#include "Fish.h"

//#define DEBUG

float Player::PlayerX;
float Player::PlayerY;

bool Player::Death;

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
	WaitFPSCnt = 0;
	Respawn = true;
	DeathCnt = 0;
	XStick = 0;
	Death = false;
	RespawnCnt = 0;
	Hide = false;

	FishFlg = Fish::P_FishFlg;//Fish.cpp����l���擾
	BalloonCrack = Balloon_NotCrack;
}

void Player::Update(int Stage) /***�`��ȊO***/
{
	NowStage = Stage;//���݂̃X�e�[�W

	if (Abtn == false) {//A�{�^���������Ă���[AbtnIntervalFream]���t���[������������Abtn���e�`�k�r�d�ɖ߂�����
		Anti_AbtnCnt++;
	}
	else if (Abtn == true) {
		if (Anti_AbtnCnt == AbtnFPSCnt) {
			Abtn = false;
		}
	}

	if (BalloonCrack == Balloon_Crack) {//���D���G�Ɋ���ꂽ���̏���
		BalloonNum--;
		BalloonCrack = Balloon_NotCrack;
	}

	FPSCnt++;//�t���[���J�E���g
	AbtnFPSCnt++;
	WaitFPSCnt++;

	if (Respawn == true) {
		DeathCnt++;
		if (XStick != 0 || Abtn == true || InputKey::GetKeyDown(PAD_INPUT_B) == TRUE) {
			Respawn = false;
		}
	}

	if (Death == true) {
		RespawnCnt++;
		Hide = true;
	}

	FishFlg = Fish::P_FishFlg;//���̃t���O�X�V

	if (FishFlg == true) {
		Death = true;
		BalloonNum = 2;
	}

	if (Death == true || OldStage != NowStage) {//�X�e�[�W���؂�ւ������v���C���[�������ʒu�֖߂�
		if (FishFlg == true) {
			Hide = true;
		}
		else {
			SetInitLocation();
		}
		
	}

	//�W���C�X�e�b�N���擾
	InputKey::Update();
	GetJoypadAnalogInput(&XStick, &YStick, DX_INPUT_PAD1);
	InputKey::GetJoyStickX(XStick);
	InputKey::GetJoyStickY(YStick);

	UpdateStageCollision();//�v���C���[�ƃX�e�[�W�̓����蔻��

	//**�ړ������Ǝ��S����**//
	if (Death == false && BalloonNum != 0) {
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
	}
	else if (BalloonNum == 0) {//���D�̐����O�ɂȂ������̏���
		PlayerDeathAnim();
		if (Death == true) {
			BalloonNum = 2;
			Death = false;
		}
	}
	
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

	if (WaitFPSCnt > 120) {
		WaitFPSCnt = 0;
	}

	if (DeathCnt > 600 || Respawn == false) {
		DeathCnt = 0;
		Respawn = false;
	}

	if (RespawnCnt > RespawnTime) {
		RespawnCnt = 0;
		Death = false;
		if (FishFlg == true) {
			Hide = true;
		}
		else if (FishFlg == false) {
			Hide = false;
		}
	}
	//**************************//

	OldStage = NowStage;
#ifdef DEBUG
	if (InputKey::GetKeyDown(PAD_INPUT_10) == TRUE) {//�X�y�[�X�L�[���������畗�D�̐����P���炷
		BalloonCrack = Balloon_Crack;
	}
#endif // DEBUG

}

void Player::Draw() const /***�`��***/
{
	if (Hide == false) {//�v���C���[��\��
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
	}
	else if (Hide == true) {//�v���C���[��\�����Ȃ�
		//�v���C���[���\��
	}
	

#ifdef DEBUG
	DrawFormatString(400, 10, C_WHITE, "FPSCnt:%d", FPSCnt);					//�t���[���J�E���g
	DrawFormatString(400, 30, C_WHITE, "Balloon:%d", BalloonNum);				//���D�̐�
	DrawFormatString(400, 50, C_WHITE, "X:%.2f Y:%.2f", PlayerX, PlayerY);		//�v���C���[���W
	DrawFormatString(400, 70, C_WHITE, "VX:%.2f VY:%.2f", VectorX, VectorY);	//�����x
	DrawFormatString(400, 90, C_WHITE, "Stage:%d", NowStage);					//���݂̃X�e�[�W
	DrawFormatString(400, 110, C_WHITE, "Respawn:%d DeathCnt:%d", Respawn, DeathCnt);
	DrawFormatString(400, 130, C_WHITE, "FishFlg:%d", FishFlg);
	DrawFormatString(400, 150, C_WHITE, "Death:%d RespawnCnt:%d", Death, RespawnCnt);
	DrawFormatString(400, 170, C_WHITE, "Hide:%d", Hide);

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
			VectorX *= 0.96f;
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
			if (VectorY >= 3.0f) {//���x����
				VectorY = 3.0f;
			}
		}
		else if (BalloonNum == 2) {//���D�Q��
			VectorY = VectorY + 0.04f;
			if (VectorY >= 2.1f) {//���x����
				VectorY = 2.1f;
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
			VectorY = VectorY + -0.9f;	//�����x�{�����x�i�㏸�j
			if (VectorY <= -3.0f) {		//���x����
				VectorY = -3.0f;
			}
			Abtn = true;
		}
	}
	else if (InputKey::GetKey(PAD_INPUT_B) == TRUE) {//B�{�^�����������牟���Ă���ԉH�΂���
		FlyBtnFlg = ON_FlyBtn;
		VectorY = VectorY + -0.2f;	//�����x�{�����x�i�㏸�j
		if (VectorY <= -3.0f) {		//���x����
			VectorY = -3.0f;
		}
	}
	else {//A�AB�{�^���������Ă��Ȃ���
		FlyBtnFlg = OFF_FlyBtn;
	}

	
}

//*�v���C���[�ƃX�e�[�W�̓����蔻�菈��*//
void Player::UpdateStageCollision() 
{
	//�v���C���[�̋�`�̍��W
	int PXU_Left,  PYU_Left;//����
	int PXL_Right, PYL_Right;//�E��
	PXU_Left  = (int)PlayerX + 18;//����X
	PYU_Left  = (int)PlayerY + 14;//����Y
	PXL_Right = (int)PlayerX + 40;//�E��X
	PYL_Right = (int)PlayerY + 64;//�E��Y

	if (NowStage == 1) {//***************�@�P�X�e�[�W�@***************//
/*******************************************************************************************************************************/
		//���ʂ̓����蔻��//
/*******************************************************************************************************************************/
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PYL_Right >= S_Sky_Ground_0_YU + PlusPx && PYU_Left <= S_Sky_Ground_0_YL - PlusPx) {//��̑�i���ʁj
				if (PXU_Left <= S_Sky_Ground_0_XL + PlusPx && PXL_Right >= S_Sky_Ground_0_XL) {//��̑�̉E
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						VectorX += 0.9f;
					}
				}
				else if (PXL_Right >= S_Sky_Ground_0_XU - PlusPx && PXL_Right <= S_Sky_Ground_0_XU) {//��̑�̍�
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
						VectorX -= 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}
/*******************************************************************************************************************************/
		//���ӂ̓����蔻��//
/*******************************************************************************************************************************/
			if (PYU_Left <= S_Sky_Ground_0_YL - PlusPx && PYL_Right >= S_Sky_Ground_0_YL) {//��̑�i���Ӂj
				if (PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {
					TouchFlg = Touch;
					VectorY *= -COR;
					if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						VectorY += 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}

			if (PYU_Left <= 0) {//��ʏ�̓����蔻��
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
		}

		if (PYU_Left > Sea_Level) {//�C�ʂ����ɍs���Ə����ʒu�֖߂�����
			Death = true;
			BalloonNum = 2;
		}
/*******************************************************************************************************************************/
		//��ӂ̓����蔻��//
/*******************************************************************************************************************************/
		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Sky_Ground_0_YU && PYL_Right <= S_Sky_Ground_0_YU + PlusPx && PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {//�����Ă��钆���̑�i��Ӂj
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 2) {//***************�@�Q�X�e�[�W�@***************//
/*******************************************************************************************************************************/
		//���ʂ̓����蔻��//
/*******************************************************************************************************************************/
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PYL_Right >= S_Sky_Ground_0_YU + PlusPx && PYU_Left <= S_Sky_Ground_0_YL - PlusPx) {//��̑�i���ʁj
				if (PXU_Left <= S_Sky_Ground_0_XL + PlusPx && PXL_Right >= S_Sky_Ground_0_XL) {//��̑�̉E
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						VectorX += 0.9f;
					}
				}
				else if (PXL_Right >= S_Sky_Ground_0_XU - PlusPx && PXL_Right <= S_Sky_Ground_0_XU) {//��̑�̍�
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
						VectorX -= 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}

			if (PYL_Right >= S2_Sky_Ground_0_YU + PlusPx && PYU_Left <= S2_Sky_Ground_0_YL - PlusPx) {//����̑�i���ʁj
				if (PXU_Left <= S2_Sky_Ground_0_XL + PlusPx && PXL_Right >= S2_Sky_Ground_0_XL) {//����̑�̉E
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						VectorX += 0.9f;
					}
				}
				else if (PXL_Right >= S2_Sky_Ground_0_XU - PlusPx && PXL_Right <= S2_Sky_Ground_0_XU) {//����̑�̍�
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
						VectorX -= 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}

			if (PYL_Right >= S2_Sky_Ground_1_YU + PlusPx && PYU_Left <= S2_Sky_Ground_1_YL - PlusPx) {//�E��̑�i���ʁj
				if (PXU_Left <= S2_Sky_Ground_1_XL + PlusPx && PXL_Right >= S2_Sky_Ground_1_XL) {//�E��̑�̉E
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						VectorX += 0.9f;
					}
				}
				else if (PXL_Right >= S2_Sky_Ground_1_XU - PlusPx && PXL_Right <= S2_Sky_Ground_1_XU) {//�E��̑�̍�
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
						VectorX -= 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}
/*******************************************************************************************************************************/
		//���ӂ̓����蔻��//
/*******************************************************************************************************************************/
			if (PYU_Left <= S_Sky_Ground_0_YL - PlusPx && PYL_Right >= S_Sky_Ground_0_YL) {//��̑�i���Ӂj
				if (PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {
					TouchFlg = Touch;
					VectorY *= -COR;
					if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						VectorY += 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}

			if (PYU_Left <= S2_Sky_Ground_0_YL - PlusPx && PYL_Right >= S2_Sky_Ground_0_YL) {//����̑�i���Ӂj
				if (PXU_Left <= S2_Sky_Ground_0_XL && PXL_Right >= S2_Sky_Ground_0_XU) {
					TouchFlg = Touch;
					VectorY *= -COR;
					if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						VectorY += 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}

			if (PYU_Left <= S2_Sky_Ground_1_YL - PlusPx && PYL_Right >= S2_Sky_Ground_1_YL) {//�E��̑�i���Ӂj
				if (PXU_Left <= S2_Sky_Ground_1_XL && PXL_Right >= S2_Sky_Ground_1_XU) {
					TouchFlg = Touch;
					VectorY *= -COR;
					if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						VectorY += 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}

			if (PYU_Left <= 0) {//��ʏ�̓����蔻��
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}

			if (PYU_Left > Sea_Level) {//�C�ʂ����ɍs���Ə����ʒu�֖߂�����
				Death = true;
				BalloonNum = 2;
			}
		}
/*******************************************************************************************************************************/
		//��ӂ̓����蔻��//
/*******************************************************************************************************************************/
		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Sky_Ground_0_YU && PYL_Right <= S_Sky_Ground_0_YU + PlusPx && PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {//�����Ă��钆���̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S2_Sky_Ground_0_YU && PYL_Right <= S2_Sky_Ground_0_YU + PlusPx && PXU_Left <= S2_Sky_Ground_0_XL && PXL_Right >= S2_Sky_Ground_0_XU) {//�����Ă��鍶��̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S2_Sky_Ground_1_YU && PYL_Right <= S2_Sky_Ground_1_YU + PlusPx && PXU_Left <= S2_Sky_Ground_1_XL && PXL_Right >= S2_Sky_Ground_1_XU) {//�����Ă��鍶��̑�i��Ӂj
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 3) {//***************�@�R�X�e�[�W�@***************//
/*******************************************************************************************************************************/
		//���ʂ̓����蔻��//
/*******************************************************************************************************************************/
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_SGround_0_YU + PlusPx && PYU_Left <= S3_Sky_SGround_0_YL - PlusPx) {//���ߓ��΁i�n�ʁj
			if (PXU_Left <= S3_Sky_SGround_0_XL + PlusPx && PXL_Right >= S3_Sky_SGround_0_XL) {//���ߓ��΂̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_SGround_0_XU - PlusPx && PXL_Right <= S3_Sky_SGround_0_XU) {//���ߓ��΂̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_SStone_0_YU + PlusPx && PYU_Left <= S3_Sky_SStone_0_YL - PlusPx) {//���ߓ��΁i�΁j
			if (PXU_Left <= S3_Sky_SStone_0_XL + PlusPx && PXL_Right >= S3_Sky_SStone_0_XL) {//���ߓ��΂̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_SStone_0_XU - PlusPx && PXL_Right <= S3_Sky_SStone_0_XU) {//���ߓ��΂̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_SGround_1_YU + PlusPx && PYU_Left <= S3_Sky_SGround_1_YL - PlusPx) {//�����ߓ��΁i�n�ʁj
			if (PXU_Left <= S3_Sky_SGround_1_XL + PlusPx && PXL_Right >= S3_Sky_SGround_1_XL) {//�����ߓ��΂̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_SGround_1_XU - PlusPx && PXL_Right <= S3_Sky_SGround_1_XU) {//�����ߓ��΂̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_SStone_1_YU + PlusPx && PYU_Left <= S3_Sky_SStone_1_YL - PlusPx) {//�����ߓ��΁i�΁j
			if (PXU_Left <= S3_Sky_SStone_1_XL + PlusPx && PXL_Right >= S3_Sky_SStone_1_XL) {//�����ߓ��΂̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_SStone_1_XU - PlusPx && PXL_Right <= S3_Sky_SStone_1_XU) {//�����ߓ��΂̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_SGround_2_YU + PlusPx && PYU_Left <= S3_Sky_SGround_2_YL - PlusPx) {//�E�ߓ��΁i�n�ʁj
			if (PXU_Left <= S3_Sky_SGround_2_XL + PlusPx && PXL_Right >= S3_Sky_SGround_2_XL) {//�E�ߓ��΂̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_SGround_2_XU - PlusPx && PXL_Right <= S3_Sky_SGround_2_XU) {//�E�ߓ��΂̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_SStone_2_YU + PlusPx && PYU_Left <= S3_Sky_SStone_2_YL - PlusPx) {//�E�ߓ��΁i�΁j
			if (PXU_Left <= S3_Sky_SStone_2_XL + PlusPx && PXL_Right >= S3_Sky_SStone_2_XL) {//�E�ߓ��΂̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_SStone_2_XU - PlusPx && PXL_Right <= S3_Sky_SStone_2_XU) {//�E�ߓ��΂̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_Ground_0_YU + PlusPx && PYU_Left <= S3_Sky_Ground_0_YL - PlusPx) {//��󒆏�
			if (PXU_Left <= S3_Sky_Ground_0_XL + PlusPx && PXL_Right >= S3_Sky_Ground_0_XL) {//��󒆏��̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_Ground_0_XU - PlusPx && PXL_Right <= S3_Sky_Ground_0_XU) {//��󒆏��̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_Ground_1_YU + PlusPx && PYU_Left <= S3_Sky_Ground_1_YL - PlusPx) {//���󒆏�
			if (PXU_Left <= S3_Sky_Ground_1_XL + PlusPx && PXL_Right >= S3_Sky_Ground_1_XL) {//���󒆏��̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_Ground_1_XU - PlusPx && PXL_Right <= S3_Sky_Ground_1_XU) {//���󒆏��̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}
/*******************************************************************************************************************************/
		//���ӂ̓����蔻��//
/*******************************************************************************************************************************/
		if (PYU_Left <= S3_Sky_SGround_0_YL - PlusPx && PYL_Right >= S3_Sky_SGround_0_YL) {//���ߓ��΁i�n�ʁj�i���Ӂj
			if (PXU_Left <= S3_Sky_SGround_0_XL && PXL_Right >= S3_Sky_SGround_0_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_SStone_0_YL - PlusPx && PYL_Right >= S3_Sky_SStone_0_YL) {//���ߓ��΁i�΁j�i���Ӂj
			if (PXU_Left <= S3_Sky_SStone_0_XL && PXL_Right >= S3_Sky_SStone_0_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_SGround_1_YL - PlusPx && PYL_Right >= S3_Sky_SGround_1_YL) {//�����ߓ��΁i�n�ʁj�i���Ӂj
			if (PXU_Left <= S3_Sky_SGround_1_XL && PXL_Right >= S3_Sky_SGround_1_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_SStone_1_YL - PlusPx && PYL_Right >= S3_Sky_SStone_1_YL) {//�����ߓ��΁i�΁j�i���Ӂj
			if (PXU_Left <= S3_Sky_SStone_1_XL && PXL_Right >= S3_Sky_SStone_1_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_SGround_2_YL - PlusPx && PYL_Right >= S3_Sky_SGround_2_YL) {//���ߓ��΁i�n�ʁj�i���Ӂj
			if (PXU_Left <= S3_Sky_SGround_2_XL && PXL_Right >= S3_Sky_SGround_2_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_SStone_2_YL - PlusPx && PYL_Right >= S3_Sky_SStone_2_YL) {//���ߓ��΁i�΁j�i���Ӂj
			if (PXU_Left <= S3_Sky_SStone_2_XL && PXL_Right >= S3_Sky_SStone_2_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_Ground_0_YL - PlusPx && PYL_Right >= S3_Sky_Ground_0_YL) {//��󒆏��i���Ӂj
			if (PXU_Left <= S3_Sky_Ground_0_XL && PXL_Right >= S3_Sky_Ground_0_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_Ground_1_YL - PlusPx && PYL_Right >= S3_Sky_Ground_1_YL) {//���󒆏��i���Ӂj
			if (PXU_Left <= S3_Sky_Ground_1_XL && PXL_Right >= S3_Sky_Ground_1_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= 0) {//��ʏ�̓����蔻��
			VectorY *= -COR;
			if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
				VectorY += 0.9f;
			}
		}

		if (PYU_Left > Sea_Level) {//�C�ʂ����ɍs���Ə����ʒu�֖߂�����
			Death = true;
			BalloonNum = 2;
		}
/*******************************************************************************************************************************/
		//��ӂ̓����蔻��//
/*******************************************************************************************************************************/

		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S3_Sky_SGround_0_YU && PYL_Right <= S3_Sky_SGround_0_YU + PlusPx && PXU_Left <= S3_Sky_SGround_0_XL && PXL_Right >= S3_Sky_SGround_0_XU) {//���ߓ��΁i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S3_Sky_SGround_1_YU && PYL_Right <= S3_Sky_SGround_1_YU + PlusPx && PXU_Left <= S3_Sky_SGround_1_XL && PXL_Right >= S3_Sky_SGround_1_XU) {//�����ߓ��΁i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S3_Sky_SGround_2_YU && PYL_Right <= S3_Sky_SGround_2_YU + PlusPx && PXU_Left <= S3_Sky_SGround_2_XL && PXL_Right >= S3_Sky_SGround_2_XU) {//�E�ߓ��΁i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S3_Sky_Ground_0_YU && PYL_Right <= S3_Sky_Ground_0_YU + PlusPx && PXU_Left <= S3_Sky_Ground_0_XL && PXL_Right >= S3_Sky_Ground_0_XU) {//��󒆏��i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S3_Sky_Ground_1_YU && PYL_Right <= S3_Sky_Ground_1_YU + PlusPx && PXU_Left <= S3_Sky_Ground_1_XL && PXL_Right >= S3_Sky_Ground_1_XU) {//���󒆏��i��Ӂj
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 4) {//***************�@�S�X�e�[�W�@***************//
/*******************************************************************************************************************************/
		//���ʂ̓����蔻��//
/*******************************************************************************************************************************/
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S4_Sky_Ground_0_YU + PlusPx && PYU_Left <= S4_Sky_Ground_0_YL - PlusPx) {//�P�ԍ�
			if (PXU_Left <= S4_Sky_Ground_0_XL + PlusPx && PXL_Right >= S4_Sky_Ground_0_XL) {//�P�ԍ��̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S4_Sky_Ground_0_XU - PlusPx && PXL_Right <= S4_Sky_Ground_0_XU) {//�P�ԍ��̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S4_Sky_Ground_1_YU + PlusPx && PYU_Left <= S4_Sky_Ground_1_YL - PlusPx) {//������Q�Ԗ�
			if (PXU_Left <= S4_Sky_Ground_1_XL + PlusPx && PXL_Right >= S4_Sky_Ground_1_XL) {//������Q�Ԗڂ̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S4_Sky_Ground_1_XU - PlusPx && PXL_Right <= S4_Sky_Ground_1_XU) {//������Q�Ԗڂ̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S4_Sky_Ground_2_YU + PlusPx && PYU_Left <= S4_Sky_Ground_2_YL - PlusPx) {//�P�ԏ�
			if (PXU_Left <= S4_Sky_Ground_2_XL + PlusPx && PXL_Right >= S4_Sky_Ground_2_XL) {//�P�ԏ�̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S4_Sky_Ground_2_XU - PlusPx && PXL_Right <= S4_Sky_Ground_2_XU) {//�P�ԏ�̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S4_Sky_Ground_3_YU + PlusPx && PYU_Left <= S4_Sky_Ground_3_YL - PlusPx) {//�P�ԉ�
			if (PXU_Left <= S4_Sky_Ground_3_XL + PlusPx && PXL_Right >= S4_Sky_Ground_3_XL) {//�P�ԉ��̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S4_Sky_Ground_3_XU - PlusPx && PXL_Right <= S4_Sky_Ground_3_XU) {//�P�ԉ��̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S4_Sky_Ground_4_YU + PlusPx && PYU_Left <= S4_Sky_Ground_4_YL - PlusPx) {//�P�ԉE
			if (PXU_Left <= S4_Sky_Ground_4_XL + PlusPx && PXL_Right >= S4_Sky_Ground_4_XL) {//�P�ԉE�̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S4_Sky_Ground_4_XU - PlusPx && PXL_Right <= S4_Sky_Ground_4_XU) {//�P�ԉE�̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}
/*******************************************************************************************************************************/
		//���ӂ̓����蔻��//
/*******************************************************************************************************************************/
		if (PYU_Left <= S4_Sky_Ground_0_YL - PlusPx && PYL_Right >= S4_Sky_Ground_0_YL) {//�P�ԍ�
			if (PXU_Left <= S4_Sky_Ground_0_XL && PXL_Right >= S4_Sky_Ground_0_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S4_Sky_Ground_1_YL - PlusPx && PYL_Right >= S4_Sky_Ground_1_YL) {//������Q�Ԗ�
			if (PXU_Left <= S4_Sky_Ground_1_XL && PXL_Right >= S4_Sky_Ground_1_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S4_Sky_Ground_2_YL - PlusPx && PYL_Right >= S4_Sky_Ground_2_YL) {//�P�ԏ�
			if (PXU_Left <= S4_Sky_Ground_2_XL && PXL_Right >= S4_Sky_Ground_2_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S4_Sky_Ground_3_YL - PlusPx && PYL_Right >= S4_Sky_Ground_3_YL) {//�P�ԉ�
			if (PXU_Left <= S4_Sky_Ground_3_XL && PXL_Right >= S4_Sky_Ground_3_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S4_Sky_Ground_4_YL - PlusPx && PYL_Right >= S4_Sky_Ground_4_YL) {//�P�ԉE
			if (PXU_Left <= S4_Sky_Ground_4_XL && PXL_Right >= S4_Sky_Ground_4_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= 0) {//��ʏ�̓����蔻��
			VectorY *= -COR;
			if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
				VectorY += 0.9f;
			}
		}

		if (PYU_Left > Sea_Level) {//�C�ʂ����ɍs���Ə����ʒu�֖߂�����
			Death = true;
			BalloonNum = 2;
		}
/*******************************************************************************************************************************/
		//��ӂ̓����蔻��//
/*******************************************************************************************************************************/

		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S4_Sky_Ground_0_YU && PYL_Right <= S4_Sky_Ground_0_YU + PlusPx && PXU_Left <= S4_Sky_Ground_0_XL && PXL_Right >= S4_Sky_Ground_0_XU) {//�P�ԍ��̑�
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S4_Sky_Ground_1_YU && PYL_Right <= S4_Sky_Ground_1_YU + PlusPx && PXU_Left <= S4_Sky_Ground_1_XL && PXL_Right >= S4_Sky_Ground_1_XU) {//������Q�Ԗڂ̑�
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S4_Sky_Ground_2_YU && PYL_Right <= S4_Sky_Ground_2_YU + PlusPx && PXU_Left <= S4_Sky_Ground_2_XL && PXL_Right >= S4_Sky_Ground_2_XU) {//�P�ԏ�̑�
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S4_Sky_Ground_3_YU && PYL_Right <= S4_Sky_Ground_3_YU + PlusPx && PXU_Left <= S4_Sky_Ground_3_XL && PXL_Right >= S4_Sky_Ground_3_XU) {//�P�ԉ��̑�
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S4_Sky_Ground_4_YU && PYL_Right <= S4_Sky_Ground_4_YU + PlusPx && PXU_Left <= S4_Sky_Ground_4_XL && PXL_Right >= S4_Sky_Ground_4_XU) {//�P�ԉE�̑�
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 5) {//***************�@�T�X�e�[�W�@***************//
/*******************************************************************************************************************************/
		//���ʂ̓����蔻��//
/*******************************************************************************************************************************/
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S5_Sky_SGround_0_YU + PlusPx && PYU_Left <= S5_Sky_SGround_0_YL - PlusPx) {//���ߓ���
			if (PXU_Left <= S5_Sky_SGround_0_XL + PlusPx && PXL_Right >= S5_Sky_SGround_0_XL) {//���ߓ��΂̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S5_Sky_SGround_0_XU - PlusPx && PXL_Right <= S5_Sky_SGround_0_XU) {//���ߓ��΂̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S5_Sky_SGround_1_YU + PlusPx && PYU_Left <= S5_Sky_SGround_1_YL - PlusPx) {//�����ߓ���
			if (PXU_Left <= S5_Sky_SGround_1_XL + PlusPx && PXL_Right >= S5_Sky_SGround_1_XL) {//�����ߓ��΂̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S5_Sky_SGround_1_XU - PlusPx && PXL_Right <= S5_Sky_SGround_1_XU) {//�����ߓ��΂̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S5_Sky_SGround_2_YU + PlusPx && PYU_Left <= S5_Sky_SGround_2_YL - PlusPx) {//�E�ߓ���
			if (PXU_Left <= S5_Sky_SGround_2_XL + PlusPx && PXL_Right >= S5_Sky_SGround_2_XL) {//�E�ߓ��΂̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S5_Sky_SGround_2_XU - PlusPx && PXL_Right <= S5_Sky_SGround_2_XU) {//�E�ߓ��΂̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S5_Sky_Ground_0_YU + PlusPx && PYU_Left <= S5_Sky_Ground_0_YL - PlusPx) {//�P�ԏ�
			if (PXU_Left <= S5_Sky_Ground_0_XL + PlusPx && PXL_Right >= S5_Sky_Ground_0_XL) {//�P�ԏ�̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S5_Sky_Ground_0_XU - PlusPx && PXL_Right <= S5_Sky_Ground_0_XU) {//�P�ԏ�̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S5_Sky_Ground_1_YU + PlusPx && PYU_Left <= S5_Sky_Ground_1_YL - PlusPx) {//���̉E
			if (PXU_Left <= S5_Sky_Ground_1_XL + PlusPx && PXL_Right >= S5_Sky_Ground_1_XL) {//���̉E�̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S5_Sky_Ground_1_XU - PlusPx && PXL_Right <= S5_Sky_Ground_1_XU) {//���̉E�̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S5_Sky_Ground_2_YU + PlusPx && PYU_Left <= S5_Sky_Ground_2_YL - PlusPx) {//���̍�
			if (PXU_Left <= S5_Sky_Ground_2_XL + PlusPx && PXL_Right >= S5_Sky_Ground_2_XL) {//���̍��̉E
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S5_Sky_Ground_2_XU - PlusPx && PXL_Right <= S5_Sky_Ground_2_XU) {//���̍��̍�
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}
/*******************************************************************************************************************************/
		//���ӂ̓����蔻��//
/*******************************************************************************************************************************/
		if (PYU_Left <= S5_Sky_SGround_0_YL - PlusPx && PYL_Right >= S5_Sky_SGround_0_YL) {//�E�ߓ���
			if (PXU_Left <= S5_Sky_SGround_0_XL && PXL_Right >= S5_Sky_SGround_0_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S5_Sky_SGround_1_YL - PlusPx && PYL_Right >= S5_Sky_SGround_1_YL) {//�����ߓ���
			if (PXU_Left <= S5_Sky_SGround_1_XL && PXL_Right >= S5_Sky_SGround_1_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S5_Sky_SGround_2_YL - PlusPx && PYL_Right >= S5_Sky_SGround_2_YL) {//�E�ߓ���
			if (PXU_Left <= S5_Sky_SGround_2_XL && PXL_Right >= S5_Sky_SGround_2_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S5_Sky_Ground_0_YL - PlusPx && PYL_Right >= S5_Sky_Ground_0_YL) {//�P�ԏ�
			if (PXU_Left <= S5_Sky_Ground_0_XL && PXL_Right >= S5_Sky_Ground_0_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S5_Sky_Ground_1_YL - PlusPx && PYL_Right >= S5_Sky_Ground_1_YL) {//���̉E
			if (PXU_Left <= S5_Sky_Ground_1_XL && PXL_Right >= S5_Sky_Ground_1_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S5_Sky_Ground_2_YL - PlusPx && PYL_Right >= S5_Sky_Ground_2_YL) {//���̍�
			if (PXU_Left <= S5_Sky_Ground_2_XL && PXL_Right >= S5_Sky_Ground_2_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}
		
		if (PYU_Left <= 0) {//��ʏ�̓����蔻��
			VectorY *= -COR;
			if (VectorY >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
				VectorY += 0.9f;
			}
		}

		if (PYU_Left > Sea_Level) {//�C�ʂ����ɍs���Ə����ʒu�֖߂�����
			Death = true;
			BalloonNum = 2;
		}
/*******************************************************************************************************************************/
		//��ӂ̓����蔻��//
/*******************************************************************************************************************************/

		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S5_Sky_SGround_0_YU && PYL_Right <= S5_Sky_SGround_0_YU + PlusPx && PXU_Left <= S5_Sky_SGround_0_XL && PXL_Right >= S5_Sky_SGround_0_XU) {//���ߓ���
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S5_Sky_SGround_1_YU && PYL_Right <= S5_Sky_SGround_1_YU + PlusPx && PXU_Left <= S5_Sky_SGround_1_XL && PXL_Right >= S5_Sky_SGround_1_XU) {//�����ߓ���
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S5_Sky_SGround_2_YU && PYL_Right <= S5_Sky_SGround_2_YU + PlusPx && PXU_Left <= S5_Sky_SGround_2_XL && PXL_Right >= S5_Sky_SGround_2_XU) {//�E�ߓ���
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S5_Sky_Ground_0_YU && PYL_Right <= S5_Sky_Ground_0_YU + PlusPx && PXU_Left <= S5_Sky_Ground_0_XL && PXL_Right >= S5_Sky_Ground_0_XU) {//��ԏ�
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S5_Sky_Ground_1_YU && PYL_Right <= S5_Sky_Ground_1_YU + PlusPx && PXU_Left <= S5_Sky_Ground_1_XL && PXL_Right >= S5_Sky_Ground_1_XU) {//���̍�
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S5_Sky_Ground_2_YU && PYL_Right <= S5_Sky_Ground_2_YU + PlusPx && PXU_Left <= S5_Sky_Ground_2_XL && PXL_Right >= S5_Sky_Ground_2_XU) {//���̉E
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
}

//*����A�j���[�V��������*//
void Player::UpdatePlayerImgRun()
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
	if (BalloonNum == 2) {
		if (Angle == P_Right && VectorX < 0) {//�E����
			NowPlayerImg = P_Img_RunStop_Ballon_2_3;
		}
		else if (Angle == P_Left && VectorX > 0) {//������
			NowPlayerImg = P_Img_RunStop_Ballon_2_3;
		}
	}
	else if (BalloonNum == 1) {
		if (Angle == P_Right && VectorX < 0) {//�E����
			NowPlayerImg = P_Img_RunStop_Ballon_1_3;
		}
		else if (Angle == P_Left && VectorX > 0) {//������
			NowPlayerImg = P_Img_RunStop_Ballon_1_3;
		}
	}
	

	
}

//*��ԃA�j���[�V��������*//
void Player::UpdatePlayerImgFly() 
{
	//���D�P��
	if (BalloonNum == 1) {
		if (InputKey::GetKey(PAD_INPUT_B) == TRUE) {//B�{�^��				
			if (FPSCnt % 8 == 0 || FPSCnt % 8 == 1 || FPSCnt % 8 == 2 || FPSCnt % 8 == 3) {
				NowPlayerImg = P_Img_Fly_Ballon_1_1;
			}
			else if (FPSCnt % 8 == 4 || FPSCnt % 8 == 5 || FPSCnt % 8 == 6 || FPSCnt % 8 == 7) {
				NowPlayerImg = P_Img_Fly_Ballon_1_0;
			}
		}
		else if (Abtn == true) {//A�{�^��
			if (FPSCnt % 8 == 0 || FPSCnt % 8 == 1 || FPSCnt % 8 == 2 || FPSCnt % 8 == 3) {
				NowPlayerImg = P_Img_Fly_Ballon_1_1;
			}
			else if (FPSCnt % 8 == 4 || FPSCnt % 8 == 5 || FPSCnt % 8 == 6 || FPSCnt % 8 == 7) {
				NowPlayerImg = P_Img_Fly_Ballon_1_0;
			}
		}
		else {//�{�^���������Ă��Ȃ���
			if (WaitFPSCnt >= 0 && WaitFPSCnt <= 30) {
				NowPlayerImg = P_Img_Fly_Ballon_1_2;
			}
			else if (WaitFPSCnt >= 31 && WaitFPSCnt <= 60) {
				NowPlayerImg = P_Img_Fly_Ballon_1_3;
			}
			else if (WaitFPSCnt >= 61 && WaitFPSCnt <= 90) {
				NowPlayerImg = P_Img_Fly_Ballon_1_2;
			}
			else if (WaitFPSCnt >= 91 && WaitFPSCnt <= 120) {
				NowPlayerImg = P_Img_Fly_Ballon_1_4;
			}
		}
	}
	
	//���D�Q��
	if (BalloonNum == 2) {
		if (InputKey::GetKey(PAD_INPUT_B) == TRUE) {//B�{�^��				
			if (FPSCnt % 8 == 0 || FPSCnt % 8 == 1 || FPSCnt % 8 == 2 || FPSCnt % 8 == 3) {
				NowPlayerImg = P_Img_Fly_Ballon_2_1;
			}
			else if (FPSCnt % 8 == 4 || FPSCnt % 8 == 5 || FPSCnt % 8 == 6 || FPSCnt % 8 == 7) {
				NowPlayerImg = P_Img_Fly_Ballon_2_0;
			}			
		}
		else if (Abtn == true) {//A�{�^��
			if (FPSCnt % 8 == 0 || FPSCnt % 8 == 1 || FPSCnt % 8 == 2 || FPSCnt % 8 == 3) {
				NowPlayerImg = P_Img_Fly_Ballon_2_1;
			}
			else if (FPSCnt % 8 == 4 || FPSCnt % 8 == 5 || FPSCnt % 8 == 6 || FPSCnt % 8 == 7) {
				NowPlayerImg = P_Img_Fly_Ballon_2_0;
			}
		}
		else if(Abtn == false || InputKey::GetKey(PAD_INPUT_B) == FALSE){//�{�^���������Ă��Ȃ���
			if (WaitFPSCnt >= 0 && WaitFPSCnt <= 30) {
				NowPlayerImg = P_Img_Fly_Ballon_2_2;
			}
			else if (WaitFPSCnt >= 31 && WaitFPSCnt <= 60) {
				NowPlayerImg = P_Img_Fly_Ballon_2_3;
			}
			else if (WaitFPSCnt >= 61 && WaitFPSCnt <= 90) {
				NowPlayerImg = P_Img_Fly_Ballon_2_2;
			}
			else if (WaitFPSCnt >= 91 && WaitFPSCnt <= 120) {
				NowPlayerImg = P_Img_Fly_Ballon_2_4;
			}
		}
	}
}

//*�ҋ@�A�j���[�V��������*//
void Player::UpdatePlayerImgWait() 
{
	//�ҋ@��ԁi���D�P�j
	if (BalloonNum == 1) {
		if (Respawn == true) {
			if (DeathCnt % 15 == 0 || DeathCnt % 15 == 1 || DeathCnt % 15 == 2 || DeathCnt % 15 == 3 || DeathCnt % 15 == 4) {
				NowPlayerImg = P_Img_Wait_Red_Ballon_1;
			}
			else {
				NowPlayerImg = P_Img_Wait_Ballon_1_1;
			}
		}
		else if (Respawn == false) {
			if (WaitFPSCnt >= 0 && WaitFPSCnt <= 30) {
				NowPlayerImg = P_Img_Wait_Ballon_1_1;
			}
			else if (WaitFPSCnt >= 31 && WaitFPSCnt <= 60) {
				NowPlayerImg = P_Img_Wait_Ballon_1_0;
			}
			else if (WaitFPSCnt >= 61 && WaitFPSCnt <= 90) {
				NowPlayerImg = P_Img_Wait_Ballon_1_1;
			}
			else if (WaitFPSCnt >= 91 && WaitFPSCnt <= 120) {
				NowPlayerImg = P_Img_Wait_Ballon_1_2;
			}
		}
	}

	//�ҋ@��ԁi���D�Q�j
	if (BalloonNum == 2) {
		if (Respawn == true) {
			if (DeathCnt % 15 == 0 || DeathCnt % 15 == 1 || DeathCnt % 15 == 2 || DeathCnt % 15 == 3 || DeathCnt % 15 == 4) {
				NowPlayerImg = P_Img_Wait_Red_Ballon_2;
			}
			else {
				NowPlayerImg = P_Img_Wait_Ballon_2_1;
			}
		}
		else if (Respawn == false) {
			if (WaitFPSCnt >= 0 && WaitFPSCnt <= 30) {
				NowPlayerImg = P_Img_Wait_Ballon_2_1;
			}
			else if (WaitFPSCnt >= 31 && WaitFPSCnt <= 60) {
				NowPlayerImg = P_Img_Wait_Ballon_2_0;
			}
			else if (WaitFPSCnt >= 61 && WaitFPSCnt <= 90) {
				NowPlayerImg = P_Img_Wait_Ballon_2_1;
			}
			else if (WaitFPSCnt >= 91 && WaitFPSCnt <= 120) {
				NowPlayerImg = P_Img_Wait_Ballon_2_2;
			}
		}
	}
}

//*���ɓ�����A�j���[�V��������*//
void Player::UpdatePlayerImgThunder() 
{
	if (FPSCnt % 6 == 0 || FPSCnt % 6 == 1 || FPSCnt % 6 == 2) {//�Q�t���[���ŉ摜�ύX
		NowPlayerImg = P_Img_Thunder_0;
	}
	else if (FPSCnt % 6 == 3 || FPSCnt % 6 == 4 || FPSCnt % 6 ==5) {
		NowPlayerImg = P_Img_Dead_0;
	}
}

//*���S���A�j���[�V��������*//
void Player::UpdatePlayerImgDead() 
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

void Player::SetInitLocation() 
{
	PlayerX = 0;
	PlayerY = 420 - P_Img_Size;
	VectorX = 0;
	VectorY = 0;

	Respawn = true;
}

//
float Player::GetPlayerX (){
	static float X = PlayerX;
	return X;
}
float Player::GetPlayerY() {
	static float Y = PlayerY;
	return Y;
}

void Player::PlayerDeathAnim() 
{
	PlayerState = P_State_Dead;
	VectorY = 3;
	PlayerY += VectorY;
}