#include "DxLib.h"
#include "Player.h"
#include "InputKey.h"
#include "Common.h"

#define DEBUG

Player::Player() 
{
	LoadDivGraph("image/Player/Player_animation_d.png", 32, 8, 4, 64, 64, PlayerImg);//�摜�ǂݍ���
	FPSCnt = 0;
	NowPlayerImg = P_Img_Wait_Ballon_2_0;
	BalloonNum = 2;
	PlayerState = P_State_Wait;
	PlayerX = 0;
	PlayerY = 400;
	VectorX = 0;
}


void Player::Update() /***�`��ȊO***/
{
	FPSCnt++;//�t���[���J�E���g

	//�W���C�X�e�b�N���擾
	InputKey::Update();
	GetJoypadAnalogInput(&XStick, &YStick, DX_INPUT_PAD1);
	InputKey::GetJoyStickX(XStick);
	InputKey::GetJoyStickY(YStick);

	//X����
	if (XStick > 0) {
		VectorX = 2;
		PlayerState = P_State_Run;
		Direction = Right;
	}
	else if (XStick < 0) {
		VectorX = -2;
		PlayerState = P_State_Run;
		Direction = Left;
	}
	else if (XStick == 0) {
		VectorX = 0;
		PlayerState = P_State_Wait;
	}

	PlayerX += VectorX;

	//Y����
	if (PlayerY < 400) {
		if (BalloonNum == 1) {
			VectorY = 2;
		}
		else if (BalloonNum == 2) {
			VectorY = 1;
		}
		PlayerState = P_State_Fly;
	}
	else if (PlayerY >= 400) {
		VectorY = 0;
	}
	
	
	if (InputKey::GetKeyDown(PAD_INPUT_A)) {
		VectorY = -30;
	}

	if (InputKey::GetKey(PAD_INPUT_B)) {
		VectorY = -5;
	}

	PlayerY += VectorY;

	//�摜����
	if (PlayerState == P_State_Wait) {//�ҋ@���
		UpdatePlayerImgWait();
	}
	else if (PlayerState == P_State_Run) {//����
		UpdatePlayerImgRun();
	}
	else if (PlayerState == P_State_Fly) {
		UpdatePlayerImgFly();
	}
	else if (PlayerState == P_State_Thunder) {//���ɓ�����
		UpdatePlayerImgThunder();
	}


	//�P�b��������t���[���J�E���g
	if (FPSCnt > 60) {
		FPSCnt = 0;
	}


#ifdef DEBUG

#endif // DEBUG

}

void Player::Draw() const /***�`��***/
{
	if (Direction == Left) {
		DrawGraph(PlayerX, PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}
	else if (Direction == Right) {
		DrawTurnGraph(PlayerX, PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}
	else {
		DrawGraph(PlayerX, PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}
	

#ifdef DEBUG
	DrawFormatString(400, 10, C_WHITE, "FPS:%d", FPSCnt);
	DrawFormatString(400, 30, C_WHITE, "XStick:%d YStick:%d", XStick, YStick);
	DrawFormatString(400, 50, C_WHITE, "Balloon:%d", BalloonNum);
	DrawFormatString(400, 70, C_WHITE, "XV:%d YV:%d", VectorX,VectorY);
	DrawFormatString(400, 90, C_WHITE, "X:%d Y:%d", PlayerX, PlayerY);
#endif // DEBUG
}

void Player::UpdatePlayerImgRun() 
{
	//����i���D�P�j
	if (BalloonNum == 1) {
		if (FPSCnt >= 0 && FPSCnt <= 4 || FPSCnt >= 15 && FPSCnt <= 19 || FPSCnt >= 30 && FPSCnt <= 34 || FPSCnt >= 45 && FPSCnt <= 49) {
			NowPlayerImg = P_Img_Run_Ballon_1_1;
		}
		else if (FPSCnt >= 5 && FPSCnt <= 9 || FPSCnt >= 20 && FPSCnt <= 24 || FPSCnt >= 35 && FPSCnt <= 39 || FPSCnt >= 50 && FPSCnt <= 54) {
			NowPlayerImg = P_Img_Run_Ballon_1_0;
		}
		else if (FPSCnt >= 10 && FPSCnt <= 14 || FPSCnt >= 25 && FPSCnt <= 29 || FPSCnt >= 40 && FPSCnt <= 44 || FPSCnt >= 55 && FPSCnt <= 60) {
			NowPlayerImg = P_Img_Run_Ballon_1_2;
		}
		/*else if (FPSCnt > 45 && FPSCnt < 60) {
			NowPlayerImg = P_Img_RunStop_Ballon_1_3;
		}*/
	}

	//����i���D�Q�j
	if (BalloonNum == 2) {
		if (FPSCnt % 15 == 0 || FPSCnt % 15 == 1 || FPSCnt % 15 == 2 || FPSCnt % 15 == 3 || FPSCnt == 4) {
			NowPlayerImg = P_Img_Run_Ballon_2_1;
		}
		else if (FPSCnt % 15 == 5 || FPSCnt % 15 == 6 || FPSCnt % 15 == 7 || FPSCnt % 15 == 8 || FPSCnt % 15 == 9) {
			NowPlayerImg = P_Img_Run_Ballon_2_0;
		}
		else if (FPSCnt % 15 == 10 || FPSCnt % 15 == 11 || FPSCnt % 15 == 12 || FPSCnt % 15 == 13 || FPSCnt % 15 == 14) {
			NowPlayerImg = P_Img_Run_Ballon_2_2;
		}
	}
}

void Player::UpdatePlayerImgFly() 
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

void Player::UpdatePlayerImgWait() 
{
	//�ҋ@��ԁi���D�P�j
	if (BalloonNum == 1) {
		if (FPSCnt > 0 && FPSCnt < 20) {
			NowPlayerImg = P_Img_Wait_Ballon_1_0;
		}
		else if (FPSCnt > 21 && FPSCnt < 40) {
			NowPlayerImg = P_Img_Wait_Ballon_1_1;
		}
		else if (FPSCnt > 41 && FPSCnt < 60) {
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

void Player::UpdatePlayerImgThunder() 
{
	if (FPSCnt % 3 == 0) {
		NowPlayerImg = P_Img_Thunder_0;
	}
	else if (FPSCnt % 5 == 0) {
		NowPlayerImg = P_Img_Thunder_1;
	}
}
