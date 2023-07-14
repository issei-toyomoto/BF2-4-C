#include"DxLib.h"
#include"Fish.h"
#include<math.h>

//コンストラクタ
Fish::Fish() {
	LoadDivGraph("image/Enemy/Enemy_FishAnimation.png",10,5,2,64,64,FishImage);
	f_PosX = 150;
	f_PosY = 389;
	Count = 0;
	Second = 0;
	FishRand = 0;
	FishFlg = FALSE;
	f_Count = 120;
	P_X = p.GetPlayerX();
	P_Y = p.GetPlayerY();
	Target = 0;
	FishAnim = 0;
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
	P_X = p.GetPlayerX();
	P_Y = p.GetPlayerY();
	//出現エリア判定
	if (P_Y >= 350 /*|| enemyY > 600*/) {
		Count++;
		Second = Count / 60;
		//三秒経過＆魚がいない
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
		if (FishFlg == TRUE) {
			MoveFish();
		}
		//魚出現時＆２秒経過前
		if (FishFlg == TRUE&&f_Count<120) {
			MoveFish();
		}
	}
	else if (P_Y < 350) {
		FishFlg = FALSE;
		Target = 0;
		Second = 0;
		f_Count = 120;
	}
}

//魚移動
void Fish::MoveFish() {
	P_X = p.GetPlayerX();
	P_Y = p.GetPlayerY();
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
	if (P_Y >= 350) {
		Target = 1;
		FishAnim = f_Count / 17;
		/*f_PosX = P_X;*/
		if (FishAnim == 4) {
			
		}
		else if (FishAnim != 4) {
			f_Count = f_Count - 1;
		}
		if (f_Count <= 0) {
			//PlayerLife = 0;
			FishFlg = FALSE;
			Target = 0;
			Second = 0;
			f_Count = 120;
		}
	}
	else if (P_Y < 350) {
		FishFlg = FALSE;
		Target = 0;
		Second = 0;
		f_Count = 120;
	}
}