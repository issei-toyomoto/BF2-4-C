#include"DxLib.h"
#include"Fish.h"
#include<math.h>
#include"Player.h"

//コンストラクタ
Fish::Fish() {
	LoadDivGraph("image/Enemy/Enemy_FishAnimation.png",10,5,2,64,64,FishImage);
	f_PosX = 150;
	f_PosY = 400;
	Count = 0;
	Second = 0;
	FishRand = 0;
	FishFlg = FALSE;
	f_Count = 120;
	P_X = Player::PlayerX;
	P_Y = Player::PlayerY;
	Target = 0;
	FishAnim = 0;
	WaitTime = 51;
}

//魚生成
void Fish::Draw() const {
	if (FishFlg==TRUE) {
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
				//case Enemy:	//敵によって画像変更
				//	DrawGraph(f_PosX,f_PosY,FishImage[EnemyFlg],TRUE);
				//	break;
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
}

//出現エリア
void Fish::Update() {
	P_X = Player::PlayerX;
	P_Y = Player::PlayerY;
	//出現エリア判定
	if (P_Y >= 358 && P_X >= 135 && P_X <= 479/*|| enemyY > 600*/) {
		Count++;
		Second = Count / 60;
		//三秒経過＆魚がいない
		/*３秒後確率抽選。その後FALSEなら１秒ごとに抽選*/
		if (Second >= 3 && FishFlg == FALSE) {
			FishRand = GetRand(99);
			Count = 0;
			Second = 2;
			//魚出現
			if (FishRand <= 99/*29*/) {
				FishFlg = TRUE;
				MoveFish();
			}
		}
		//魚移動
		else if (FishFlg == TRUE) {
			MoveFish();
		}
	}
	//プレイヤーが範囲外に出たとき
	if (P_Y < 358 && FishFlg == TRUE) {
		if (FishAnim <= 3) {
			MoveFish();
		}
		else if (FishAnim >= 5) {
			FishAnim = 5;
			f_PosY = f_PosY + 2;
			if (f_PosY >= 440) {
				InitFish();
			}
		}		
	}
	else if (P_Y < 358 && FishFlg == FALSE) {
		Count = 0;
		Second = 0;
	}
}

//魚移動
void Fish::MoveFish() {
	//攻撃対象が敵
	/*if (enemyY > 600) {
		f_PosX = enemyX;
		f_PosY = enemyY - f_Count;
		f_Count = f_Count - 1;
		if(f_Count == 0){
			EnemyLife = 0;
		}
	}*/
	//攻撃対象がプレイヤー
	if (P_Y >= 358 && P_X >= 135 && P_X <= 479 || FishAnim <= 3) {
		TargetPlayer();
	}
}

//プレイヤーを襲う処理
void Fish::TargetPlayer() {
	Target = 1;
	f_PosX = P_X;
	FishAnim = f_Count / 17;
	//アニメーション計算
	f_Count = f_Count - 2;
	//プレイヤー接触後
	if (f_Count <= 0) {
		WaitTime--;
		if (WaitTime <= 0) {
			InitFish();
			//PlayerLife=PlayerLife-1;
		}
	}
}

//敵を襲う処理
void Fish::TargetEnemy() {

}

//初期化
void Fish::InitFish() {
	FishFlg = FALSE;
	f_PosY = 400;
	Target = 0;
	Second = 0;
	f_Count = 120;
	WaitTime = 51;
}