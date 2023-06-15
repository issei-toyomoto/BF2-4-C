#pragma once
#include "DxLib.h"

class InputKey
{
private:
	static int key_flg;
	static int now_key;
	static int old_key;

public:
	InputKey()
	{
		key_flg = 0;
		now_key = 0;
		old_key = 0;
	}

	static void Update();

	//‰Ÿ‚µ‚Ä‚¢‚éŠÔM†‚ğ‘—‚é
	static int GetKey(int key);

	//‰Ÿ‚µ‚½uŠÔM†‚ğ‘—‚é
	static int GetKeyDown(int key);
};


