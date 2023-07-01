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
	BallonNum = Init_BallonNum;
	PlayerState = P_State_Thunder;
}


void Player::Update() /***�`��ȊO***/
{
	FPSCnt++;//�t���[���J�E���g

	//�W���C�X�e�b�N���擾
	InputKey::Update();
	GetJoypadAnalogInput(&XStick, &YStick, DX_INPUT_PAD1);
	InputKey::GetJoyStickX(XStick);
	InputKey::GetJoyStickY(YStick);

	if (PlayerState == P_State_Wait) {//�ҋ@���
		UpdatePlayerWait();
	}
	else if (PlayerState == P_State_Run) {//����
		UpdatePlayerRun();
	}
	else if (PlayerState == P_State_Thunder) {//���ɓ�����
		UpdatePlayerThunder();
	}

	if (FPSCnt > 60) {
		FPSCnt = 0;
	}
}

void Player::Draw() const /***�`��***/
{
	DrawGraph(100, 100, PlayerImg[NowPlayerImg], TRUE);

#ifdef DEBUG
	DrawFormatString(400, 10, C_WHITE, "FPS:%d", FPSCnt);
	DrawFormatString(400, 30, C_WHITE, "XStick:%d YStick:%d", XStick, YStick);
#endif // DEBUG
}

void Player::UpdatePlayerRun() 
{
	//����i���D�P�j
	if (BallonNum == 1) {
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
	if (BallonNum == 2) {
		if (FPSCnt >= 0 && FPSCnt <= 4 || FPSCnt >= 15 && FPSCnt <= 19 || FPSCnt >= 30 && FPSCnt <= 34 || FPSCnt >= 45 && FPSCnt <= 49) {
			NowPlayerImg = P_Img_Run_Ballon_2_1;
		}
		else if (FPSCnt >= 5 && FPSCnt <= 9 || FPSCnt >= 20 && FPSCnt <= 24 || FPSCnt >= 35 && FPSCnt <= 39 || FPSCnt >= 50 && FPSCnt <= 54) {
			NowPlayerImg = P_Img_Run_Ballon_2_0;
		}
		else if (FPSCnt >= 10 && FPSCnt <= 14 || FPSCnt >= 25 && FPSCnt <= 29 || FPSCnt >= 40 && FPSCnt <= 44 || FPSCnt >= 55 && FPSCnt <=60) {
			NowPlayerImg = P_Img_Run_Ballon_2_2;
		}
		/*else if (FPSCnt > 45 && FPSCnt < 60) {
			NowPlayerImg = P_Img_Run_Ballon_2_3;
		}*/
	}
}

void Player::UpdatePlayerWait() 
{
	//�ҋ@��ԁi���D�P�j
	if (BallonNum == 1) {
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
	if (BallonNum == 2) {
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

void Player::UpdatePlayerThunder() 
{
	if (FPSCnt >= 0 && FPSCnt <= 2) {
		NowPlayerImg = P_Img_Thunder_0;
	}
	else if (FPSCnt >= 3 && FPSCnt <= 5) {
		NowPlayerImg = P_Img_Thunder_1;
	}
}
