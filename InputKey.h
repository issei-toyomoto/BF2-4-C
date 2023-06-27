#pragma once
#include "DxLib.h"

class InputKey
{
private:
	/*static int key_flg;
	static int now_key;
	static int old_key;*/

public:
	static int key_flg;
	static int now_key;
	static int old_key;
	InputKey()
	{
		key_flg = 0;
		now_key = 0;
		old_key = 0;
	}

	static void Update();

	//押している間信号を送る
	static int GetKey(int key);

	//押した瞬間信号を送る
	static int GetKeyDown(int key);
};


