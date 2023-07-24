#include "TitleScene.h"
#include "DxLib.h"
#include "InputKey.h"
#include "GameMain.h"
#include "AbstractScene.h"
#include "Common.h"

Title::Title() {
	gTitleFontImg = LoadGraph("images-20230711T024428Z-001/images/Title/Title_Logo.png");
	gTitleModeImg = LoadGraph("images-20230711T024428Z-001/images/Title/Title_ModeSelect.png");
	gTitleCreditImg = LoadGraph("images-20230711T024428Z-001/images/Title/Title_Credit.png");
	/*Key_flg = InputKey::key_flg;
	Now_key = InputKey::now_key;
	Old_key = InputKey::old_key;*/
}

Title::~Title() {

}

AbstractScene* Title::Update()
{
	InputKey::Update();
	if (CheckHitKey(KEY_INPUT_1)) {
		return new GameMain();
	}
	else if (CheckHitKey(KEY_INPUT_6)){
		return nullptr;
	}
	return this;
}

void Title::Draw() const {
	DrawGraph(50,20, gTitleFontImg, TRUE);
	DrawGraph(170, 270, gTitleModeImg, TRUE);
	DrawGraph(190, 430, gTitleCreditImg, TRUE);
#ifdef DEBUG
	DrawString(0, 0, "1キー押したらGameMain", C_RED);
	DrawString(100, 0, "6キー押したら終了", C_RED)
#endif // DEBUG
}