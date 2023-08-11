#include "TitleScene.h"
#include "DxLib.h"
#include "InputKey.h"
#include "GameMain.h"
#include "AbstractScene.h"
#include "Common.h"
#define DEBUG

Title::Title() {
	gTitleFontImg = LoadGraph("images-20230711T024428Z-001/images/Title/Title_Logo.png");
	gTitleModeImg = LoadGraph("images-20230711T024428Z-001/images/Title/Title_ModeSelect.png");
	gTitleCreditImg = LoadGraph("images-20230711T024428Z-001/images/Title/Title_Credit.png");
	LoadDivGraph("images-20230711T024428Z-001/images/Title/Title_CursorAnimation.png", 4, 4, 1, 32, 64, gTitleCursorAnim);
	FPSCount = 0;
	MenuNumber = 0;
	gMenuY = 0;
}

Title::~Title() {

}

AbstractScene* Title::Update()
{
	/*PlaySoundMem(soundstorage.TripBGM, DX_PLAYTYPE_LOOP, TRUE);*/
	FPSCount++;
	InputKey::Update();
	gMenuY = MenuNumber * 30;
	if (FPSCount == 60) {
		FPSCount = 0;
	}
	if  (InputKey::GetJoyStickYOnes() > 0) {
		if (++MenuNumber > 2)MenuNumber = 0;
	}
	if (InputKey::GetJoyStickYOnes() < 0)
		if (--MenuNumber < 0)MenuNumber = 2;
	if (inputkey.GetKey(PAD_INPUT_1) == TRUE && MenuNumber == 0 || inputkey.GetKey(PAD_INPUT_8)) {
		PlaySoundMem(ss.gStartSE, DX_PLAYTYPE_BACK, TRUE);
		return new GameMain();
	}
	else if (CheckHitKey(KEY_INPUT_6)) {
		return nullptr;
	}
	return this;
}

void Title::Draw() const {
	DrawGraph(50, 40, gTitleFontImg, TRUE);
	DrawGraph(170, 290, gTitleModeImg, TRUE);
	DrawGraph(190, 430, gTitleCreditImg, TRUE);
	if (FPSCount >= 0 && FPSCount <= 14) {
		DrawGraph(130, 275 + gMenuY, gTitleCursorAnim[0],TRUE);
	}
	if (FPSCount >= 15 && FPSCount <= 29) {
		DrawGraph(130, 275 + gMenuY, gTitleCursorAnim[1], TRUE);
	}
	if (FPSCount >= 30 && FPSCount <= 44) {
		DrawGraph(130, 275 + gMenuY, gTitleCursorAnim[2], TRUE);
	}
	if (FPSCount >= 45 && FPSCount <= 60) {
		DrawGraph(130, 275 + gMenuY, gTitleCursorAnim[3], TRUE);
	}
#ifdef DEBUG
	DrawString(250, 0, "6ƒL[‰Ÿ‚µ‚½‚çI—¹", C_RED);
#endif // DEBUG
}