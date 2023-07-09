#include "DxLib.h"
#include "Player.h"
#include "InputKey.h"
#include "Common.h"

#define DEBUG

Player::Player() 
{
	LoadDivGraph("image/Player/Player_Animation.png", 32, 8, 4, 64, 64, PlayerImg);//画像読み込み
	FPSCnt = 0;
	NowPlayerImg = P_Img_Wait_Ballon_2_0;
	BalloonNum = 2;
	PlayerState = P_State_Wait;
	PlayerX = 0;
	PlayerY = 420 - P_Img_Size;
	VectorX = 0;
	VectorY = -1;
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
	//マウスカーソル情報取得
	GetMousePoint(&MoX, &MoY);

	UpdateStageCollision();//プレイヤーとステージの当たり判定

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
	//*画面内*//
	if (Angle == Left) {//左方向に向いている時
		DrawGraph(PlayerX, PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}
	else if (Angle == Right) {//右方向に向いている時
		DrawTurnGraph(PlayerX, PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}
	else {
		DrawGraph(PlayerX, PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}

	//*画面外*//
	if (PlayerX < 0) {
		if (Angle == Left) {
			DrawGraph(640 + PlayerX, PlayerY, PlayerImg[NowPlayerImg], TRUE);
		}
		else if (Angle == Right) {
			DrawTurnGraph(640 + PlayerX, PlayerY, PlayerImg[NowPlayerImg], TRUE);
		}
	}
	else if (PlayerX > 640 - P_Img_Size) {
		if (Angle == Left) {
			DrawGraph(PlayerX - 640, PlayerY, PlayerImg[NowPlayerImg], TRUE);
		}
		else if (Angle == Right) {
			DrawTurnGraph(PlayerX - 640, PlayerY, PlayerImg[NowPlayerImg], TRUE);
		}
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
	DrawBox(PlayerX + 17, PlayerY + 14, PlayerX + 40, PlayerY + 64, C_WHITE, FALSE);
	//風船
	DrawBox(PlayerX + 12, PlayerY + 14, PlayerX + 52, PlayerY + 38, C_GREEN,FALSE);
#endif //DEBUG

}

void Player::UpdatePlayerX() //*プレイヤーのX座標処理*//
{
	if (XStick > 0) {//右
		PlayerState = P_State_Run;	//プレイヤーのステータスを走るに変更
		Angle = Right;				//向いている方向を右に変更
		VectorX = VectorX + 0.1f;	//速度＋加速度
		if (VectorX >= 4.0f) {		//速度制限
			VectorX = 4.0f;
		}
	}
	else if (XStick < 0) {//左
		PlayerState = P_State_Run;	//プレイヤーのステータスを走るに変更
		Angle = Left;				//向いている方向を左に変更
		VectorX = VectorX + -0.1f;	//速度＋加速度
		if (VectorX <= -4.0f) {		//速度制限
			VectorX = -4.0f;
		}
	}
	else if (XStick == 0) {//待機
		VectorX *= 0.95f;			//慣性
		PlayerState = P_State_Wait;	//プレイヤーのステータスを待機に変更
	}

	if (PlayerX < - P_Img_Size) {
		PlayerX = 640 - P_Img_Size;
	}
	else if (PlayerX > 640) {
		PlayerX = 0;
	}

}

void Player::UpdatePlayerY() //*プレイヤーのY座標処理*//
{
	if (PlayerY < 420 - P_Img_Size) {
		if (BalloonNum == 1) {//風船１個
			VectorY = 2.0f;
		}
		else if (BalloonNum == 2) {//風船２個
			VectorY = 1.0f;
		}
		PlayerState = P_State_Fly;//プレイヤーのステータスを飛ぶに変更
	}
	else if (PlayerY >= 420 - P_Img_Size) {
		VectorY = 0;
	}

	if (InputKey::GetKeyDown(PAD_INPUT_A)) {//Aボタンを押したら１回だけ羽ばたく(※１フレームしか入力を取っていない）
		if (PlayerX < 0) {//画面上
			VectorX *= 0.8;
		}
		else {
			VectorY = -20.0f;
		}
	}

	if (InputKey::GetKey(PAD_INPUT_B)) {//Bボタンを押したら押している間羽ばたく
		if (PlayerY < 0) {//画面上
			VectorY *= 0.8;
		}
		else {
			VectorY = -5.0f;
		}
	}
}

void Player::UpdateStageCollision() //*プレイヤーとステージの当たり判定処理*//
{
	//プレイヤーの矩形の座標
	int PXU, PYU;//左上
	int PXL, PYL;//右下
	PXU = PlayerX + 12;//左上X
	PYU = PlayerY + 14;//左上Y
	PXL = PlayerX + 52;//右下X
	PYL = PlayerY + 64;//右下Y

	if (NowStage == 1) {//ステージ１でのステージとの当たり判定
		if (PYL >= S_Ground_0_YU && PXU >= S_Ground_0_XL && PXL <= S_Ground_0_XU) {//左下の台、地面の上
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

void Player::UpdatePlayerImgRun()//*走るアニメーション処理*//
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

void Player::UpdatePlayerImgFly() //*飛ぶアニメーション処理*//
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

void Player::UpdatePlayerImgWait() //*待機アニメーション処理*//
{
	//待機状態（風船１個）
	if (BalloonNum == 1) {
		if (FPSCnt >= 0 && FPSCnt <= 20) {
			NowPlayerImg = P_Img_Wait_Ballon_1_0;
		}
		else if (FPSCnt >= 21 && FPSCnt <= 40) {
			NowPlayerImg = P_Img_Wait_Ballon_1_1;
		}
		else if (FPSCnt >= 41 && FPSCnt <= 60) {
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

void Player::UpdatePlayerImgThunder() //*雷に当たるアニメーション処理*//
{
	if (FPSCnt % 6 == 0 || FPSCnt % 6 == 1 || FPSCnt % 6 == 2) {
		NowPlayerImg = P_Img_Thunder_0;
	}
	else if (FPSCnt % 6 == 3 || FPSCnt % 6 == 4 || FPSCnt % 6 ==5) {
		NowPlayerImg = P_Img_Thunder_1;
	}
}

void Player::UpdatePlayerImgDead() //*死亡時アニメーション処理*//
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
