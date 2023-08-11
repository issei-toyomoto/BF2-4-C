#include"DxLib.h"
#include"Fish.h"
#include<math.h>
#include"Player.h"
#include"Enemy.h"

bool Fish::P_FishFlg;
bool Fish::E_FishFlg;

//�R���X�g���N�^
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

//������
void Fish::Draw() const {
	if (P_SpawnFlg==TRUE||E_SpawnFlg) {
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
	CheckPlayer();
	if (E_SpawnFlg == FALSE) {
		CheckEnemy();
	}
}

//���ړ�(�v���C���[)
void Fish::P_MoveFish() {
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

//���ړ�(�G)
void Fish::E_MoveFish() {
	//�U���Ώۂ��G
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
	//�A�j���[�V�����v�Z
	f_Count = f_Count - 2;
	if (FishAnim == 3) {
		E_FishFlg = TRUE;
	}
	//�G�ڐG��
	if (f_Count <= 0) {
		WaitTime--;
		if (WaitTime <= 0) {
			InitFish();
		}
	}
}

//������
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

//���ɐH�ׂ�ꂽ�Ƃ��v���C���[�p
bool Fish::GetFishFlg() {
	static bool f = P_FishFlg;
	return f;
}

//���ɐH�ׂ�ꂽ�Ƃ��G�p
bool Fish::E_GetFishFlg() {
	static bool e = E_FishFlg;
	return e;
}

//�v���C���[����
void Fish::CheckPlayer() {
	P_X = Player::PlayerX;
	P_Y = Player::PlayerY;
	//�o���G���A����
	if (P_Y >= 358 && P_Y <= 460 && P_X >= 135 && P_X <= 479) {
		Count++;
		Second = Count / 60;
		//�O�b�o�߁��������Ȃ�
		/*�R�b��m�����I�B���̌�FALSE�Ȃ�P�b���Ƃɒ��I*/
		if (Second >= 3 && P_SpawnFlg == FALSE) {
			FishRand = GetRand(99);
			Count = 0;
			Second = 2;
			//���o��
			if (FishRand <= 29) {
				//���̌�����ݒ�i�����_���j
				FishRand = GetRand(1);
				if (FishRand == 1) {
					TurnFlg = TRUE;
				}
				P_SpawnFlg = TRUE;
				P_MoveFish();
			}
		}
		//���ړ�
		else if (P_SpawnFlg == TRUE) {
			P_MoveFish();
		}
	}
	//���o�����Ƀv���C���[���͈͊O�ɏo���Ƃ�
	if (P_Y < 358 && P_SpawnFlg == TRUE) {
		//�ڐG��
		if (FishAnim <= 3) {
			P_MoveFish();
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
	else if (P_Y < 358 && P_SpawnFlg == FALSE) {
		//���I�p���ԃ��Z�b�g
		Count = 0;
		Second = 0;
	}
}

//�G�l�~�[����
void Fish::CheckEnemy() {
	for (int i = 0; i <= ENEMY_MAX; i++) {
		if (E_Flg == FALSE) {
			E_X = Enemy::EnemyData[i].x;
			E_Y = Enemy::EnemyData[i].y;
			E_Color = Enemy::EnemyData[i].state;
			if (E_Y >= 360 && E_Y <= 460)E_Flg = TRUE;
		}
	}
	//�o���G���A����
	if (E_Y >= 360 && E_Y <= 460) {
		Count++;
		Second = Count / 60;
		//�O�b�o�߁��������Ȃ�
		/*�R�b��m�����I�B���̌�FALSE�Ȃ�P�b���Ƃɒ��I*/
		if (Second >= 0 && E_SpawnFlg == FALSE) {
			FishRand = GetRand(99);
			Count = 0;
			Second = 0;
			//���o��
			if (FishRand <= 99/*29*/) {
				//���̌�����ݒ�i�����_���j
				FishRand = GetRand(1);
				if (FishRand == 1) {
					TurnFlg = TRUE;
				}
				E_SpawnFlg = TRUE;
				E_MoveFish();
			}
		}
		//���ړ�
		else if (E_SpawnFlg == TRUE) {
			E_MoveFish();
		}
	}
	//���o�����ɓG���͈͊O�ɏo���Ƃ�
	if (E_Y < 358 && E_Y > 460 && E_SpawnFlg == TRUE) {
		//�ڐG��
		if (FishAnim <= 3) {
			E_MoveFish();
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
	//�����o�����ɓG���O�ɏo���Ƃ�
	else if (E_Y < 358 && E_SpawnFlg == FALSE) {
		//���I�p���ԃ��Z�b�g
		Count = 0;
		Second = 0;
		}
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
		case 2:	//�G�ɂ���ĉ摜�ύX
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
		case 2:	//�G�ɂ���ĉ摜�ύX
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

