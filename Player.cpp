#include "DxLib.h"
#include "Player.h"
#include "InputKey.h"
#include "Common.h"
#include "Fish.h"

#define DEBUG
#define DEBUG_Flg

int Player::OldFraem;
int Player::NowFraem;

float Player::PlayerX;
float Player::PlayerY;

Player::Player() 
{
	LoadDivGraph("image/Player/Player_Animation.png", 32, 8, 4, 64, 64, PlayerImg);//画像読み込み
	FPSCnt = 0;
	AbtnFPSCnt = 1;
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
	TouchFlg = Not_Touch;
	Abtn = false;
	NowFraem = 0;
	OldFraem = 0;
	WaitFPSCnt = 0;
	Respawn = true;
	DeathCnt = 0;
	XStick = 0;

	FishFlg = Fish::P_FishFlg;//Fish.cppから値を取得
}

void Player::Update(int Stage) /***描画以外***/
{
	if (Abtn == false) {//Aボタンを押してから[AbtnIntervalFream]分フレームがたったらAbtnをＦＡＬＳＥに戻す処理
		Anti_AbtnCnt++;
	}
	else if (Abtn == true) {
		if (Anti_AbtnCnt == AbtnFPSCnt) {
			Abtn = false;
		}
	}

	FPSCnt++;//フレームカウント
	AbtnFPSCnt++;
	WaitFPSCnt++;

	if (Respawn == true) {
		DeathCnt++;
		if (XStick != 0 || Abtn == true || InputKey::GetKeyDown(PAD_INPUT_B) == TRUE) {
			Respawn = false;
		}
	}

	FishFlg = Fish::P_FishFlg;//魚のフラグ更新

	if (FishFlg == true) {
		SetInitLocation();
	}

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

	//*フレームカウントリセット*//
	if (FPSCnt > 60) {//１秒たったらフレームカウントリセット
		FPSCnt = 0;
	}

	if (Anti_AbtnCnt > AbtnIntervalFream) {
		Anti_AbtnCnt = 0;
	}

	if (AbtnFPSCnt > AbtnIntervalFream) {
		AbtnFPSCnt = 0;
	}

	if (WaitFPSCnt > 120) {
		WaitFPSCnt = 0;
	}

	if (DeathCnt > 600 || Respawn == false) {
		DeathCnt = 0;
		Respawn = false;
	}
	//**************************//
#ifdef DEBUG
	if (InputKey::GetKeyDown(PAD_INPUT_10) == TRUE) {//スペースキーを押したら風船の数を１つ減らす
		BalloonNum--;
	}
#endif // DEBUG

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
	DrawFormatString(400, 30, C_WHITE, "Balloon:%d", BalloonNum);				//風船の数
	DrawFormatString(400, 50, C_WHITE, "X:%.2f Y:%.2f", PlayerX, PlayerY);		//プレイヤー座標
	DrawFormatString(400, 70, C_WHITE, "MX:%d MY:%d", MoX, MoY);				//マウスカーソルの座標
	DrawFormatString(400, 90, C_WHITE, "Stage:%d", NowStage);					//現在のステージ
	DrawFormatString(400, 120, C_WHITE, "Anti_AbtnCnt:%d",Anti_AbtnCnt);		//
	DrawFormatString(400, 150, C_WHITE, "AbtnFPS:%d", AbtnFPSCnt);				//
	DrawFormatString(400, 270, C_WHITE, "Death:%d DeathCnt:%d", Respawn, DeathCnt);
	DrawFormatString(400, 290, C_WHITE, "FishFlg:%d", FishFlg);

	//プレイヤー画像サイズ
	DrawBox((int)PlayerX, (int)PlayerY, (int)PlayerX + 64, (int)PlayerY + 64, C_RED,FALSE);
	DrawLine((int)PlayerX, (int)PlayerY, (int)PlayerX + 64, (int)PlayerY + 64, C_RED, 1);
	//プレイヤーサイズ
	DrawBox((int)PlayerX + 18, (int)PlayerY + 14, (int)PlayerX + 40, (int)PlayerY + 64, C_WHITE, FALSE);
	//プレイヤーの下辺
	DrawLine((int)PlayerX + 14, (int)PlayerY + 64, (int)PlayerX + 40, (int)PlayerY + 64, C_GREEN, 2);
	//風船
	DrawBox((int)PlayerX + 12, (int)PlayerY + 14, (int)PlayerX + 52, (int)PlayerY + 38, C_GREEN,FALSE);
#endif //DEBUG

#ifdef DEBUG_Flg
	DrawFormatString(400, 170, C_WHITE, "FlyBtn:%d(0:off 1:on)", FlyBtnFlg);	//飛ぶボタンを押しているか
	DrawFormatString(400, 190, C_WHITE, "GroundFlg:%d(0:not 1:on)", GroundFlg);	//地面に触れているか
	DrawFormatString(400, 210, C_WHITE, "TouchFlg;%d(0:not 1:on)", TouchFlg);	//地面以外に触れている
	DrawFormatString(400, 230, C_WHITE, "Abtn;%d(0:not 1:on)", Abtn);			//Aボタンを押しているか
#endif // DEBUG_Flg

}

