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
	FlyBtnFlg = OFF_FlyBtn;
	GroundFlg = Not_Ground;
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
	if (FlyBtnFlg == ON_FlyBtn || GroundFlg == Ground) {
		UpdatePlayerX();
	}
	else {
		//画面端のX座標処理
		if (PlayerX < -(P_Img_Size)) {//右端
			PlayerX = 640 - P_Img_Size;
		}
		else if (PlayerX > 640) {//左端
			PlayerX = 0;
		}

		//ステックが傾けている方向にキャラクターのアングルを変える処理
		if (XStick > 0) {
			Angle = P_Right;
		}
		else if (XStick < 0) {
			Angle = P_Left;
		}
	}
	PlayerX += VectorX;//X座標更新

	//Y方向
	UpdatePlayerY();
	PlayerY += VectorY;//Y座標更新

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
	if (Angle == P_Left) {//左方向に向いている時
		DrawGraph((int)PlayerX, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}
	else if (Angle == P_Right) {//右方向に向いている時
		DrawTurnGraph((int)PlayerX, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}
	else {
		DrawGraph((int)PlayerX, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
	}

	//*画面外*//
	if (PlayerX < 0) {
		if (Angle == P_Left) {
			DrawGraph(640 + (int)PlayerX, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
		}
		else if (Angle == P_Right) {
			DrawTurnGraph(640 + (int)PlayerX, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
		}
	}
	else if (PlayerX > 640 - P_Img_Size) {
		if (Angle == P_Left) {
			DrawGraph((int)PlayerX - 640, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
		}
		else if (Angle == P_Right) {
			DrawTurnGraph((int)PlayerX - 640, (int)PlayerY, PlayerImg[NowPlayerImg], TRUE);
		}
	}

#ifdef DEBUG
	DrawFormatString(400, 10, C_WHITE, "FPS:%d", FPSCnt);						//フレームカウント
	DrawFormatString(400, 30, C_WHITE, "XStick:%d YStick:%d", XStick, YStick);  //ステックの値
	DrawFormatString(400, 50, C_WHITE, "Balloon:%d", BalloonNum);				//風船の数
	DrawFormatString(400, 70, C_WHITE, "XV:%.2f YV:%.2f", VectorX, VectorY);	//加速度
	DrawFormatString(400, 90, C_WHITE, "X:%.2f Y:%.2f", PlayerX, PlayerY);		//プレイヤー座標
	DrawFormatString(400, 110, C_WHITE, "Angle:%d(1;左 0:右)", Angle);			//向いている方向
	DrawFormatString(400, 130, C_WHITE, "MX:%d MY:%d", MoX, MoY);				//マウスカーソルの座標
	DrawFormatString(400, 150, C_WHITE, "Stage:%d", NowStage);					//現在のステージ
	DrawFormatString(400, 170, C_WHITE, "FlyBtn:%d(0:off 1:on)", FlyBtnFlg);//飛ぶボタンを押しているかどうか
	DrawFormatString(400, 190, C_WHITE, "GroundFlg:%d(0:not 1:on)", GroundFlg);

	//プレイヤー画像サイズ
	DrawBox((int)PlayerX, (int)PlayerY, (int)PlayerX + 64, (int)PlayerY + 64, C_RED,FALSE);
	DrawLine((int)PlayerX, (int)PlayerY, (int)PlayerX + 64, (int)PlayerY + 64, C_RED, 1);
	//プレイヤーサイズ
	DrawBox((int)PlayerX + 18, (int)PlayerY + 14, (int)PlayerX + 40, (int)PlayerY + 64, C_WHITE, FALSE);
	//風船
	DrawBox((int)PlayerX + 12, (int)PlayerY + 14, (int)PlayerX + 52, (int)PlayerY + 38, C_GREEN,FALSE);
#endif //DEBUG

}

void Player::UpdatePlayerX() //*プレイヤーのX座標処理*//
{
	if (XStick > 0) {//右
		PlayerState = P_State_Run;	//プレイヤーのステータスを走るに変更
		Angle = P_Right;				//向いている方向を右に変更
		VectorX = VectorX + 0.3f;	//速度＋加速度
		if (VectorX >= 3.0f) {		//速度制限
			VectorX = 3.0f;
		}
	}
	else if (XStick < 0) {//左
		PlayerState = P_State_Run;	//プレイヤーのステータスを走るに変更
		Angle = P_Left;				//向いている方向を左に変更
		VectorX = VectorX + -0.3f;	//速度＋加速度
		if (VectorX <= -3.0f) {		//速度制限
			VectorX = -3.0f;
		}
	}
	else if (XStick == 0) {//待機
		VectorX *= 0.89f;			//慣性
		PlayerState = P_State_Wait;	//プレイヤーのステータスを待機に変更
	}

	//画面端のX座標処理
	if (PlayerX < -(P_Img_Size)) {//右端
		PlayerX = 640 - P_Img_Size;
	}
	else if (PlayerX > 640) {//左端
		PlayerX = 0;
	}
}

void Player::UpdatePlayerY() //*プレイヤーのY座標処理*//
{
	//落下処理
	if (GroundFlg == Not_Ground) {
		if (PlayerY < _SCREEN_WIDHT_) {
			if (BalloonNum == 1) {//風船１個
				VectorY = VectorY + 0.4f;
				if (VectorY >= 4.0f) {//速度制限
					VectorY = 4.0f;
				}
			}
			else if (BalloonNum == 2) {//風船２個
				VectorY =VectorY + 0.4f;
				if (VectorY >= 2.0f) {//速度制限
					VectorY = 2.0f;
				}
			}
			PlayerState = P_State_Fly;//プレイヤーのステータスを飛ぶに変更
		}
	}

	if (InputKey::GetKeyDown(PAD_INPUT_A)) {//Aボタンを押したら１回だけ羽ばたく(※１フレームしか入力を取っていない）
		FlyBtnFlg = ON_FlyBtn;
		if (PlayerY < 0) {//画面上（未完成）
			VectorY = VectorY * 0.8f;
		}
		else {
			VectorY = -5.0f;
		}
	}
	else if (InputKey::GetKey(PAD_INPUT_B)) {//Bボタンを押したら押している間羽ばたく
		FlyBtnFlg = ON_FlyBtn;
		if (PlayerY < 0) {//画面上（未完成）
			VectorY = VectorY * 0.8f;
		}
		else {
			VectorY = -2.0f;
		}
	}
	else {
		FlyBtnFlg = OFF_FlyBtn;
	}
}

void Player::UpdateStageCollision() //*プレイヤーとステージの当たり判定処理*//
{
	//プレイヤーの矩形の座標
	int PXU_Left,  PYU_Left;//左上
	int PXL_Right, PYL_Right;//右下
	PXU_Left  = (int)PlayerX + 18;//左上X
	PYU_Left  = (int)PlayerY + 14;//左上Y
	PXL_Right = (int)PlayerX + 40;//右下X
	PYL_Right = (int)PlayerY + 64;//右下Y

	if (NowStage == 1) {//ステージ１でのステージとの当たり判定(地面に埋まる＆地面に引っかかるバグあり)

		//台の側面＆下辺//
		if (GroundFlg == Not_Ground) {
			if (PXL_Right >= S_Sky_Ground_0_XU && PXU_Left <= S_Sky_Ground_0_XL) {//浮いている中央の台（側面）
				if (PYU_Left <= S_Sky_Ground_0_YL && PYL_Right >= S_Sky_Ground_0_YU) {
					VectorX *= -1.0f;
				}
			}

			if (PYU_Left < S_Sky_Ground_0_YL && PYL_Right > S_Sky_Ground_0_YU) {//浮いている中央の台（下辺）
				if (PXL_Right >= S_Sky_Ground_0_XU && PXU_Left <= S_Sky_Ground_0_XL) {
					VectorY *= -1.0f;
				}
			}

			if (PYL_Right > S_Ground_Left_YU) {//左下の台（側面）
				if (PXU_Left <= S_Ground_Left_XL) {
					VectorX *= -1.0f;
				}
			}

			if (PYL_Right > S_Ground_Right_YU) {//右下の台（側面）
				if (PXL_Right >= S_Ground_Right_XU) {
					VectorX *= -1.0f;
				}
			}
		}
		
		//台の上辺//
		if (PYL_Right >= S_Ground_Left_YU) {//左下の台と右下の台のY座標は一緒
			if (PXL_Right >= -P_Img_Size && PXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
				GroundFlg = Ground;
				VectorY = 0;
			}
			else if (PXL_Right >= S_Ground_Right_XU && PXU_Left <= S_Ground_Right_XL + P_Img_Size) {//右下の台（上辺）
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else if (PYL_Right >= S_Sky_Ground_0_YU && PYU_Left <= S_Sky_Ground_0_YL) {//浮いている中央の台（上辺）
			if (PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else {
			GroundFlg = Not_Ground;
		}

	}
	else if (NowStage == 2) {//ステージ１でのステージとの当たり判定(未完成)
		if (PYL_Right >= S_Ground_Left_YU) {
			if (PXL_Right >= -P_Img_Size && PXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
				GroundFlg = Ground;
				VectorY = 0;
			}
			else if (PXL_Right >= S_Ground_Right_XU && PXU_Left <= S_Ground_Right_XL + P_Img_Size) {//右下の台（上辺）
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else if (PYL_Right >= S_Sky_Ground_0_YU && PYU_Left <= S_Sky_Ground_0_YL) {//浮いている中央の台（上辺）
			if (PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 3) {//ステージ１でのステージとの当たり判定
		if (PYL_Right >= S_Ground_Left_YU) {
			if (PXL_Right >= -P_Img_Size && PXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
				GroundFlg = Ground;
				VectorY = 0;
			}
			else if (PXL_Right >= S_Ground_Right_XU && PXU_Left <= S_Ground_Right_XL + P_Img_Size) {//右下の台（上辺）
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 4) {//ステージ１でのステージとの当たり判定
		if (PYL_Right >= S_Ground_Left_YU) {
			if (PXL_Right >= -P_Img_Size && PXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
				GroundFlg = Ground;
				VectorY = 0;
			}
			else if (PXL_Right >= S_Ground_Right_XU && PXU_Left <= S_Ground_Right_XL + P_Img_Size) {//右下の台（上辺）
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 5) {//ステージ１でのステージとの当たり判定
		if (PYL_Right >= S_Ground_Left_YU) {
			if (PXL_Right >= -P_Img_Size && PXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
				GroundFlg = Ground;
				VectorY = 0;
			}
			else if (PXL_Right >= S_Ground_Right_XU && PXU_Left <= S_Ground_Right_XL + P_Img_Size) {//右下の台（上辺）
				GroundFlg = Ground;
				VectorY = 0;
			}
			else {
				GroundFlg = Not_Ground;
			}
		}
		else {
			GroundFlg = Not_Ground;
		}
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
	if (Angle == P_Right && VectorX < 0) {//右方向
		NowPlayerImg = P_Img_RunStop_Ballon_2_3;
	}
	else if (Angle == P_Left && VectorX > 0) {//左方向
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
	if (FPSCnt % 6 == 0 || FPSCnt % 6 == 1 || FPSCnt % 6 == 2) {//２フレームで画像変更
		NowPlayerImg = P_Img_Thunder_0;
	}
	else if (FPSCnt % 6 == 3 || FPSCnt % 6 == 4 || FPSCnt % 6 ==5) {
		NowPlayerImg = P_Img_Thunder_1;
	}
}

void Player::UpdatePlayerImgDead() //*死亡時アニメーション処理*//
{
	if (FPSCnt % 9 == 0 || FPSCnt % 9 == 1 || FPSCnt % 9 == 2) {//２フレームで画像変更
		NowPlayerImg = P_Img_Dead_0;
	}
	else if (FPSCnt % 9 == 3 || FPSCnt % 9 == 4 || FPSCnt % 9 == 5) {
		NowPlayerImg = P_Img_Dead_1;
	}
	else if (FPSCnt % 9 == 6 || FPSCnt % 9 == 7 || FPSCnt % 9 == 8) {
		NowPlayerImg = P_Img_Dead_2;
	}
}

float Player::GetPlayerX (){
	float X = PlayerX;
	return X;
}

float Player::GetPlayerY() {
	float Y = PlayerY;
	return Y;
}