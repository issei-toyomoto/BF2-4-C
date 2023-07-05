#include "DxLib.h"
#include "Player.h"
#include "InputKey.h"
#include "Common.h"

#define DEBUG

Player::Player() 
{
	LoadDivGraph("image/Player/Player_animation_d.png", 32, 8, 4, 64, 64, PlayerImg);//画像読み込み
	FPSCnt = 0;
	NowPlayerImg = P_Img_Wait_Ballon_2_0;
	BalloonNum = 2;
	PlayerState = P_State_Wait;
	PlayerX = 0;
	PlayerY = 420 - P_Img_Size;
	VectorX = 0;
	VectorY = 0;
	Angle = -1;
}


void Player::Update(int Stage) /***描画以外***/
{
	FPSCnt++;//フレームカウント

	NowStage = Stage;//現在のステージ

	//ジョイステック情報取得
	InputKey::Update();
	GetJoypadAnalogInput(&XStick, &YStick, DX_INPUT_PAD1);
	InputKey::GetJoyStickX(XStick);
	InputKey::GetJoyStickY(YStick);
	GetMousePoint(&MoX, &MoY);

	//X方向
	UpdatePlayerX();
	PlayerX += VectorX;

	//Y方向
	UpdatePlayerY();
	PlayerY += VectorY;

	//画像処理
	if (PlayerState == P_State_Wait) {//待機状態
		UpdatePlayerImgWait();
	}
	else if (PlayerState == P_State_Run) {//走る
		UpdatePlayerImgRun();
	}
	else if (PlayerState == P_State_Fly) {//飛ぶ
		UpdatePlayerImgFly();
	}
	else if (PlayerState == P_State_Thunder) {//雷に当たる
		UpdatePlayerImgThunder();
	}
	else if (PlayerState == P_State_Dead) {//死亡時アニメーション
		UpdatePlayerImgDead();
	}


	//１秒たったらフレームカウントリセット
	if (FPSCnt > 60) {
		FPSCnt = 0;
	}
}

