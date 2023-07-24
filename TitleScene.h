#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
#include "InputKey.h"

class Title : public AbstractScene
{
private:
	/*int Key_flg;
	int Now_key;
	int Old_key;*/
	int gTitleFontImg;
	int gTitleModeImg;
	int gTitleCreditImg;
public:
	Title();
	~Title();

	AbstractScene* Update() override;
	void Draw() const override;
};