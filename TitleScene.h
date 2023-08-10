#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
#include "InputKey.h"
#include"Soundstorage.h"
class Title : public AbstractScene
{
private:
	/*int Key_flg;
	int Now_key;
	int Old_key;*/
	InputKey inputkey;
	Soundstorage ss;

	int gTitleFontImg;
	int gTitleModeImg;
	int gTitleCreditImg;
	int gTitleCursorAnim[4];
	int FPSCount;
	int MenuNumber;
	int gMenuY;
public:
	Title();
	~Title();

	AbstractScene* Update() override;
	void Draw() const override;
};