void Player::Draw() const /***描画***/
{
	if (Angle == Left) {
		DrawGraph(PlayerX, PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}
	else if (Angle == Right) {
		DrawTurnGraph(PlayerX, PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}
	else {
		DrawGraph(PlayerX, PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}
#ifdef DEBUG
	DrawFormatString(400, 10, C_WHITE, "FPS:%d", FPSCnt);						//フレームカウント
	DrawFormatString(400, 30, C_WHITE, "XStick:%d YStick:%d", XStick, YStick);  //ステックの値
	DrawFormatString(400, 50, C_WHITE, "Balloon:%d", BalloonNum);				//風船の数
	DrawFormatString(400, 70, C_WHITE, "XV:%.2f YV:%.2f", VectorX, VectorY);	//加速度
	DrawFormatString(400, 90, C_WHITE, "X:%.2f Y:%.2f", PlayerX, PlayerY);		//プレイヤー座標
	DrawFormatString(400, 110, C_WHITE, "Angle:%d(0:右 1;左)", Angle);			//向いている方向
	DrawFormatString(400, 130, C_WHITE, "MX:%d MY:%d", MoX, MoY);				//マウスカーソルの座標
	DrawFormatString(400, 150, C_WHITE, "Stage:%d", NowStage);

	//プレイヤー画像サイズ
	DrawBox(PlayerX, PlayerY, PlayerX + 64, PlayerY + 64, C_RED,FALSE);
	DrawLine(PlayerX, PlayerY, PlayerX + 64, PlayerY + 64, C_RED, 1);
	//プレイヤーサイズ
	DrawBox(PlayerX + 12, PlayerY + 14, PlayerX + 52, PlayerY + 64, C_WHITE, FALSE);
	//風船
	DrawBox(PlayerX + 12, PlayerY + 14, PlayerX + 52, PlayerY + 38, C_BLUE,FALSE);
#endif //DEBUG

}

void Player::UpdatePlayerX() 
{
	if (XStick > 0) {//右
		PlayerState = P_State_Run;
		Angle = Right;
		VectorX = VectorX + 0.1f;
		if (VectorX >= 4.0f) {//速度制限
			VectorX = 4.0f;
		}
	}
	else if (XStick < 0) {//左
		PlayerState = P_State_Run;
		Angle = Left;
		VectorX = VectorX + -0.1f;
		if (VectorX <= -4.0f) {//速度制限
			VectorX = -4.0f;
		}
	}
	else if (XStick == 0) {//待機
		VectorX *= 0.95f;//慣性
		PlayerState = P_State_Wait;
	}
}

void Player::UpdatePlayerY() 
{
	if (PlayerY < 420 - P_Img_Size) {
		if (BalloonNum == 1) {
			VectorY = 2.0f;
		}
		else if (BalloonNum == 2) {
			VectorY = 1.0f;
		}
		PlayerState = P_State_Fly;
	}
	/*else if (PlayerY >= 420 - 64) {
		VectorY = 0;
	}*/

	if (InputKey::GetKeyDown(PAD_INPUT_A)) {
		VectorY = -20.0f;
	}

	if (InputKey::GetKey(PAD_INPUT_B)) {
		VectorY = -5.0f;
	}
}

void Player::UpdateStageCollision() 
{
	int PXU, PYU;//左上
	int PXL, PYL;//右下

	PXU = PlayerX + 12;//左上X
	PYU = PlayerX + 14;//左上Y
	PXL = PlayerX + 52;//右下X
	PYL = PlayerX + 64;//右下Y

	if (NowStage == 1) {//ステージ１でのステージとの当たり判定
		if (PXU <= S_Ground_0_XL && PXL >= S_Ground_0_XU && PYU <= S_Ground_0_YU && PYL >= S_Ground_0_YU) {//左下の台
			VectorY = 0;
		}
	}
	else if (NowStage == 2) {//ステージ１でのステージとの当たり判定

	}
	else if (NowStage == 3) {//ステージ１でのステージとの当たり判定

	}
	else if (NowStage == 4) {//ステージ１でのステージとの当たり判定

	}
	else if (NowStage == 5) {//ステージ１でのステージとの当たり判定

	}
}

void Player::UpdatePlayerImgRun()
{
	//走る（風船１個）
	if (BalloonNum == 1) {
		if (FPSCnt % 15 == 0 || FPSCnt % 15 == 1 || FPSCnt % 15 == 2 || FPSCnt % 15 == 3 || FPSCnt == 4) {//５フレームごとに画像変更
			NowPlayerImg = P_Img_Run_Ballon_1_1;
		}
		else if (FPSCnt % 15 == 5 || FPSCnt % 15 == 6 || FPSCnt % 15 == 7 || FPSCnt % 15 == 8 || FPSCnt % 15 == 9) {
			NowPlayerImg = P_Img_Run_Ballon_1_0;
		}
		else if (FPSCnt % 15 == 10 || FPSCnt % 15 == 11 || FPSCnt % 15 == 12 || FPSCnt % 15 == 13 || FPSCnt % 15 == 14) {
			NowPlayerImg = P_Img_Run_Ballon_1_2;
		}
	}

	//走る（風船２個）
	if (BalloonNum == 2) {
		if (FPSCnt % 15 == 0 || FPSCnt % 15 == 1 || FPSCnt % 15 == 2 || FPSCnt % 15 == 3 || FPSCnt == 4) {//５フレームごとに画像変更
			NowPlayerImg = P_Img_Run_Ballon_2_1;
		}
		else if (FPSCnt % 15 == 5 || FPSCnt % 15 == 6 || FPSCnt % 15 == 7 || FPSCnt % 15 == 8 || FPSCnt % 15 == 9) {
			NowPlayerImg = P_Img_Run_Ballon_2_0;
		}
		else if (FPSCnt % 15 == 10 || FPSCnt % 15 == 11 || FPSCnt % 15 == 12 || FPSCnt % 15 == 13 || FPSCnt % 15 == 14) {
			NowPlayerImg = P_Img_Run_Ballon_2_2;
		}
	}

	//反対方向に向かうときの処理
	if (Angle == Right && VectorX < 0) {
		NowPlayerImg = P_Img_RunStop_Ballon_2_3;
	}
	else if (Angle == Left && VectorX > 0) {
		NowPlayerImg = P_Img_RunStop_Ballon_2_3;
	}
}

void Player::UpdatePlayerImgFly() 
{
	//風船１個
	if (InputKey::GetKeyDown(PAD_INPUT_A) || InputKey::GetKey(PAD_INPUT_B)) {
		if (BalloonNum == 1) {
			if (FPSCnt % 8 == 0 || FPSCnt % 8 == 1) {//２フレームで次の画像
				NowPlayerImg = P_Img_Fly_Ballon_1_0;
			}
			else if (FPSCnt % 8 == 2 || FPSCnt % 8 == 3) {
				NowPlayerImg = P_Img_Fly_Ballon_1_1;
			}
			else if (FPSCnt % 8 == 4 || FPSCnt % 8 == 5) {
				NowPlayerImg = P_Img_Fly_Ballon_1_2;
			}
			else if (FPSCnt % 8 == 6 || FPSCnt % 8 == 7) {
				NowPlayerImg = P_Img_Fly_Ballon_1_3;
			}
		}
	}
	else {
		NowPlayerImg = P_Img_FlyStop_Ballon_1_4;
	}
	
	//風船２個
	if (InputKey::GetKeyDown(PAD_INPUT_A) || InputKey::GetKey(PAD_INPUT_B)) {
		if (BalloonNum == 2) {
			if (FPSCnt % 8 == 0 || FPSCnt % 8 == 1) {//２フレームで次の画像
				NowPlayerImg = P_Img_Fly_Ballon_2_0;
			}
			else if (FPSCnt % 8 == 2 || FPSCnt % 8 == 3) {
				NowPlayerImg = P_Img_Fly_Ballon_2_1;
			}
			else if (FPSCnt % 8 == 4 || FPSCnt % 8 == 5) {
				NowPlayerImg = P_Img_Fly_Ballon_2_2;
			}
			else if (FPSCnt % 8 == 6 || FPSCnt % 8 == 7) {
				NowPlayerImg = P_Img_Fly_Ballon_2_3;
			}
		}
	}
	else {
		NowPlayerImg = P_Img_FlyStop_Ballon_2_4;
	}
}

void Player::UpdatePlayerImgWait() 
{
	//待機状態（風船１個）
	if (BalloonNum == 1) {
		if (FPSCnt > 0 && FPSCnt < 20) {
			NowPlayerImg = P_Img_Wait_Ballon_1_0;
		}
		else if (FPSCnt > 21 && FPSCnt < 40) {
			NowPlayerImg = P_Img_Wait_Ballon_1_1;
		}
		else if (FPSCnt > 41 && FPSCnt < 60) {
			NowPlayerImg = P_Img_Wait_Ballon_1_2;
		}
	}

	//待機状態（風船２個）
	if (BalloonNum == 2) {
		if (FPSCnt > 0 && FPSCnt < 20) {
			NowPlayerImg = P_Img_Wait_Ballon_2_0;
		}
		else if (FPSCnt > 21 && FPSCnt < 40) {
			NowPlayerImg = P_Img_Wait_Ballon_2_1;
		}
		else if (FPSCnt > 41 && FPSCnt < 60) {
			NowPlayerImg = P_Img_Wait_Ballon_2_2;
		}
	}
}

void Player::UpdatePlayerImgThunder() 
{
	if (FPSCnt % 4 == 0 || FPSCnt % 4 == 1) {
		NowPlayerImg = P_Img_Thunder_0;
	}
	else if (FPSCnt % 4 == 2 || FPSCnt % 4 == 3) {
		NowPlayerImg = P_Img_Thunder_1;
	}
}

void Player::UpdatePlayerImgDead() 
{
	if (FPSCnt % 9 == 0 || FPSCnt % 9 == 1 || FPSCnt % 9 == 2) {
		NowPlayerImg = P_Img_Dead_0;
	}
	else if (FPSCnt % 9 == 3 || FPSCnt % 9 == 4 || FPSCnt % 9 == 5) {
		NowPlayerImg = P_Img_Dead_1;
	}
	else if (FPSCnt % 9 == 6 || FPSCnt % 9 == 7 || FPSCnt % 9 == 8) {
		NowPlayerImg = P_Img_Dead_2;
	}
}
