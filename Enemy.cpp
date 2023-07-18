#include "Enemy.h"
#include "Player.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

// �R���X�g���N�^
Enemy::Enemy()
{
	enemy.x = ENEMY_X;    // �G��X���W
	enemy.y = ENEMY_Y;    // �G��Y���W
	enemy.state = 0;      // �G�̏��(0:�s���N 1:�� 2:���F)
	enemy.life = 2;       // �G��HP
	enemy.flg = 0;        // �G�̉摜�ԍ��p
	enemy.speed = 0.4f;   // �G�̈ړ����x
	StartFlg = 0;         // �X�^�[�g��Ԃ����肷��p
	FPScnt = 0;           // FPS�J�E���g
	i = 0;                // �X�^�[�g���A�G�̃��[�V�����Ǘ��p
	Px = Player::PlayerX;
	Py = Player::PlayerY;

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

	Px = Player::PlayerX;
	Py = Player::PlayerY;

	if (StartFlg == 0 && i < 4)
	{
		StartMove();
	}
	else if(StartFlg != 0 && enemy.state == 0)
	{
		EnemyMove();
	}
	else
	{
		enemy.x = ENEMY_X;
		enemy.y = ENEMY_Y;
		enemy.state = 0;
		StartFlg = 0;
	}

	//�P�b��������t���[���J�E���g
	if (FPScnt > 60) 
	{
		FPScnt = 0;
		i++;
	}
}

// �`��̍X�V����������
void Enemy::Draw() const
{
#ifdef _DEBUG
	DrawFormatString(50, 50, 0xffffff, "EnX:%f EnY:%f", enemy.x, enemy.y);
	DrawFormatString(50, 70, 0xffffff, "Enflg:%d", enemy.flg);
	DrawFormatString(50, 100, 0xffffff, "Px:%f", Px);
	DrawFormatString(50, 130, 0xffffff, "Py:%f", Py);

	// �G�̓����蔻��\��
	if (enemy.state == 0)
	{
		if (StartFlg == 0)
		{
			// �X�^�[�g���[�V������
			DrawBox((int)enemy.x, (int)enemy.y + 25, (int)enemy.x + 50, (int)enemy.y + 64, 0xffffff, FALSE);
			DrawBox((int)enemy.x + 85, (int)enemy.y + 25, (int)enemy.x + 50 + 85, (int)enemy.y + 64, 0xffffff, FALSE);
			DrawBox((int)enemy.x + 170, (int)enemy.y + 25, (int)enemy.x + 50 + 170, (int)enemy.y + 64, 0xffffff, FALSE);
		}
		else
		{
			// �X�^�[�g�ȊO
			DrawBox((int)enemy.x + 10, (int)enemy.y + 12, (int)enemy.x + 55, (int)enemy.y + 65, 0xffffff, FALSE);
			/*DrawBox(EnemyX + 95, EnemyY + 10, EnemyX + 55 + 85, EnemyY + 64, 0xffffff, FALSE);
			DrawBox(EnemyX + 180, EnemyY + 10, EnemyX + 55 + 170, EnemyY + 64, 0xffffff, FALSE);*/

		}
	}

#endif // DEBUG

	// �G�摜�̕\��
	if (enemy.life != 0)
	{
		if (StartFlg == 0)
		{
			// �X�^�[�g���[�V������
			DrawGraph((int)enemy.x, (int)enemy.y, EnemyImg[enemy.flg], TRUE);
			DrawGraph((int)enemy.x + 85, (int)enemy.y, EnemyImg[enemy.flg], TRUE);
			DrawGraph((int)enemy.x + 170, (int)enemy.y, EnemyImg[enemy.flg], TRUE);
		}
		else
		{
			// �X�^�[�g�ȊO
			// ��ʓ�
			if (Px >= enemy.x + 10)
			{
				DrawTurnGraph((int)enemy.x, (int)enemy.y, EnemyImg[enemy.flg], TRUE);
			}
			else
			{
				DrawGraph((int)enemy.x, (int)enemy.y, EnemyImg[enemy.flg], TRUE);
			}
			
			// ��ʊO
			if (enemy.x < 0)
			{
				DrawGraph(640 + (int)enemy.x, (int)enemy.y, EnemyImg[enemy.flg], TRUE);
			}
			else if (enemy.x > 640 - 64)
			{
				DrawGraph((int)enemy.x - 640, (int)enemy.y, EnemyImg[enemy.flg], TRUE);
			}
		}
	}
}

// �G�̈ړ�����
void Enemy::EnemyMove()
{

	// �G��X���W�͈�
	if (enemy.x <= 0)
	{
		enemy.x = 640;
	}
	else if (enemy.x > 640)
	{
		enemy.x = 0;
	}

	// �G��Y���W�͈�
	if (enemy.y <= -15)
	{
		enemy.y = enemy.y * 0.8f;
	}
	else if (enemy.y > 356)
	{
		enemy.speed = enemy.speed;
		enemy.y = 356;
	}


	// �v���C���[���G���E�ɂ���Ƃ��͉E�Ɉړ�
	if (Px >= enemy.x)
	{
		// X���W���Z
		enemy.x += enemy.speed;

	}
	else
	{
		// �v���C���[���G��荶�ɂ���Ƃ��͍��Ɉړ�
		// X���W���Z
		enemy.x -= enemy.speed;

	}


	// �v���C���[���G����ɂ���Ƃ��͕��シ��
	if (Py < enemy.y)
	{
		EnemyUp();

		// Y���W���Z
		enemy.y -= enemy.speed;
	}
	else 
	{
		EnemyDown();

		// Y���W���Z
		enemy.y += enemy.speed;

	}

	
}

// �G�̃X�^�[�g����
void Enemy::StartMove()
{
		if (i == 0)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy.flg = 0;
			}
			else
			{
				enemy.flg = 1;
			}
		}
		else if(i == 1)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy.flg = 2;
			}
			else
			{
				enemy.flg = 3;
			}
		}
		else if(i == 2)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy.flg = 4;
			}
			else
			{
				enemy.flg = 5;
			}
		}
		else if (i == 3)
		{
			if (FPScnt > 0 && FPScnt < 15 || FPScnt > 31 && FPScnt < 45)
			{
				enemy.flg = 6;
			}
			else
			{
				enemy.flg = 7;
				StartFlg = 1;
				i = 0;
			}
		}
}

// �G�̕��ヂ�[�V��������
void Enemy::EnemyUp()
{
	// �p�^�p�^��𓮂������[�V����
	if (FPScnt > 0 && FPScnt < 5 || FPScnt > 11 && FPScnt < 15 || FPScnt > 21 && FPScnt < 25)
	{
		enemy.flg = 8;
	}
	else if (FPScnt > 31 && FPScnt < 35 || FPScnt > 41 && FPScnt < 45 || FPScnt > 51 && FPScnt < 55)
	{
		enemy.flg = 8;
	}
	else
	{
		enemy.flg = 9;
	}
}

// �G�̍~�����[�V��������
void Enemy::EnemyDown()
{
	// �~�����[�V����
	if (FPScnt > 6 && FPScnt < 10 || FPScnt > 26 && FPScnt < 30 || FPScnt > 46 && FPScnt < 50)
	{
		enemy.flg = 11;
	}
	else if (FPScnt > 16 && FPScnt < 20 || FPScnt > 36 && FPScnt < 40 || FPScnt > 56 && FPScnt < 60)
	{
		enemy.flg = 12;
	}
	else
	{
		enemy.flg = 10;

		// 10 11 10 12 10 
	}
}

// �G�ƃX�e�[�W�̓����蔻�菈��
void Enemy::EnemyCollision()
{

}