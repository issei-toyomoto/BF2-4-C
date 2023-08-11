#include"DxLib.h"
#include"Fish.h"
#include<math.h>
#include"Player.h"
#include"Enemy.h"

bool Fish::P_FishFlg;
bool Fish::E_FishFlg;

//コンストラクタ
Fish::Fish() {
	LoadDivGraph("image/Enemy/Enemy_FishAnimation.png",10,5,2,64,64,FishImage);
	f_PosX = 150;
	f_PosY = 400;
	Count = 0;
	Second = 0;
	FishRand = 0;
	P_SpawnFlg = FALSE;
	E_SpawnFlg = FALSE;
	f_Count = 120;
	P_X = Player::PlayerX;
	P_Y = Player::PlayerY;
	E_X = 0;
	E_Y = 0;
	Target = 0;
	FishAnim = 0;
	WaitTime = 51;
	P_FishFlg = FALSE;
	TurnFlg = FALSE;
	E_Color = 0;
}

//魚生成
void Fish::Draw() const {
	if (P_SpawnFlg==TRUE||E_SpawnFlg) {
		//魚画像(アニメーション)
		if (TurnFlg == FALSE) {
			DrawLeft();
		}
		else if (TurnFlg == TRUE) {
			DrawRight();
		}
	}
}

//出現エリア
void Fish::Update() {
	CheckPlayer();
	if (E_SpawnFlg == FALSE) {
		CheckEnemy();
	}
}

//魚移動(プレイヤー)
void Fish::P_MoveFish() {
	Target = 1;
	f_PosX = P_X;
	FishAnim = f_Count / 17;
	//アニメーション計算
	f_Count = f_Count - 2;
	if (FishAnim == 3) {
		P_FishFlg = TRUE;
	}
	//プレイヤー接触後
	if (f_Count <= 0) {
		WaitTime--;
		if (WaitTime <= 0) {
			InitFish();
		}
	}
}

//魚移動(敵)
void Fish::E_MoveFish() {
	//攻撃対象が敵
	switch (E_Color) {
	case 0:
		Target = 2;
		break;
	case 1:
		Target = 3;
		break;
	case 2:
		Target = 4;
		break;
	}
	f_PosX = E_X;
	FishAnim = f_Count / 17;
	//アニメーション計算
	f_Count = f_Count - 2;
	if (FishAnim == 3) {
		E_FishFlg = TRUE;
	}
	//敵接触後
	if (f_Count <= 0) {
		WaitTime--;
		if (WaitTime <= 0) {
			InitFish();
		}
	}
}

//初期化
void Fish::InitFish() {
	E_Flg = FALSE;
	P_SpawnFlg = FALSE;
	E_SpawnFlg = FALSE;
	P_FishFlg = FALSE;
	TurnFlg = FALSE;
	f_PosY = 400;
	Target = 0;
	f_Count = 120;
	WaitTime = 51;
}

//魚に食べられたときプレイヤー用
bool Fish::GetFishFlg() {
	static bool f = P_FishFlg;
	return f;
}

//魚に食べられたとき敵用
bool Fish::E_GetFishFlg() {
	static bool e = E_FishFlg;
	return e;
}

//プレイヤー判定
void Fish::CheckPlayer() {
	P_X = Player::PlayerX;
	P_Y = Player::PlayerY;
	//出現エリア判定
	if (P_Y >= 358 && P_Y <= 460 && P_X >= 135 && P_X <= 479) {
		Count++;
		Second = Count / 60;
		//三秒経過＆魚がいない
		/*３秒後確率抽選。その後FALSEなら１秒ごとに抽選*/
		if (Second >= 3 && P_SpawnFlg == FALSE) {
			FishRand = GetRand(99);
			Count = 0;
			Second = 2;
			//魚出現
			if (FishRand <= 29) {
				//魚の向きを設定（ランダム）
				FishRand = GetRand(1);
				if (FishRand == 1) {
					TurnFlg = TRUE;
				}
				P_SpawnFlg = TRUE;
				P_MoveFish();
			}
		}
		//魚移動
		else if (P_SpawnFlg == TRUE) {
			P_MoveFish();
		}
	}
	//魚出現中にプレイヤーが範囲外に出たとき
	if (P_Y < 358 && P_SpawnFlg == TRUE) {
		//接触後
		if (FishAnim <= 3) {
			P_MoveFish();
		}
		//接触前
		else if (FishAnim >= 4) {
			FishAnim = 5;
			f_PosY = f_PosY + 2;
			if (f_PosY >= 440) {
				InitFish();
			}
		}
	}
	//魚未出現時にプレイヤーが外に出たとき
	else if (P_Y < 358 && P_SpawnFlg == FALSE) {
		//抽選用時間リセット
		Count = 0;
		Second = 0;
	}
}

