#include "Stage.h"
#include"Common.h"
#include "InputKey.h"

AbstractScene* gStage1::Update()
{
	gPlayer.x += gPlayer.speed;
	InputKey::Update();

	//左右移動 // 参考資料:りんごおとし
	if (InputKey::GetKey(KEY_INPUT_LEFT)/* && gPlayer.speed >= -5*/) {
		gPlayer.speed -= 0.6f;
	}
	//else
	//	if (gPlayer.speed <= 0.0f) {
	//		gPlayer.speed += 0.2f;
	//	}
	if (InputKey::GetKey(KEY_INPUT_RIGHT)/*&& gPlayer.speed < 5*/) {
		gPlayer.speed += 0.6f;
	}
	/*else
		if (gPlayer.speed > -0.0f) {
			gPlayer.speed -= 0.2f;
		}*/
	if (gPlayer.speed < 0.3f && gPlayer.speed > -0.3f) {
		if (~InputKey::GetKey(KEY_INPUT_LEFT) && ~InputKey::GetKey(KEY_INPUT_RIGHT)) {
			gPlayer.speed = 0.0f;
		}
	}
	if (CheckHitKey(KEY_INPUT_8)) {
		return nullptr;
	}
	return this;
}

void gStage1::Draw() const
{
	DrawFormatString(10, 30, C_RED, "8キーでプログラム終了");
	DrawGraph(100 + gPlayer.speed, 100, gPlayerImg, TRUE);
	DrawGraph(500, 300, gStageImg1, FALSE);
}