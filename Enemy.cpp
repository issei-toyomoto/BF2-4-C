#include "Enemy.h"
#include "Player.h"
#include "Common.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

// �R���X�g���N�^
Enemy::Enemy()
{
	EnemyInit();

	StartFlg = 0;   // �X�^�[�g��Ԃ����肷��p
	FPScnt = 0;     // FPS�J�E���g
	StartMotion = 0;          // �X�^�[�g���A�G�̃��[�V�����Ǘ��p
	Px = 0;         // �v���C���[��X���W
	Py = 0;         // �v���C���[��Y���W
	HitFlg = 0;
	HitPFlg = 0;

	LoadDivGraph("image/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, EnemyImg[0]);  //�摜�ǂݍ���
	LoadDivGraph("image/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, EnemyImg[1]);  //�摜�ǂݍ���
	LoadDivGraph("image/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, EnemyImg[2]);  //�摜�ǂݍ���
}

// �f�X�g���N�^
Enemy::~Enemy()
{

}

// �`��ȊO�̍X�V����������
void Enemy::Update()
{
	
	FPScnt++;

	// �v���C���[�̍��W�擾
	Px = Player::PlayerX;
	Py = Player::PlayerY;

	if (StartFlg == 0 && StartMotion < 4)
	{
		StartMove();
	}
	else if(StartFlg != 0)
	{
		EnemyMove();		
	}

	//�P�b��������t���[���J�E���g
	if (FPScnt > 60) 
	{
		FPScnt = 0;
		StartMotion++;
	}
}

// �`��̍X�V����������
void Enemy::Draw() const 
{
#ifdef _DEBUG
	DrawFormatString(50, 50, 0xffffff, "EnX:%f EnY:%f", enemy[2].x, enemy[2].y);
	DrawFormatString(50, 70, 0xffffff, "Enflg:%d", enemy[0].life);
	DrawFormatString(50, 90, 0xffffff, "Enflg:%d", enemy[1].life);
	DrawFormatString(50, 110, 0xffffff, "Enflg:%d", enemy[2].life);
	DrawFormatString(130, 70, 0xffffff, "die:%f", enemy[0].die);
	

	//for (int i = 0; i < ENEMY_MAX; i++)
	//{

	//	// �G�̓����蔻��\��
	//	if (enemy[i].state == 0)
	//	{
	//		if (StartFlg == 0)
	//		{
	//			// �X�^�[�g���[�V������
	//			DrawBox((int)enemy[i].x, (int)enemy[i].y + 25, (int)enemy[i].x + 50, (int)enemy[i].y + 64, 0xffffff, FALSE);
	//		}
	//		else
	//		{
	//			// �X�^�[�g�ȊO
	//			//DrawBox((int)enemy[i].x + 10, (int)enemy[i].y + 12, (int)enemy[i].x + 55, (int)enemy[i].y + 65, 0xffffff, FALSE);
	//			
	//			// �v���C���[�Ɠ������Ă�ꍇ�Ԙg�A�������Ă��Ȃ��ꍇ���g
	//			if (HitPFlg == i)
	//			{
	//				DrawBox((int)EnXL[i], (int)EnYL[i], (int)EnXR[i], (int)EnYR[i], 0xff0000, FALSE);
	//			}
	//			else
	//			{
	//				DrawBox((int)EnXL[i], (int)EnYL[i], (int)EnXR[i], (int)EnYR[i], 0xffffff, FALSE);
	//			}
	//		}
	//	}
	//}

#endif // DEBUG

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// �G�摜�̕\��
		if (enemy[i].life != 6)
		{
			if (StartFlg == 0)
			{
				// �X�^�[�g���[�V������
				DrawGraph((int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);
			}
			else
			{
				// �X�^�[�g�ȊO
				// ��ʓ�
				if (enemy[i].direction == 1)
				{
					DrawTurnGraph((int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);
				}
				else
				{
					DrawGraph((int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);
				}

				// ��ʊO
				if (enemy[i].x < 0)
				{
					DrawGraph(640 + (int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);
				}
				else if (enemy[i].x > 640 - 64)
				{
					DrawGraph((int)enemy[i].x - 640, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);
				}
			}
		}
	}
}

// �G�̏���������
void Enemy::EnemyInit()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].x = ENEMY_X + 85 * i;
		enemy[i].y = ENEMY_Y;
		enemy[i].state = 0;
	}
}

// �G�̈ړ�����
void Enemy::EnemyMove()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].life != 0)
		{
			HitStage(i);
			HitFlg = HitEnemy(i);
			HitPFlg = HitPlayer(i);

			// �G��X���W�͈�
			if (enemy[i].x <= 0)
			{
				enemy[i].x = 640;
			}
			else if (enemy[i].x > 640)
			{
				enemy[i].x = 0;
			}

			// �G��Y���W�͈�
			if (enemy[i].y <= -20)
			{
				enemy[i].y = enemy[i].y * 0.8f;
			}
			else if (enemy[i].y > 356)
			{
				enemy[i].speed = enemy[i].speed;
				enemy[i].y = 356;
			}


			if (Px >= enemy[i].x + 50)
			{
				// �v���C���[���G���E�ɂ���Ƃ��͉E�Ɉړ�
				// X���W���Z
				enemy[i].x += enemy[i].speed;
				enemy[i].direction = 1;

			}
			else
			{
				// �v���C���[���G��荶�ɂ���Ƃ��͍��Ɉړ�
				// X���W���Z
				enemy[i].x -= enemy[i].speed;
				enemy[i].direction = 0;

			}


			// �v���C���[���G����ɂ���Ƃ��͕��シ��
			if (Py < enemy[i].y || enemy[i].ground == 1)
			{
				enemy[i].speed = 0.6f;

				EnemyUp(i);

				// Y���W���Z
				enemy[i].y -= enemy[i].speed;
			}
			else
			{
				EnemyDown(i);

				// Y���W���Z
				enemy[i].y += enemy[i].speed;

			}

			enemy[i].ground = 0;
		}
		else
		{
			EnemyDie(i);
		}
	}
	
}

