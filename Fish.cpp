#include"Fish.h"
#include"DxLib.h"
#include<math.h>

//コンストラクタ
Fish::Fish() {
	LoadDivGraph("image/Enemy/Enemy_FishAnimation.png",10,5,2,64,64,FishImage);
	WaitTime=0;
	f_PosX=0;
	f_PosY=0;
	Count = 0;
	Second = 0;
	FishRand = 0;
	FishFlg = FALSE;
	f_Count = 120;
	P_X = p.GetPlayerX();
	P_Y = p.GetPlayerY();
	Target = 0;
}

//魚生成
void Fish::Draw() const {
	if (f_Count < 120) {
			//魚画像(アニメーション)
		switch (f_Count / 17) {
		case 6:
			DrawGraph(f_PosX, f_PosY, FishImage[0], TRUE);
			break;
		case 5:
			DrawGraph(f_PosX, f_PosY, FishImage[1], TRUE);
			break;
		case 4:
			DrawGraph(f_PosX, f_PosY, FishImage[2], TRUE);
			break;
		case 3:
			switch (Target) {
			case 1:
				DrawGraph(f_PosX, f_PosY, FishImage[6], TRUE);
				break;
				//case Enemy:	//敵によって画像変更
				//	DrawGraph(f_PosX,f_PosY,FishImage[EnemyFlg],TRUE);
				//	break;
			}
		case 2:
			DrawGraph(f_PosX, f_PosY, FishImage[4], TRUE);
			break;
		case 1:
			DrawGraph(f_PosX, f_PosY, FishImage[5], TRUE);
			break;
		case 0:
			DrawGraph(f_PosX, f_PosY, FishImage[6], TRUE);
			break;
		}
	}
}

//出現エリア
void Fish::Update() {

	//出現エリア判定
	if (P_Y+64 >= 600 /*|| enemyY > 600*/) {
		while (P_Y+64 >= 600 /*&& enemyY>600*/) {
			Count++;
			Second = Count / 60;
			//三秒経過＆魚がいない
			if (Second >= 3 && FishFlg == FALSE) {
				FishRand = GetRand(99);
				Count = 0;
				Second = 0;
				//魚出現
				if (FishRand <= 29) {
					FishFlg = TRUE;
					MoveFish();
				}
			}
			//魚移動
			if (FishFlg == TRUE) {
				MoveFish();
			}
		}
		//魚出現時＆２秒経過前
		if (FishFlg == TRUE&&f_Count<120) {
			MoveFish();
		}
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
	if (P_Y+64 >= 600) {
		Target = 1;
		f_PosX = P_X+18;
		f_PosY = P_Y+64 - f_Count;
		f_Count = f_Count - 1;
		/*if(f_Count == 0){
			PlayerLife = 0;
		}*/
	}
	//攻撃対象が範囲から出たとき
	else if (P_Y+64 < 600 /*&& enemyY < 600*/) {
		//元に戻る
		f_PosY = f_PosY + f_Count;
		f_Count = f_Count + 1;
		//リセット
		if (f_Count == 120) {
			Target = 0;
			FishFlg = FALSE;
		}
	}
}