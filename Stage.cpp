#include "Stage.h"
#include"Common.h"
#include "InputKey.h"

AbstractScene* gStage1::Update()
{
	gPlayer.x += gPlayer.speedx;
	gPlayer.y += gPlayer.speedy;
	InputKey::Update();

	//左右移動 // 参考資料:りんごおとし
	//if (InputKey::GetKey(KEY_INPUT_LEFT)/* && gPlayer.speed >= -5*/) {
	//	gPlayer.speedx -= 5;
	//}
	//else
	//	if (gPlayer.speedx <= 0) {
	//		gPlayer.speedx += 1;
	//	}
	//if (InputKey::GetKey(KEY_INPUT_RIGHT)/*&& gPlayer.speed < 5*/) {
	//	gPlayer.speedx += 5;
	//}
	//else
	//	if (gPlayer.speedx > 0) {
	//		gPlayer.speedx -= 1;
	//	}
	//if (InputKey::GetKey(KEY_INPUT_SPACE)/* && gPlayer.speed >= -5*/) {
	//	gPlayer.speedy -= 5;
	//}
	//else
	//	if (gPlayer.speedy <= 0) {
	//		gPlayer.speedy += 1;
	//	}
	//if (gPlayer.speedx < 0&& gPlayer.speedx > 0) {
	//	if (~InputKey::GetKey(KEY_INPUT_LEFT) && ~InputKey::GetKey(KEY_INPUT_RIGHT)) {
	//		gPlayer.speedx = 1;
	//	}
	//}
	if (CheckHitKey(KEY_INPUT_2)) {
		return new gStage2();
	}
	return this;
}

void gStage1::Draw() const
{
	DrawFormatString(10, 30, C_RED, "2キーでステージ2へ");
	DrawGraph(100 + gPlayer.speedx, 365 + gPlayer.speedy, gPlayerImg, TRUE);
	DrawGraph(0, 470, gSeaImg, FALSE);
	DrawGraph(0, 450, gStageImg1, FALSE);
	DrawGraph(460, 450, gStageImg1, FALSE);
	DrawGraph(150, 270, gStageImg2, FALSE);
}

AbstractScene* gStage2::Update()
{
	gPlayer.x += gPlayer.speedx;
	gPlayer.y += gPlayer.speedy;
	InputKey::Update();

	if (CheckHitKey(KEY_INPUT_3)) {
		return new gStage3();
	}
	return this;
}

void gStage2::Draw() const
{
	DrawFormatString(10, 30, C_RED, "3キーでステージ3へ");
	DrawGraph(100 + gPlayer.speedx, 350 + gPlayer.speedy, gPlayerImg, TRUE);
	DrawGraph(0, 470, gSeaImg, FALSE);
	DrawGraph(0, 450, gStageImg1, FALSE);
	DrawGraph(460, 450, gStageImg1, FALSE);
	DrawGraph(150, 270, gStageImg2, FALSE);
	DrawGraph(50, 100, gStageImg3, FALSE);
	DrawGraph(450, 100, gStageImg3, FALSE);
}

AbstractScene* gStage3::Update()
{
	gPlayer.x += gPlayer.speedx;
	gPlayer.y += gPlayer.speedy;
	InputKey::Update();

	if (CheckHitKey(KEY_INPUT_4)) {
		return new gStage4();
	}
	return this;
}

void gStage3::Draw() const
{
	DrawFormatString(10, 30, C_RED, "4キーでステージ4へ");
	DrawGraph(100 + gPlayer.speedx, 365 + gPlayer.speedy, gPlayerImg, TRUE);
	DrawGraph(0, 470, gSeaImg, FALSE);
	DrawGraph(0, 450, gStageImg1, FALSE);
	DrawGraph(460, 450, gStageImg1, FALSE);
	DrawGraph(150, 250, gStageImg4, FALSE);
	DrawGraph(300, 200, gStageImg4, FALSE);
	DrawGraph(450, 150, gStageImg4, FALSE);
}

AbstractScene* gStage4::Update()
{
	gPlayer.x += gPlayer.speedx;
	gPlayer.y += gPlayer.speedy;
	InputKey::Update();

	if (CheckHitKey(KEY_INPUT_5)) {
		return new gStage5();
	}
	return this;
}

void gStage4::Draw() const
{
	DrawFormatString(10, 30, C_RED, "5キーでステージ5へ");
	DrawGraph(100 + gPlayer.speedx, 365 + gPlayer.speedy, gPlayerImg, TRUE);
	DrawGraph(0, 470, gSeaImg, FALSE);
	DrawGraph(0, 450, gStageImg1, FALSE);
	DrawGraph(460, 450, gStageImg1, FALSE);
	DrawGraph(150, 250, gStageImg2, FALSE);
}

AbstractScene* gStage5::Update()
{
	gPlayer.x += gPlayer.speedx;
	gPlayer.y += gPlayer.speedy;
	InputKey::Update();

	if (CheckHitKey(KEY_INPUT_6)) {
		return nullptr;
	}
	return this;
}

void gStage5::Draw() const
{
	DrawFormatString(10, 30, C_RED, "6キーでプログラム終了");
	DrawGraph(100 + gPlayer.speedx, 365 + gPlayer.speedy, gPlayerImg, TRUE);
	DrawGraph(0, 470, gSeaImg, FALSE);
	DrawGraph(0, 450, gStageImg1, FALSE);
	DrawGraph(460, 450, gStageImg1, FALSE);
	DrawGraph(150, 250, gStageImg2, FALSE);
}