// �G�̃X�^�[�g����
void Enemy::StartMove()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (StartMotion == 0)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[i].flg = 0;
			}
			else
			{
				enemy[i].flg = 1;
			}
		}
		else if (StartMotion == 1)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[i].flg = 2;
			}
			else
			{
				enemy[i].flg = 3;
			}
		}
		else if (StartMotion == 2)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[i].flg = 4;
			}
			else
			{
				enemy[i].flg = 5;
			}
		}
		else if (StartMotion == 3)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[i].flg = 6;
			}
			else
			{
				enemy[i].flg = 7;
				StartFlg = 1;
				StartMotion = 0;
			}
		}
	}
}

// �G�̕��ヂ�[�V��������
void Enemy::EnemyUp(int e)
{
	
	// �p�^�p�^��𓮂������[�V����
	if (FPScnt > 0 && FPScnt < 5 || FPScnt > 11 && FPScnt < 15 || FPScnt > 21 && FPScnt < 25)
	{
		enemy[e].flg = 8;
	}
	else if (FPScnt > 31 && FPScnt < 35 || FPScnt > 41 && FPScnt < 45 || FPScnt > 51 && FPScnt < 55)
	{
		enemy[e].flg = 8;
	}
	else
	{
		enemy[e].flg = 9;
	}
	
}

// �G�̍~�����[�V��������
void Enemy::EnemyDown(int e)
{
	
	// �~�����[�V����
	if (FPScnt > 0 && FPScnt < 20)
	{
		enemy[e].flg = 11;
	}
	else if (FPScnt > 41  && FPScnt < 60 )
	{
		enemy[e].flg = 12;
	}
	else
	{
		enemy[e].flg = 10;

		// 10 11 10 12 10 
	}
	
}

// �G���m�̓����蔻��
int Enemy::HitEnemy(int e)
{
	EnXL[e] = enemy[e].x + 10.0f;
	EnYL[e] = enemy[e].y + 12.0f;
	EnXR[e] = EnXL[e] + 45.0f;
	EnYR[e] = EnYL[e] + 53.0f;

	if (e == 0)
	{
		if (EnXL[e] <= EnXR[e + 1] && EnYL[e] <= EnYR[e + 1] && EnXR[e] >= EnXL[e + 1] && EnYR[e] >= EnYL[e])
		{
			enemy[e].x -= 10.0f;
			return 1;
		}
	}
	else if (e == 1)
	{
		if (EnXL[e] <= EnXR[e + 1] && EnYL[e] <= EnYR[e + 1] && EnXR[e] >= EnXL[e + 1] && EnYR[e] >= EnYL[e])
		{
			enemy[e].x -= 10.0f;
			return 2;
		}
	}
	else if (e == 2)
	{
		if (EnXL[e] <= EnXR[e - 2] && EnYL[e] <= EnYR[e - 2] && EnXR[e] >= EnXL[e - 2] && EnYR[e] >= EnYL[e])
		{
			enemy[e].x -= 10.0f;
			return 3;
		}
	}
	
	return 0;
}

