#include "DxLib.h"
#include "Player.h"
#include "InputKey.h"
#include "Common.h"

#define DEBUG

Player::Player() 
{
	LoadDivGraph("image/Player/Player_animation_d.png", 32, 8, 4, 64, 64, PlayerImg);//画像読み込み
	FPSCnt = 0;
}


void Player::Update() /***描画以外***/
{
	FPSCnt++;

	InputKey::Update();
	GetJoypadAnalogInput(&XStick, &YStick, DX_INPUT_PAD1);

	InputKey::GetJoyStickX(XStick);
	InputKey::GetJoyStickY(YStick);

	if (FPSCnt > 60) {
		FPSCnt = 0;
	}
}

void Player::Draw() const /***描画***/
{
	DrawGraph(100, 100, PlayerImg[P_Img_Thunder_1], TRUE);

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