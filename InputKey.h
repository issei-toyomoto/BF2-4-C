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

	//�����Ă���ԐM���𑗂�
	static int GetKey(int key);

	//�������u�ԐM���𑗂�
	static int GetKeyDown(int key);
};