// �G�ƃX�e�[�W�̓����蔻�菈��
void Enemy::HitStage(int e)
{
	int EnXL[ENEMY_MAX] = { 0 }, EnYL[ENEMY_MAX] = { 0 };//����
	int EnXR[ENEMY_MAX] = { 0 }, EnYR[ENEMY_MAX] = { 0 };//�E��

	
	EnXL[e] = (int)enemy[e].x + 10;
	EnYL[e] = (int)enemy[e].y + 12;
	EnXR[e] = EnXL[e] + 50;
	EnYR[e] = EnYL[e] + 60;
	

	if (EnXL[e] <= S_Ground_Left_XL && EnYR[e] >= S_Ground_Left_YU)
	{//�����̑�i���ʁj
		enemy[e].ground = 1;
		enemy[e].y -= 0.8f;//�����W���H
	}
	else if (EnXR[e] >= S_Ground_Right_XU && EnYR[e] >= S_Ground_Right_YU) 
	{//�E���̑�i���ʁj
		enemy[e].ground = 1;
		enemy[e].y -= 0.8f;
	}
	else if (EnXR[e] >= S_Sky_Ground_0_XU && EnXR[e] <= S_Sky_Ground_0_XU && EnYR[e] >= S_Sky_Ground_0_YU  && EnYL[e] <= S_Sky_Ground_0_YL) 
	{//��̑�̍��i���ʁj
		enemy[e].ground = 1;
		enemy[e].y -= 0.8f;
	}
	else if (EnXL[e] >= S_Sky_Ground_0_XL && EnXL[e] <= S_Sky_Ground_0_XL && EnYR[e] >= S_Sky_Ground_0_YU && EnYL[e] <= S_Sky_Ground_0_YL) 
	{//��̑�̉E�i���ʁj
		enemy[e].ground = 1;
		enemy[e].y -= 0.8f;
	}
	else if (EnYL[e] <= S_Sky_Ground_0_YL && EnYR[e] >= S_Sky_Ground_0_YU)
	{//��̑�i���Ӂj
		if (EnXL[e] <= S_Sky_Ground_0_XL && EnXR[e] >= S_Sky_Ground_0_XU)
		{
			enemy[e].y -= 0.8f;
			//if (VectorY >= 0)
			//{//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɂP����
			//	VectorY += 1.0f;
			//}
		}
	}
	else if (EnYL[e] <= 0)
	{//��ʏ�̓����蔻��
		enemy[e].ground = 1;
		enemy[e].y -= 0.8f;
		//if (VectorY >= 0) 
		//{//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɂP����
		//	VectorY += 1.0f;
		//}
	}
	
}

// �G�ƃv���C���[�̓����蔻��
int Enemy::HitPlayer(int e)
{
	//�v���C���[�̋�`�̍��W
	float PXL, PYL;//����
	float PXR, PYR;//�E��

	PXL = Px + 18;//����X
	PYL = Py + 14;//����Y
	PXR = Px + 40;//�E��X
	PYR = Py+ 64;//�E��Y

	
	EnXL[e] = enemy[e].x + 10.0f;
	EnYL[e] = enemy[e].y + 12.0f;
	EnXR[e] = EnXL[e] + 45.0f;
	EnYR[e] = EnYL[e] + 53.0f;

	
	if (enemy[e].life != 0)
	{
		if (EnXL[e] <= PXR && EnYL[e] <= PYR && EnXR[e] >= PXL && EnYR[e] >= PYL)
		{
			enemy[e].flg = 17;
			// ��
			enemy[e].life -= 1;
			return e;
		}
	}
		
	return 3;
}

// �G�̎��S���[�V��������
void Enemy::EnemyDie(int e)
{
	// �p�^�p�^��𓮂������[�V����
	if (FPScnt > 0 && FPScnt < 4 || FPScnt > 9 && FPScnt < 12 || FPScnt > 17 && FPScnt < 20)
	{
		enemy[e].flg = 13;
	}
	else if (FPScnt > 25 && FPScnt < 28 || FPScnt > 33 && FPScnt < 36 || FPScnt > 41 && FPScnt < 44)
	{
		enemy[e].flg = 13;
	}
	else if (FPScnt > 49 && FPScnt < 52 || FPScnt > 57 && FPScnt < 60)
	{
		enemy[e].flg = 13;
	}
	else
	{
		enemy[e].flg = 14;
	}

	if (enemy[e].die <= 8)
	{
		enemy[e].die++;
		enemy[e].y -= 2.8f;
	}
	else if(enemy[e].die <= 15)
	{
		enemy[e].die++;
	}
	else if(enemy[e].y <= 490.0f)
	{
		enemy[e].y += 3.0f;
	}
}
