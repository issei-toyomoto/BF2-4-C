#include "Enemy.h"
#include "Player.h"
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

	LoadDivGraph("image/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, EnemyImg);  //�摜�ǂݍ���
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
	else
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			enemy[j].x = ENEMY_X;
			enemy[j].y = ENEMY_Y;
			enemy[j].state = 0;
		}

		StartFlg = 0;
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
	DrawFormatString(50, 70, 0xffffff, "Enflg:%d", enemy[0].flg);
	DrawFormatString(50, 100, 0xffffff, "Px:%f", Px);
	DrawFormatString(50, 130, 0xffffff, "Py:%f", Py);

	for (int j = 0; j < ENEMY_MAX; j++)
	{
		// �G�̓����蔻��\��
		if (enemy[j].state == 0)
		{
			if (StartFlg == 0)
			{
				// �X�^�[�g���[�V������
				DrawBox((int)enemy[j].x, (int)enemy[j].y + 25, (int)enemy[j].x + 50, (int)enemy[j].y + 64, 0xffffff, FALSE);
			}
			else
			{
				// �X�^�[�g�ȊO
				DrawBox((int)enemy[j].x + 10, (int)enemy[j].y + 12, (int)enemy[j].x + 55, (int)enemy[j].y + 65, 0xffffff, FALSE);
				
			}
		}
	}

#endif // DEBUG

	for (int j = 0; j < ENEMY_MAX; j++)
	{
		// �G�摜�̕\��
		if (enemy[j].life != 0)
		{
			if (StartFlg == 0)
			{
				// �X�^�[�g���[�V������
				DrawGraph((int)enemy[j].x, (int)enemy[j].y, EnemyImg[enemy[j].flg], TRUE);
			}
			else
			{
				// �X�^�[�g�ȊO
				// ��ʓ�
				if (Px >= enemy[j].x + 10)
				{
					DrawTurnGraph((int)enemy[j].x, (int)enemy[j].y, EnemyImg[enemy[j].flg], TRUE);
				}
				else
				{
					DrawGraph((int)enemy[j].x, (int)enemy[j].y, EnemyImg[enemy[j].flg], TRUE);
				}

				// ��ʊO
				if (enemy[j].x < 0)
				{
					DrawGraph(640 + (int)enemy[j].x, (int)enemy[j].y, EnemyImg[enemy[j].flg], TRUE);
				}
				else if (enemy[j].x > 640 - 64)
				{
					DrawGraph((int)enemy[j].x - 640, (int)enemy[j].y, EnemyImg[enemy[j].flg], TRUE);
				}
			}
		}
	}
}

// �G�̏���������
void Enemy::EnemyInit()
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		enemy[j].x = ENEMY_X + 85 * j;
		enemy[j].y = ENEMY_Y;
	}
}

// �G�̈ړ�����
void Enemy::EnemyMove()
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		// �G��X���W�͈�
		if (enemy[j].x <= 0)
		{
			enemy[j].x = 640;
		}
		else if (enemy[j].x > 640)
		{
			enemy[j].x = 0;
		}

		// �G��Y���W�͈�
		if (enemy[j].y <= -20)
		{
			enemy[j].y = enemy[j].y * 0.8f;
		}
		else if (enemy[j].y > 356)
		{
			enemy[j].speed = enemy[j].speed;
			enemy[j].y = 356;
		}


		// �v���C���[���G���E�ɂ���Ƃ��͉E�Ɉړ�
		if (Px >= enemy[j].x)
		{
			// X���W���Z
			enemy[j].x += enemy[j].speed;

		}
		else
		{
			// �v���C���[���G��荶�ɂ���Ƃ��͍��Ɉړ�
			// X���W���Z
			enemy[j].x -= enemy[j].speed;

		}


		// �v���C���[���G����ɂ���Ƃ��͕��シ��
		if (Py < enemy[j].y)
		{
			EnemyUp();

			// Y���W���Z
			enemy[j].y -= enemy[j].speed;
		}
		else
		{
			EnemyDown();

			// Y���W���Z
			enemy[j].y += enemy[j].speed;

		}
	}
	
}

// �G�̃X�^�[�g����
void Enemy::StartMove()
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		if (StartMotion == 0)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[j].flg = 0;
			}
			else
			{
				enemy[j].flg = 1;
			}
		}
		else if (StartMotion == 1)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[j].flg = 2;
			}
			else
			{
				enemy[j].flg = 3;
			}
		}
		else if (StartMotion == 2)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[j].flg = 4;
			}
			else
			{
				enemy[j].flg = 5;
			}
		}
		else if (StartMotion == 3)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy[j].flg = 6;
			}
			else
			{
				enemy[j].flg = 7;
				StartFlg = 1;
				StartMotion = 0;
			}
		}
	}
}

// �G�̕��ヂ�[�V��������
void Enemy::EnemyUp()
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		// �p�^�p�^��𓮂������[�V����
		if (FPScnt > 0 && FPScnt < 5 || FPScnt > 11 && FPScnt < 15 || FPScnt > 21 && FPScnt < 25)
		{
			enemy[j].flg = 8;
		}
		else if (FPScnt > 31 && FPScnt < 35 || FPScnt > 41 && FPScnt < 45 || FPScnt > 51 && FPScnt < 55)
		{
			enemy[j].flg = 8;
		}
		else
		{
			enemy[j].flg = 9;
		}
	}
}

// �G�̍~�����[�V��������
void Enemy::EnemyDown()
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		// �~�����[�V����
		if (FPScnt > 0 && FPScnt < 20)
		{
			enemy[j].flg = 11;
		}
		else if (FPScnt > 21 && FPScnt < 40)
		{
			enemy[j].flg = 12;
		}
		else
		{
			enemy[j].flg = 10;

			// 10 11 10 12 10 
		}
	}
}

// �G�ƃX�e�[�W�̓����蔻�菈��
void Enemy::StageCollision()
{

}