void Player::UpdatePlayerX() //*プレイヤーのX座標処理*//
{
	if (XStick > 0) {//右
		PlayerState = P_State_Run;	//プレイヤーのステータスを走るに変更
		Angle = P_Right;				//向いている方向を右に変更
		if (GroundFlg == Ground) {//地面
			VectorX = VectorX + 0.3f;	//速度＋加速度
			if (VectorX >= 3.0f) {		//速度制限
				VectorX = 3.0f;
			}
		}
		else if (GroundFlg == Not_Ground) {//空中
			if (Abtn == true) {
				VectorX = VectorX + 0.8f;	//速度＋加速度
				if (VectorX >= 3.0f) {		//速度制限
					VectorX = 3.0f;
				}
			}
			else {
				VectorX = VectorX + 0.1f;	//速度＋加速度
				if (VectorX >= 3.0f) {		//速度制限
					VectorX = 3.0f;
				}
			}
		}
	}
	else if (XStick < 0) {//左
		PlayerState = P_State_Run;	//プレイヤーのステータスを走るに変更
		Angle = P_Left;				//向いている方向を左に変更
		if (GroundFlg == Ground) {//地面
			VectorX = VectorX + -0.3f;	//速度＋加速度
			if (VectorX <= -3.0f) {		//速度制限
				VectorX = -3.0f;
			}
		}
		else if (GroundFlg == Not_Ground) {//空中
			if (Abtn == true) {
				VectorX = VectorX + -0.8f;	//速度＋加速度
				if (VectorX <= -3.0f) {		//速度制限
					VectorX = -3.0f;
				}
			}
			else {
				VectorX = VectorX + -0.1f;	//速度＋加速度
				if (VectorX <= -3.0f) {		//速度制限
					VectorX = -3.0f;
				}
			}
		}
	}
	else if (XStick == 0) {//待機
		if (GroundFlg == Ground) {
			VectorX *= 0.89f;			//慣性
		}
		else if (GroundFlg == Not_Ground) {
			VectorX *= 0.96f;
		}
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
	if (GroundFlg == Not_Ground) {//地面の上に立っていない時
		/*if (PlayerY < _SCREEN_WIDHT_) {
					
		}*/
		if (BalloonNum == 1) {//風船１個
			VectorY = VectorY + 0.04f;
			if (VectorY >= 3.0f) {//速度制限
				VectorY = 3.0f;
			}
		}
		else if (BalloonNum == 2) {//風船２個
			VectorY = VectorY + 0.04f;
			if (VectorY >= 2.1f) {//速度制限
				VectorY = 2.1f;
			}
		}
	}
	else if (GroundFlg == Ground) {//地面の上なら落下しないようにする
		VectorY = 0;
	}

	if (FlyBtnFlg == ON_FlyBtn || GroundFlg == Not_Ground) {//A、Bボタンか地面の上に立っていない時
		PlayerState = P_State_Fly;//プレイヤーのステータスを飛ぶに変更
	}

	if (InputKey::GetKeyDown(PAD_INPUT_A) == TRUE) {//Aボタンを押したら１回だけ羽ばたく
		if (Abtn == false) {			//Aボタンのインターバル用の条件
			FlyBtnFlg = ON_FlyBtn;
			VectorY = VectorY + -0.9f;	//初速度＋加速度（上昇）
			if (VectorY <= -3.0f) {		//速度制限
				VectorY = -3.0f;
			}
			Abtn = true;
		}
	}
	else if (InputKey::GetKey(PAD_INPUT_B) == TRUE) {//Bボタンを押したら押している間羽ばたく
		FlyBtnFlg = ON_FlyBtn;
		VectorY = VectorY + -0.2f;	//初速度＋加速度（上昇）
		if (VectorY <= -3.0f) {		//速度制限
			VectorY = -3.0f;
		}
	}
	else {//A、Bボタンを押していない時
		FlyBtnFlg = OFF_FlyBtn;
	}

	
}

//*プレイヤーとステージの当たり判定処理*//
void Player::UpdateStageCollision() 
{
	//プレイヤーの矩形の座標
	int PXU_Left,  PYU_Left;//左上
	int PXL_Right, PYL_Right;//右下
	PXU_Left  = (int)PlayerX + 18;//左上X
	PYU_Left  = (int)PlayerY + 14;//左上Y
	PXL_Right = (int)PlayerX + 40;//右下X
	PYL_Right = (int)PlayerY + 64;//右下Y

	if (NowStage == 1) {//***************　１ステージ　***************//
/*******************************************************************************************************************************/
		//側面の当たり判定//
/*******************************************************************************************************************************/
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorX += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PYL_Right >= S_Sky_Ground_0_YU + PlusPx && PYU_Left <= S_Sky_Ground_0_YL - PlusPx) {//上の台（側面）
				if (PXU_Left <= S_Sky_Ground_0_XL + PlusPx && PXL_Right >= S_Sky_Ground_0_XL) {//上の台の右
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						VectorX += 0.9f;
					}
				}
				else if (PXL_Right >= S_Sky_Ground_0_XU - PlusPx && PXL_Right <= S_Sky_Ground_0_XU) {//上の台の左
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
						VectorX -= 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}
/*******************************************************************************************************************************/
		//下辺の当たり判定//
/*******************************************************************************************************************************/
			if (PYU_Left <= S_Sky_Ground_0_YL - PlusPx && PYL_Right >= S_Sky_Ground_0_YL) {//上の台（下辺）
				if (PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {
					TouchFlg = Touch;
					VectorY *= -COR;
					if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						VectorY += 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}

			if (PYU_Left <= 0) {//画面上の当たり判定
				VectorY *= -COR;
				if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorY += 0.9f;
				}
			}
		}

		if (PYU_Left > Sea_Level) {//海面したに行くと初期位置へ戻す処理
			SetInitLocation();
		}
/*******************************************************************************************************************************/
		//上辺の当たり判定//
/*******************************************************************************************************************************/
		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//右下の台（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Sky_Ground_0_YU && PYL_Right <= S_Sky_Ground_0_YU + PlusPx && PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {//浮いている中央の台（上辺）
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 2) {//***************　２ステージ　***************//
/*******************************************************************************************************************************/
		//側面の当たり判定//
/*******************************************************************************************************************************/
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorX += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PYL_Right >= S_Sky_Ground_0_YU + PlusPx && PYU_Left <= S_Sky_Ground_0_YL - PlusPx) {//上の台（側面）
				if (PXU_Left <= S_Sky_Ground_0_XL + PlusPx && PXL_Right >= S_Sky_Ground_0_XL) {//上の台の右
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						VectorX += 0.9f;
					}
				}
				else if (PXL_Right >= S_Sky_Ground_0_XU - PlusPx && PXL_Right <= S_Sky_Ground_0_XU) {//上の台の左
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
						VectorX -= 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}

			if (PYL_Right >= S2_Sky_Ground_0_YU + PlusPx && PYU_Left <= S2_Sky_Ground_0_YL - PlusPx) {//左上の台（側面）
				if (PXU_Left <= S2_Sky_Ground_0_XL + PlusPx && PXL_Right >= S2_Sky_Ground_0_XL) {//左上の台の右
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						VectorX += 0.9f;
					}
				}
				else if (PXL_Right >= S2_Sky_Ground_0_XU - PlusPx && PXL_Right <= S2_Sky_Ground_0_XU) {//左上の台の左
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
						VectorX -= 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}

			if (PYL_Right >= S2_Sky_Ground_1_YU + PlusPx && PYU_Left <= S2_Sky_Ground_1_YL - PlusPx) {//右上の台（側面）
				if (PXU_Left <= S2_Sky_Ground_1_XL + PlusPx && PXL_Right >= S2_Sky_Ground_1_XL) {//右上の台の右
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						VectorX += 0.9f;
					}
				}
				else if (PXL_Right >= S2_Sky_Ground_1_XU - PlusPx && PXL_Right <= S2_Sky_Ground_1_XU) {//右上の台の左
					TouchFlg = Touch;
					VectorX *= -COR;
					if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
						VectorX -= 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}
/*******************************************************************************************************************************/
		//下辺の当たり判定//
/*******************************************************************************************************************************/
			if (PYU_Left <= S_Sky_Ground_0_YL - PlusPx && PYL_Right >= S_Sky_Ground_0_YL) {//上の台（下辺）
				if (PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {
					TouchFlg = Touch;
					VectorY *= -COR;
					if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						VectorY += 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}

			if (PYU_Left <= S2_Sky_Ground_0_YL - PlusPx && PYL_Right >= S2_Sky_Ground_0_YL) {//左上の台（下辺）
				if (PXU_Left <= S2_Sky_Ground_0_XL && PXL_Right >= S2_Sky_Ground_0_XU) {
					TouchFlg = Touch;
					VectorY *= -COR;
					if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						VectorY += 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}

			if (PYU_Left <= S2_Sky_Ground_1_YL - PlusPx && PYL_Right >= S2_Sky_Ground_1_YL) {//右上の台（下辺）
				if (PXU_Left <= S2_Sky_Ground_1_XL && PXL_Right >= S2_Sky_Ground_1_XU) {
					TouchFlg = Touch;
					VectorY *= -COR;
					if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
						VectorY += 0.9f;
					}
				}
				else {
					TouchFlg = Not_Touch;
				}
			}

			if (PYU_Left <= 0) {//画面上の当たり判定
				VectorY *= -COR;
				if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorY += 0.9f;
				}
			}

			if (PYU_Left > Sea_Level) {//海面したに行くと初期位置へ戻す処理
				SetInitLocation();
			}
		}
/*******************************************************************************************************************************/
		//上辺の当たり判定//
/*******************************************************************************************************************************/
		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//右下の台（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Sky_Ground_0_YU && PYL_Right <= S_Sky_Ground_0_YU + PlusPx && PXU_Left <= S_Sky_Ground_0_XL && PXL_Right >= S_Sky_Ground_0_XU) {//浮いている中央の台（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S2_Sky_Ground_0_YU && PYL_Right <= S2_Sky_Ground_0_YU + PlusPx && PXU_Left <= S2_Sky_Ground_0_XL && PXL_Right >= S2_Sky_Ground_0_XU) {//浮いている左上の台（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S2_Sky_Ground_1_YU && PYL_Right <= S2_Sky_Ground_1_YU + PlusPx && PXU_Left <= S2_Sky_Ground_1_XL && PXL_Right >= S2_Sky_Ground_1_XU) {//浮いている左上の台（上辺）
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 3) {//***************　３ステージ　***************//
/*******************************************************************************************************************************/
		//側面の当たり判定//
/*******************************************************************************************************************************/
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorX += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_SGround_0_YU + PlusPx && PYU_Left <= S3_Sky_SGround_0_YL - PlusPx) {//左鍾乳石（地面）
			if (PXU_Left <= S3_Sky_SGround_0_XL + PlusPx && PXL_Right >= S3_Sky_SGround_0_XL) {//左鍾乳石の右
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_SGround_0_XU - PlusPx && PXL_Right <= S3_Sky_SGround_0_XU) {//左鍾乳石の左
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_SStone_0_YU + PlusPx && PYU_Left <= S3_Sky_SStone_0_YL - PlusPx) {//左鍾乳石（石）
			if (PXU_Left <= S3_Sky_SStone_0_XL + PlusPx && PXL_Right >= S3_Sky_SStone_0_XL) {//左鍾乳石の右
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_SStone_0_XU - PlusPx && PXL_Right <= S3_Sky_SStone_0_XU) {//左鍾乳石の左
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_SGround_1_YU + PlusPx && PYU_Left <= S3_Sky_SGround_1_YL - PlusPx) {//中央鍾乳石（地面）
			if (PXU_Left <= S3_Sky_SGround_1_XL + PlusPx && PXL_Right >= S3_Sky_SGround_1_XL) {//中央鍾乳石の右
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_SGround_1_XU - PlusPx && PXL_Right <= S3_Sky_SGround_1_XU) {//中央鍾乳石の左
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_SStone_1_YU + PlusPx && PYU_Left <= S3_Sky_SStone_1_YL - PlusPx) {//中央鍾乳石（石）
			if (PXU_Left <= S3_Sky_SStone_1_XL + PlusPx && PXL_Right >= S3_Sky_SStone_1_XL) {//中央鍾乳石の右
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_SStone_1_XU - PlusPx && PXL_Right <= S3_Sky_SStone_1_XU) {//中央鍾乳石の左
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_SGround_2_YU + PlusPx && PYU_Left <= S3_Sky_SGround_2_YL - PlusPx) {//右鍾乳石（地面）
			if (PXU_Left <= S3_Sky_SGround_2_XL + PlusPx && PXL_Right >= S3_Sky_SGround_2_XL) {//右鍾乳石の右
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_SGround_2_XU - PlusPx && PXL_Right <= S3_Sky_SGround_2_XU) {//右鍾乳石の左
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_SStone_2_YU + PlusPx && PYU_Left <= S3_Sky_SStone_2_YL - PlusPx) {//右鍾乳石（石）
			if (PXU_Left <= S3_Sky_SStone_2_XL + PlusPx && PXL_Right >= S3_Sky_SStone_2_XL) {//右鍾乳石の右
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_SStone_2_XU - PlusPx && PXL_Right <= S3_Sky_SStone_2_XU) {//右鍾乳石の左
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_Ground_0_YU + PlusPx && PYU_Left <= S3_Sky_Ground_0_YL - PlusPx) {//上空中床
			if (PXU_Left <= S3_Sky_Ground_0_XL + PlusPx && PXL_Right >= S3_Sky_Ground_0_XL) {//上空中床の右
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_Ground_0_XU - PlusPx && PXL_Right <= S3_Sky_Ground_0_XU) {//上空中床の左
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYL_Right >= S3_Sky_Ground_1_YU + PlusPx && PYU_Left <= S3_Sky_Ground_1_YL - PlusPx) {//下空中床
			if (PXU_Left <= S3_Sky_Ground_1_XL + PlusPx && PXL_Right >= S3_Sky_Ground_1_XL) {//下空中床の右
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorX += 0.9f;
				}
			}
			else if (PXL_Right >= S3_Sky_Ground_1_XU - PlusPx && PXL_Right <= S3_Sky_Ground_1_XU) {//下空中床の左
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}
/*******************************************************************************************************************************/
		//下辺の当たり判定//
/*******************************************************************************************************************************/
		if (PYU_Left <= S3_Sky_SGround_0_YL - PlusPx && PYL_Right >= S3_Sky_SGround_0_YL) {//左鍾乳石（地面）（下辺）
			if (PXU_Left <= S3_Sky_SGround_0_XL && PXL_Right >= S3_Sky_SGround_0_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_SStone_0_YL - PlusPx && PYL_Right >= S3_Sky_SStone_0_YL) {//左鍾乳石（石）（下辺）
			if (PXU_Left <= S3_Sky_SStone_0_XL && PXL_Right >= S3_Sky_SStone_0_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_SGround_1_YL - PlusPx && PYL_Right >= S3_Sky_SGround_1_YL) {//中央鍾乳石（地面）（下辺）
			if (PXU_Left <= S3_Sky_SGround_1_XL && PXL_Right >= S3_Sky_SGround_1_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_SStone_1_YL - PlusPx && PYL_Right >= S3_Sky_SStone_1_YL) {//中央鍾乳石（石）（下辺）
			if (PXU_Left <= S3_Sky_SStone_1_XL && PXL_Right >= S3_Sky_SStone_1_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_SGround_2_YL - PlusPx && PYL_Right >= S3_Sky_SGround_2_YL) {//左鍾乳石（地面）（下辺）
			if (PXU_Left <= S3_Sky_SGround_2_XL && PXL_Right >= S3_Sky_SGround_2_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_SStone_2_YL - PlusPx && PYL_Right >= S3_Sky_SStone_2_YL) {//左鍾乳石（石）（下辺）
			if (PXU_Left <= S3_Sky_SStone_2_XL && PXL_Right >= S3_Sky_SStone_2_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_Ground_0_YL - PlusPx && PYL_Right >= S3_Sky_Ground_0_YL) {//上空中床（下辺）
			if (PXU_Left <= S3_Sky_Ground_0_XL && PXL_Right >= S3_Sky_Ground_0_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= S3_Sky_Ground_1_YL - PlusPx && PYL_Right >= S3_Sky_Ground_1_YL) {//下空中床（下辺）
			if (PXU_Left <= S3_Sky_Ground_1_XL && PXL_Right >= S3_Sky_Ground_1_XU) {
				TouchFlg = Touch;
				VectorY *= -COR;
				if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorY += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}

		if (PYU_Left <= 0) {//画面上の当たり判定
			VectorY *= -COR;
			if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
				VectorY += 0.9f;
			}
		}

		if (PYU_Left > Sea_Level) {//海面したに行くと初期位置へ戻す処理
			SetInitLocation();
		}
/*******************************************************************************************************************************/
		//上辺の当たり判定//
/*******************************************************************************************************************************/

		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//右下の台（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S3_Sky_SGround_0_YU && PYL_Right <= S3_Sky_SGround_0_YU + PlusPx && PXU_Left <= S3_Sky_SGround_0_XL && PXL_Right >= S3_Sky_SGround_0_XU) {//左鍾乳石（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S3_Sky_SGround_1_YU && PYL_Right <= S3_Sky_SGround_1_YU + PlusPx && PXU_Left <= S3_Sky_SGround_1_XL && PXL_Right >= S3_Sky_SGround_1_XU) {//中央鍾乳石（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S3_Sky_SGround_2_YU && PYL_Right <= S3_Sky_SGround_2_YU + PlusPx && PXU_Left <= S3_Sky_SGround_2_XL && PXL_Right >= S3_Sky_SGround_2_XU) {//右鍾乳石（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S3_Sky_Ground_0_YU && PYL_Right <= S3_Sky_Ground_0_YU + PlusPx && PXU_Left <= S3_Sky_Ground_0_XL && PXL_Right >= S3_Sky_Ground_0_XU) {//上空中床（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S3_Sky_Ground_1_YU && PYL_Right <= S3_Sky_Ground_1_YU + PlusPx && PXU_Left <= S3_Sky_Ground_1_XL && PXL_Right >= S3_Sky_Ground_1_XU) {//下空中床（上辺）
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 4) {//***************　４ステージ　***************//
/*******************************************************************************************************************************/
		//側面の当たり判定//
/*******************************************************************************************************************************/
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorX += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}
/*******************************************************************************************************************************/
		//下辺の当たり判定//
/*******************************************************************************************************************************/
		if (PYU_Left <= 0) {//画面上の当たり判定
			VectorY *= -COR;
			if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
				VectorY += 0.9f;
			}
		}

		if (PYU_Left > Sea_Level) {//海面したに行くと初期位置へ戻す処理
			SetInitLocation();
		}
/*******************************************************************************************************************************/
		//上辺の当たり判定//
/*******************************************************************************************************************************/

		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//右下の台（上辺）
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
	else if (NowStage == 5) {//***************　５ステージ　***************//
/*******************************************************************************************************************************/
		//側面の当たり判定//
/*******************************************************************************************************************************/
		if (GroundFlg == Not_Ground) {
			if (PXU_Left <= S_Ground_Left_XL && PYL_Right >= S_Ground_Left_YU + PlusPx) {//左下の台（側面）
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
					VectorX += 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}

			if (PXL_Right >= S_Ground_Right_XU && PYL_Right >= S_Ground_Right_YU + PlusPx) {//右下の台（側面）
				TouchFlg = Touch;
				VectorX *= -COR;
				if (VectorX >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を引く
					VectorX -= 0.9f;
				}
			}
			else {
				TouchFlg = Not_Touch;
			}
		}
/*******************************************************************************************************************************/
		//下辺の当たり判定//
/*******************************************************************************************************************************/
		if (PYU_Left <= 0) {//画面上の当たり判定
			VectorY *= -COR;
			if (VectorY >= 0) {//めり込まないようにするために加速度が０以上になると加速度に値を足す
				VectorY += 0.9f;
			}
		}

		if (PYU_Left > Sea_Level) {//海面したに行くと初期位置へ戻す処理
			SetInitLocation();
		}
/*******************************************************************************************************************************/
		//上辺の当たり判定//
/*******************************************************************************************************************************/

		if (PYL_Right >= S_Ground_Left_YU && PYL_Right <= S_Ground_Left_YU + PlusPx && PXU_Left <= S_Ground_Left_XL) {//左下の台（上辺）
			GroundFlg = Ground;
		}
		else if (PYL_Right >= S_Ground_Right_YU && PYL_Right <= S_Ground_Right_YU + PlusPx && PXL_Right >= S_Ground_Right_XU) {//右下の台（上辺）
			GroundFlg = Ground;
		}
		else {
			GroundFlg = Not_Ground;
		}
	}
}

//*走るアニメーション処理*//
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
	if (Angle == P_Right && VectorX < 0) {//右方向
		NowPlayerImg = P_Img_RunStop_Ballon_2_3;
	}
	else if (Angle == P_Left && VectorX > 0) {//左方向
		NowPlayerImg = P_Img_RunStop_Ballon_2_3;
	}
}

//*飛ぶアニメーション処理*//
void Player::UpdatePlayerImgFly() 
{
	//風船１個
	if (BalloonNum == 1) {
		if (InputKey::GetKey(PAD_INPUT_B) == TRUE) {//Bボタン				
			if (FPSCnt % 8 == 0 || FPSCnt % 8 == 1 || FPSCnt % 8 == 2 || FPSCnt % 8 == 3) {
				NowPlayerImg = P_Img_Fly_Ballon_1_1;
			}
			else if (FPSCnt % 8 == 4 || FPSCnt % 8 == 5 || FPSCnt % 8 == 6 || FPSCnt % 8 == 7) {
				NowPlayerImg = P_Img_Fly_Ballon_1_0;
			}
		}
		else if (Abtn == true) {//Aボタン
			if (FPSCnt % 8 == 0 || FPSCnt % 8 == 1 || FPSCnt % 8 == 2 || FPSCnt % 8 == 3) {
				NowPlayerImg = P_Img_Fly_Ballon_1_1;
			}
			else if (FPSCnt % 8 == 4 || FPSCnt % 8 == 5 || FPSCnt % 8 == 6 || FPSCnt % 8 == 7) {
				NowPlayerImg = P_Img_Fly_Ballon_1_0;
			}
		}
		else {//ボタンを押していない時
			if (WaitFPSCnt >= 0 && WaitFPSCnt <= 30) {
				NowPlayerImg = P_Img_Fly_Ballon_1_2;
			}
			else if (WaitFPSCnt >= 31 && WaitFPSCnt <= 60) {
				NowPlayerImg = P_Img_Fly_Ballon_1_3;
			}
			else if (WaitFPSCnt >= 61 && WaitFPSCnt <= 90) {
				NowPlayerImg = P_Img_Fly_Ballon_1_2;
			}
			else if (WaitFPSCnt >= 91 && WaitFPSCnt <= 120) {
				NowPlayerImg = P_Img_Fly_Ballon_1_4;
			}
		}
	}
	
	//風船２個
	if (BalloonNum == 2) {
		if (InputKey::GetKey(PAD_INPUT_B) == TRUE) {//Bボタン				
			if (FPSCnt % 8 == 0 || FPSCnt % 8 == 1 || FPSCnt % 8 == 2 || FPSCnt % 8 == 3) {
				NowPlayerImg = P_Img_Fly_Ballon_2_1;
			}
			else if (FPSCnt % 8 == 4 || FPSCnt % 8 == 5 || FPSCnt % 8 == 6 || FPSCnt % 8 == 7) {
				NowPlayerImg = P_Img_Fly_Ballon_2_0;
			}			
		}
		else if (Abtn == true) {//Aボタン
			if (FPSCnt % 8 == 0 || FPSCnt % 8 == 1 || FPSCnt % 8 == 2 || FPSCnt % 8 == 3) {
				NowPlayerImg = P_Img_Fly_Ballon_2_1;
			}
			else if (FPSCnt % 8 == 4 || FPSCnt % 8 == 5 || FPSCnt % 8 == 6 || FPSCnt % 8 == 7) {
				NowPlayerImg = P_Img_Fly_Ballon_2_0;
			}
		}
		else if(Abtn == false || InputKey::GetKey(PAD_INPUT_B) == FALSE){//ボタンを押していない時
			if (WaitFPSCnt >= 0 && WaitFPSCnt <= 30) {
				NowPlayerImg = P_Img_Fly_Ballon_2_2;
			}
			else if (WaitFPSCnt >= 31 && WaitFPSCnt <= 60) {
				NowPlayerImg = P_Img_Fly_Ballon_2_3;
			}
			else if (WaitFPSCnt >= 61 && WaitFPSCnt <= 90) {
				NowPlayerImg = P_Img_Fly_Ballon_2_2;
			}
			else if (WaitFPSCnt >= 91 && WaitFPSCnt <= 120) {
				NowPlayerImg = P_Img_Fly_Ballon_2_4;
			}
		}
	}
}

//*待機アニメーション処理*//
void Player::UpdatePlayerImgWait() 
{
	//待機状態（風船１個）
	if (BalloonNum == 1) {
		if (Respawn == true) {
			if (DeathCnt % 15 == 0 || DeathCnt % 15 == 1 || DeathCnt % 15 == 2 || DeathCnt % 15 == 3 || DeathCnt % 15 == 4) {
				NowPlayerImg = P_Img_Wait_Red_Ballon_1;
			}
			else {
				NowPlayerImg = P_Img_Wait_Ballon_1_1;
			}
		}
		else if (Respawn == false) {
			if (WaitFPSCnt >= 0 && WaitFPSCnt <= 30) {
				NowPlayerImg = P_Img_Wait_Ballon_1_1;
			}
			else if (WaitFPSCnt >= 31 && WaitFPSCnt <= 60) {
				NowPlayerImg = P_Img_Wait_Ballon_1_0;
			}
			else if (WaitFPSCnt >= 61 && WaitFPSCnt <= 90) {
				NowPlayerImg = P_Img_Wait_Ballon_1_1;
			}
			else if (WaitFPSCnt >= 91 && WaitFPSCnt <= 120) {
				NowPlayerImg = P_Img_Wait_Ballon_1_2;
			}
		}
	}

	//待機状態（風船２個）
	if (BalloonNum == 2) {
		if (Respawn == true) {
			if (DeathCnt % 15 == 0 || DeathCnt % 15 == 1 || DeathCnt % 15 == 2 || DeathCnt % 15 == 3 || DeathCnt % 15 == 4) {
				NowPlayerImg = P_Img_Wait_Red_Ballon_2;
			}
			else {
				NowPlayerImg = P_Img_Wait_Ballon_2_1;
			}
		}
		else if (Respawn == false) {
			if (WaitFPSCnt >= 0 && WaitFPSCnt <= 30) {
				NowPlayerImg = P_Img_Wait_Ballon_2_1;
			}
			else if (WaitFPSCnt >= 31 && WaitFPSCnt <= 60) {
				NowPlayerImg = P_Img_Wait_Ballon_2_0;
			}
			else if (WaitFPSCnt >= 61 && WaitFPSCnt <= 90) {
				NowPlayerImg = P_Img_Wait_Ballon_2_1;
			}
			else if (WaitFPSCnt >= 91 && WaitFPSCnt <= 120) {
				NowPlayerImg = P_Img_Wait_Ballon_2_2;
			}
		}
	}
}

void Player::UpdatePlayerImgThunder() //*雷に当たるアニメーション処理*//
{
	if (FPSCnt % 6 == 0 || FPSCnt % 6 == 1 || FPSCnt % 6 == 2) {//２フレームで画像変更
		NowPlayerImg = P_Img_Thunder_0;
	}
	else if (FPSCnt % 6 == 3 || FPSCnt % 6 == 4 || FPSCnt % 6 ==5) {
		NowPlayerImg = P_Img_Dead_0;
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

void Player::SetInitLocation() 
{
	PlayerX = 0;
	PlayerY = 420 - P_Img_Size;
	VectorX = 0;
	VectorY = 0;

	Respawn = true;
}

float Player::GetPlayerX (){
	static float X = PlayerX;
	return X;
}

float Player::GetPlayerY() {
	static float Y = PlayerY;
	return Y;
}