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
	SpawnFlg = FALSE;
	f_Count = 120;
	P_X = Player::PlayerX;
	P_Y = Player::PlayerY;
	Target = 0;
	FishAnim = 0;
	WaitTime = 51;
	P_FishFlg = FALSE;
	TurnFlg = FALSE;
}

//������
void Fish::Draw() const {
	if (SpawnFlg==TRUE) {
		//���摜(�A�j���[�V����)
		if (TurnFlg == FALSE) {
			DrawLeft();
		}
		else if (TurnFlg == TRUE) {
			DrawRight();
		}
	}
}

//�o���G���A
void Fish::Update() {
	P_X = Player::PlayerX;
	P_Y = Player::PlayerY;
	//�o���G���A����
	if (P_Y >= 358 && P_X >= 135 && P_X <= 479/*|| enemyY > 600*/) {
		Count++;
		Second = Count / 60;
		//�O�b�o�߁��������Ȃ�
		/*�R�b��m�����I�B���̌�FALSE�Ȃ�P�b���Ƃɒ��I*/
		if (Second >= 3 && SpawnFlg == FALSE) {
			FishRand = GetRand(99);
			Count = 0;
			Second = 2;
			//���o��
			if (FishRand <= 99/*29*/) {
				FishRand = GetRand(1);
				if (FishRand == 1) {
					
				}
				SpawnFlg = TRUE;
				MoveFish();
			}
		}
		//���ړ�
		else if (SpawnFlg == TRUE) {
			MoveFish();
		}
	}
	//���o�����Ƀv���C���[���͈͊O�ɏo���Ƃ�
	if (P_Y < 358 && SpawnFlg == TRUE) {
		//�ڐG��
		if (FishAnim <= 3) {
			MoveFish();
		}
		//�ڐG�O
		else if (FishAnim >= 4) {
			FishAnim = 5;
			f_PosY = f_PosY + 2;
			if (f_PosY >= 440) {
				InitFish();
			}
		}
	}
	//�����o�����Ƀv���C���[���O�ɏo���Ƃ�
	else if (P_Y < 358 && SpawnFlg == FALSE) {
		//���I�p���ԃ��Z�b�g
		Count = 0;
		Second = 0;
	}
}

//���ړ�
void Fish::MoveFish() {
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
	if (P_Y >= 358 && P_X >= 135 && P_X <= 479 || FishAnim <= 3) {
		TargetPlayer();
	}
}

//�v���C���[���P������
void Fish::TargetPlayer() {
	Target = 1;
	f_PosX = P_X;
	FishAnim = f_Count / 17;
	//�A�j���[�V�����v�Z
	f_Count = f_Count - 2;
	if (FishAnim == 3) {
		P_FishFlg = TRUE;
	}
	//�v���C���[�ڐG��
	if (f_Count <= 0) {
		WaitTime--;
		if (WaitTime <= 0) {
			InitFish();
		}
	}
}

//�G���P������
void Fish::TargetEnemy() {

}

//������
void Fish::InitFish() {
	SpawnFlg = FALSE;
	P_FishFlg = FALSE;
	TurnFlg = FALSE;
	f_PosY = 400;
	Target = 0;
	Second = 0;
	f_Count = 120;
	WaitTime = 51;
}

//���ɐH�ׂ�ꂽ�Ƃ��v���C���[�p
bool Fish::GetFishFlg() {
	static bool f = P_FishFlg;
	return f;
}

//�������`��
void Fish::DrawRight() const {
	//���摜(�A�j���[�V����)
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
			//case Enemy:	//�G�ɂ���ĉ摜�ύX
			//	DrawTurnGraph(f_PosX,f_PosY,FishImage[EnemyFlg],TRUE);
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

//�������`��
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
			//case Enemy:	//�G�ɂ���ĉ摜�ύX
			//	DrawGraph(f_PosX,f_PosY,FishImage[EnemyFlg],TRUE);
			//	break;
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

