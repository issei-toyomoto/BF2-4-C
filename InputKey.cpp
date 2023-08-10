#include "InputKey.h"

int InputKey::key_flg;
int InputKey::now_key;
int InputKey::old_key;

int InputKey::Xbuf;
int InputKey::Ybuf;

int InputKey::X_flg;
int InputKey::X_now;
int InputKey::X_old;

int InputKey::Y_flg;
int InputKey::Y_now;
int InputKey::Y_old;

void InputKey::Update()
{
	old_key = now_key;
	now_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	key_flg = now_key & ~old_key;

	GetJoypadAnalogInput(&Xbuf, &Ybuf, DX_INPUT_PAD1);
	X_old = X_now;
	X_now = Xbuf;
	X_flg = X_now & ~X_old;

	Y_old = Y_now;
	Y_now = Ybuf;
	Y_flg = Y_now & ~Y_old;
}

/********ボタン入力*********/
int InputKey::GetKey(int key)
{
	if (now_key & key)
	{
		return TRUE;
	}

	return FALSE;
}

int InputKey::GetKeyDown(int key)
{
	if (key_flg & key)
	{
		return TRUE;
	}

	return FALSE;
}

/********ジョイスティックX軸*********/
int InputKey::GetJoyStickX() 
{
	return Xbuf;
}

int InputKey::GetJoyStickXOnes() 
{
	if (X_flg & 0) {
		return TRUE;
	}
	return FALSE;
}

/********ジョイスティックY軸*********/
int InputKey::GetJoyStickY()
{
	return Ybuf;
}

int InputKey::GetJoyStickYOnes()
{
	if (Y_flg  & Y_now & !0) {
		return TRUE;
	}
	return FALSE;
}