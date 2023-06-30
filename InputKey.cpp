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
	GetJoypadAnalogInput(&Xbuf, &Ybuf, DX_INPUT_PAD1);
	X_old = X_now;
	X_now = Xbuf;
	X_flg = X_now & ~X_old;

	Y_old = Y_now;
	Y_now = Ybuf;
	Y_flg = Y_now & ~Y_old;

	old_key = now_key;
	now_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	key_flg = now_key & ~old_key;
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
int InputKey::GetJoyStickX(int X) 
{
	if (X_now & X) {
		return TRUE;
	}
	return FALSE;
}

int InputKey::GetJoyStickXOnes(int X) 
{
	if (X_flg & X) {
		return TRUE;
	}
	return FALSE;
}

/********ジョイスティックY軸*********/
int InputKey::GetJoyStickY(int Y)
{
	if (Y_now & Y) {
		return TRUE;
	}
	return FALSE;
}

int InputKey::GetJoyStickYOnes(int Y)
{
	if (Y_flg & Y) {
		return TRUE;
	}
	return FALSE;
}