//エネミー判定
void Fish::CheckEnemy() {
	for (int i = 0; i <= ENEMY_MAX; i++) {
		if (E_Flg == FALSE) {
			E_X = Enemy::EnemyData[i].x;
			E_Y = Enemy::EnemyData[i].y;
			E_Color = Enemy::EnemyData[i].state;
			if (E_Y >= 360 && E_Y <= 460)E_Flg = TRUE;
		}
	}
	//出現エリア判定
	if (E_Y >= 360 && E_Y <= 460) {
		Count++;
		Second = Count / 60;
		//三秒経過＆魚がいない
		/*３秒後確率抽選。その後FALSEなら１秒ごとに抽選*/
		if (Second >= 0 && E_SpawnFlg == FALSE) {
			FishRand = GetRand(99);
			Count = 0;
			Second = 0;
			//魚出現
			if (FishRand <= 99/*29*/) {
				//魚の向きを設定（ランダム）
				FishRand = GetRand(1);
				if (FishRand == 1) {
					TurnFlg = TRUE;
				}
				E_SpawnFlg = TRUE;
				E_MoveFish();
			}
		}
		//魚移動
		else if (E_SpawnFlg == TRUE) {
			E_MoveFish();
		}
	}
	//魚出現中に敵が範囲外に出たとき
	if (E_Y < 358 && E_Y > 460 && E_SpawnFlg == TRUE) {
		//接触後
		if (FishAnim <= 3) {
			E_MoveFish();
		}
		//接触前
		else if (FishAnim >= 4) {
			FishAnim = 5;
			f_PosY = f_PosY + 2;
			if (f_PosY >= 440) {
				InitFish();
			}
		}
	}
	//魚未出現時に敵が外に出たとき
	else if (E_Y < 358 && E_SpawnFlg == FALSE) {
		//抽選用時間リセット
		Count = 0;
		Second = 0;
		}
}

//左向き描画
void Fish::DrawRight() const {
	//魚画像(アニメーション)
	switch (FishAnim) {
	case 6:
		DrawGraph((int)f_PosX, (int)f_PosY, FishImage[0], TRUE);
		break;
	case 5:
		DrawGraph((int)f_PosX, (int)f_PosY, FishImage[1], TRUE);
		break;
	case 4:
		DrawGraph((int)f_PosX, (int)f_PosY, FishImage[2], TRUE);
		break;
	case 3:
		switch (Target) {
		case 0:
			break;
		case 1:
			DrawGraph((int)f_PosX, (int)f_PosY, FishImage[6], TRUE);
			break;
		case 2:	//敵によって画像変更
			DrawTurnGraph((int)f_PosX, (int)f_PosY,FishImage[7],TRUE);
			break;
		case 3:	
			DrawTurnGraph((int)f_PosX, (int)f_PosY,FishImage[8],TRUE);
			break;
		case 4:	
			DrawTurnGraph((int)f_PosX, (int)f_PosY,FishImage[9],TRUE);
			break;
		}
		break;
	case 2:
		DrawGraph((int)f_PosX, (int)f_PosY, FishImage[3], TRUE);
		break;
	case 1:
		DrawGraph((int)f_PosX, (int)f_PosY, FishImage[4], TRUE);
		break;
	case 0:
		DrawGraph((int)f_PosX, (int)f_PosY, FishImage[5], TRUE);
		break;
	}
}

//左向き描画
void Fish::DrawLeft() const {
	switch (FishAnim) {
	case 6:
		DrawTurnGraph((int)f_PosX, (int)f_PosY, FishImage[0], TRUE);
		break;
	case 5:
		DrawTurnGraph((int)f_PosX, (int)f_PosY, FishImage[1], TRUE);
		break;
	case 4:
		DrawTurnGraph((int)f_PosX, (int)f_PosY, FishImage[2], TRUE);
		break;
	case 3:
		switch (Target) {
		case 0:
			break;
		case 1:
			DrawTurnGraph((int)f_PosX, (int)f_PosY, FishImage[6], TRUE);
			break;
		case 2:	//敵によって画像変更
			DrawTurnGraph((int)f_PosX, (int)f_PosY,FishImage[7],TRUE);
			break;
		case 3:	
			DrawTurnGraph((int)f_PosX, (int)f_PosY,FishImage[8],TRUE);
			break;
		case 4:	
			DrawTurnGraph((int)f_PosX, (int)f_PosY,FishImage[9],TRUE);
			break;
		}
		break;
	case 2:
		DrawTurnGraph((int)f_PosX, (int)f_PosY, FishImage[3], TRUE);
		break;
	case 1:
		DrawTurnGraph((int)f_PosX, (int)f_PosY, FishImage[4], TRUE);
		break;
	case 0:
		DrawTurnGraph((int)f_PosX, (int)f_PosY, FishImage[5], TRUE);
		break;
	}
}

