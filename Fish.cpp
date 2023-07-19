#include"DxLib.h"
#include"Fish.h"
#include<math.h>
#include"Player.h"

//�R���X�g���N�^
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

//������
void Fish::Draw() const {
	if (FishFlg==TRUE) {
		//���摜(�A�j���[�V����)
		switch (FishAnim) {
		case 6://�P�Q�R�`�P�O�U
			DrawGraph((int)f_PosX, (int)f_PosY, FishImage[0], TRUE);
			break;
		case 5://�P�O�T�`�W�W
			DrawGraph((int)f_PosX, (int)f_PosY, FishImage[1], TRUE);
			break;
		case 4://�W�V�`�V�O
			DrawGraph((int)f_PosX, (int)f_PosY, FishImage[2], TRUE);
			break;
		case 3://�V�O�[�P�V
			switch (Target) {
			case 0:
				break;
			case 1:
				DrawGraph((int)f_PosX, (int)f_PosY, FishImage[6], TRUE);
				break;
				//case Enemy:	//�G�ɂ���ĉ摜�ύX
				//	DrawGraph(f_PosX,f_PosY,FishImage[EnemyFlg],TRUE);
				//	break;
			}
			break;
		case 2://�T�R�`�R�T
			DrawGraph((int)f_PosX, (int)f_PosY, FishImage[3], TRUE);
			break;
		case 1://�R�S�`�P�V
			DrawGraph((int)f_PosX, (int)f_PosY, FishImage[4], TRUE);
			break;
		case 0://�P�U�`�O
			DrawGraph((int)f_PosX, (int)f_PosY, FishImage[5], TRUE);
			break;
		}
	}
}

//�o���G���A
void Fish::Update() {
	P_X = Player::PlayerX;
	P_Y = Player::PlayerY;
	//�o���G���A����
	if (P_Y >= 360 && P_X >= 156 && P_X <= 479/*|| enemyY > 600*/) {
		Count++;
		Second = Count / 60;
		//�O�b�o�߁��������Ȃ�
		/*�R�b��m�����I�B���̌�FALSE�Ȃ�P�b���Ƃɒ��I*/
		if (Second >= 3 && FishFlg == FALSE) {
			FishRand = GetRand(99);
			Count = 0;
			Second = 2;
			//���o��
			if (FishRand <= 99/*29*/) {
				FishFlg = TRUE;
				MoveFish();
			}
		}
		//���ړ�
		else if (FishFlg == TRUE) {
			MoveFish();
		}
		//���o�������Q�b�o�ߑO
		//if (FishFlg == TRUE && f_Count<120) {
		//	MoveFish();
		//}
	}
	//�v���C���[���͈͊O�ɏo���Ƃ�
	if (P_Y < 360 && FishFlg == TRUE) {
		FishAnim == 4;
		f_PosY = f_PosY + 2;
		if (f_PosY >= 410) {
			InitFish();
		}		
	}
}

//���ړ�
void Fish::MoveFish() {
	//�v���C���[���W�擾
	P_X = Player::PlayerX;
	P_Y = Player::PlayerY;
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
	if (P_Y >= 360 && P_X >= 156 && P_X <= 479) {
		TargetPlayer();
	}
}

//�v���C���[���P������
void Fish::TargetPlayer() {
	Target = 1;
	f_PosX = P_X;
	FishAnim = f_Count / 15;
	//�A�j���[�V�����v�Z
	f_Count = f_Count - 1;
	//�v���C���[�ڐG��
	if (f_Count <= 0) {
		WaitTime--;
		if (WaitTime <= 0) {
			InitFish();
			//PlayerLife=PlayerLife-1;
		}
	}
}

//������
void Fish::InitFish() {
	f_PosY = 400;
	FishFlg = FALSE;
	Target = 0;
	Second = 0;
	f_Count = 120;
	WaitTime = 51;
}