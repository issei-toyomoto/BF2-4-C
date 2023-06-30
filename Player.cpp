#include "DxLib.h"
#include "Player.h"
#include "InputKey.h"
#include "Common.h"

#define DEBUG

Player::Player() 
{
	LoadDivGraph("image/Player/Player_animation_d.png", 32, 8, 4, 64, 64, PlayerImg);//画像読み込み
	FPSCnt = 0;
	NowPlayerImg = P_Img_Wait_Ballon_2_0;
	BallonNum = Init_BallonNum;
	PlayerState = P_State_Wait;
}


void Player::Update() /***描画以外***/
{
	FPSCnt++;//フレームカウント

	//ジョイステック情報取得
	InputKey::Update();
	GetJoypadAnalogInput(&XStick, &YStick, DX_INPUT_PAD1);
	InputKey::GetJoyStickX(XStick);
	InputKey::GetJoyStickY(YStick);

	//待機状態（風船２個）
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

	//待機状態（風船１個）
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
	


	if (FPSCnt > 60) {
		FPSCnt = 0;
	}
}

void Player::Draw() const /***描画***/
{
	DrawGraph(100, 100, PlayerImg[NowPlayerImg], TRUE);

#ifdef DEBUG
	DrawFormatString(480, 10, C_WHITE, "FPS:%d", FPSCnt);
#endif // DEBUG
}

void Player::UpdatePlayerMove() 
{
	
}

void Player::DrawPlayerMove()const 
{

}