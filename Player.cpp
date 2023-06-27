#include "DxLib.h"
#include "Player.h"
#include "InputKey.h"
#include "Common.h"

#define DEBUG

void Player::Update() /***•`‰æˆÈŠO***/
{
	InputKey::Update();
	GetJoypadAnalogInput(&XStick, &YStick, DX_INPUT_PAD1);

	InputKey::GetJoyStickX(XStick);
	InputKey::GetJoyStickY(YStick);
}

void Player::Draw() const /***•`‰æ***/
{


#ifdef DEBUG
	DrawFormatString(10, 10, C_WHITE, "X:%d Y:%d",XStick,YStick);
#endif // DEBUG
}