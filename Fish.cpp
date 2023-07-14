#include"DxLib.h"
#include"Fish.h"
#include<math.h>

//�R���X�g���N�^
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
	FishAnim = 0;
}

//������
void Fish::Draw() const {
	if (FishFlg==TRUE) {
		//���摜(�A�j���[�V����)
		switch (FishAnim) {
		case 5:
			DrawGraph((int)P_X, (int)P_Y, FishImage[0], TRUE);
			break;
		case 4:
			DrawGraph((int)P_X, (int)P_Y, FishImage[1], TRUE);
			break;
		case 3:
			DrawGraph((int)P_X, (int)P_Y, FishImage[2], TRUE);
			break;
		case 2:
			switch (Target) {
			case 1:
				DrawGraph((int)P_X, (int)P_Y, FishImage[6], TRUE);
				break;
				//case Enemy:	//�G�ɂ���ĉ摜�ύX
				//	DrawGraph(f_PosX,f_PosY,FishImage[EnemyFlg],TRUE);
				//	break;
			}
		case 1:
			DrawGraph((int)P_X, (int)P_Y, FishImage[4], TRUE);
			break;
		case 0:
			DrawGraph((int)P_X, (int)P_Y, FishImage[5], TRUE);
			break;
		}
	}
}

//�o���G���A
void Fish::Update() {

	P_X = p.GetPlayerX();
	P_Y = p.GetPlayerY();
	//�o���G���A����
	if (P_Y+64.0f >= 360 /*|| enemyY > 600*/) {
		Count++;
		Second = Count / 60;
		//�O�b�o�߁��������Ȃ�
		if (Second >= 3 && FishFlg == FALSE) {
			FishRand = GetRand(99);
			Count = 0;
			Second = 2;
			//���o��
			if (FishRand <= 29) {
				FishFlg = TRUE;
				MoveFish();
			}
		}
		//���ړ�
		if (FishFlg == TRUE) {
			MoveFish();
		}
		//���o�������Q�b�o�ߑO
		if (FishFlg == TRUE&&f_Count<120) {
			MoveFish();
		}
	}
}

//���ړ�
void Fish::MoveFish() {

	//�U���Ώۂ��G
	/*if (enemyY > 600) {
		f_PosX = enemyX;
		f_PosY = enemyY - f_Count;
		f_Count = f_Count - 1;
		if(f_Count == 0){
			EnemyLife = 0;
		}
	}*/
	//�U���Ώۂ��v���C���[
	if (P_Y+64.0f >= 360) {
		Target = 1;
		FishAnim = f_Count / 17;
		f_PosX = P_X + 18.0f;
		f_PosY = P_Y + 64.0f - f_Count;
		f_Count = f_Count - 1;
		if (f_Count == 0) {
			f_PosY = f_PosY + 2.0f;
			//PlayerLife = 0;
			if (f_PosY >= 480) {
				FishFlg = FALSE;
				f_Count = 120;
			}
		}
	}
	
	//�U���Ώۂ��͈͂���o���Ƃ�
	else if (P_Y+64.0f < 360.0f /*&& enemyY < 600*/) {
		//���ɖ߂�
		f_PosY = f_PosY + f_Count;
		f_Count = f_Count + 2;
		//���Z�b�g
		if (f_Count >= 120) {
			Target = 0;
			FishFlg = FALSE;
			f_Count = 120;
		}
	}
}