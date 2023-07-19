#include"DxLib.h"
#include"Fish.h"
#include<math.h>
#include"Player.h"

//ÉRÉìÉXÉgÉâÉNÉ^
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

//ãõê∂ê¨
void Fish::Draw() const {
	if (FishFlg==TRUE) {
		//ãõâÊëú(ÉAÉjÉÅÅ[ÉVÉáÉì)
		switch (FishAnim) {
		case 6://ÇPÇQÇRÅ`ÇPÇOÇU
			DrawGraph((int)f_PosX, (int)f_PosY, FishImage[0], TRUE);
			break;
		case 5://ÇPÇOÇTÅ`ÇWÇW
			DrawGraph((int)f_PosX, (int)f_PosY, FishImage[1], TRUE);
			break;
		case 4://ÇWÇVÅ`ÇVÇO
			DrawGraph((int)f_PosX, (int)f_PosY, FishImage[2], TRUE);
			break;
		case 3://ÇVÇOÅ[ÇPÇV
			switch (Target) {
			case 0:
				break;
			case 1:
				DrawGraph((int)f_PosX, (int)f_PosY, FishImage[6], TRUE);
				break;
				//case Enemy:	//ìGÇ…ÇÊÇ¡ÇƒâÊëúïœçX
				//	DrawGraph(f_PosX,f_PosY,FishImage[EnemyFlg],TRUE);
				//	break;
			}
			break;
		case 2://ÇTÇRÅ`ÇRÇT
			DrawGraph((int)f_PosX, (int)f_PosY, FishImage[3], TRUE);
			break;
		case 1://ÇRÇSÅ`ÇPÇV
			DrawGraph((int)f_PosX, (int)f_PosY, FishImage[4], TRUE);
			break;
		case 0://ÇPÇUÅ`ÇO
			DrawGraph((int)f_PosX, (int)f_PosY, FishImage[5], TRUE);
			break;
		}
	}
}

//èoåªÉGÉäÉA
void Fish::Update() {
	P_X = Player::PlayerX;
	P_Y = Player::PlayerY;
	//èoåªÉGÉäÉAîªíË
	if (P_Y >= 360 && P_X >= 156 && P_X <= 479/*|| enemyY > 600*/) {
		Count++;
		Second = Count / 60;
		//éOïbåoâﬂÅïãõÇ™Ç¢Ç»Ç¢
		/*ÇRïbå„ämó¶íäëIÅBÇªÇÃå„FALSEÇ»ÇÁÇPïbÇ≤Ç∆Ç…íäëI*/
		if (Second >= 3 && FishFlg == FALSE) {
			FishRand = GetRand(99);
			Count = 0;
			Second = 2;
			//ãõèoåª
			if (FishRand <= 99/*29*/) {
				FishFlg = TRUE;
				MoveFish();
			}
		}
		//ãõà⁄ìÆ
		else if (FishFlg == TRUE) {
			MoveFish();
		}
		//ãõèoåªéûÅïÇQïbåoâﬂëO
		//if (FishFlg == TRUE && f_Count<120) {
		//	MoveFish();
		//}
	}
	//ÉvÉåÉCÉÑÅ[Ç™îÕàÕäOÇ…èoÇΩÇ∆Ç´
	if (P_Y < 360 && FishFlg == TRUE) {
		FishAnim == 4;
		f_PosY = f_PosY + 2;
		if (f_PosY >= 410) {
			InitFish();
		}		
	}
}

//ãõà⁄ìÆ
void Fish::MoveFish() {
	//ÉvÉåÉCÉÑÅ[ç¿ïWéÊìæ
	P_X = Player::PlayerX;
	P_Y = Player::PlayerY;
	//çUåÇëŒè€Ç™ìG
	/*if (enemyY > 600) {
		f_PosX = enemyX;
		f_PosY = enemyY - f_Count;
		f_Count = f_Count - 1;
		if(f_Count == 0){
			EnemyLife = 0;
		}
	}*/
	//çUåÇëŒè€Ç™ÉvÉåÉCÉÑÅ[
	if (P_Y >= 360 && P_X >= 156 && P_X <= 479) {
		TargetPlayer();
	}
}

//ÉvÉåÉCÉÑÅ[ÇèPÇ§èàóù
void Fish::TargetPlayer() {
	Target = 1;
	f_PosX = P_X;
	FishAnim = f_Count / 15;
	//ÉAÉjÉÅÅ[ÉVÉáÉìåvéZ
	f_Count = f_Count - 1;
	//ÉvÉåÉCÉÑÅ[ê⁄êGå„
	if (f_Count <= 0) {
		WaitTime--;
		if (WaitTime <= 0) {
			InitFish();
			//PlayerLife=PlayerLife-1;
		}
	}
}

//èâä˙âª
void Fish::InitFish() {
	f_PosY = 400;
	FishFlg = FALSE;
	Target = 0;
	Second = 0;
	f_Count = 120;
	WaitTime = 51;
}