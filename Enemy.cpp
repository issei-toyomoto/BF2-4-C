#include "Enemy.h"
#include "Player.h"
#include "Common.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "stdlib.h"
#include<time.h>
#include "InputKey.h"

int Enemy::HitPFlg = 0;

// �R���X�g���N�^
Enemy::Enemy()
{
	EnemyInit();

	StartFlg = 0;   // �X�^�[�g��Ԃ����肷��p
	Fcnt = 0;     // FPS�J�E���g
	StartMotion = 0;          // �X�^�[�g���A�G�̃��[�V�����Ǘ��p
	Px = 0;         // �v���C���[��X���W
	Py = 0;         // �v���C���[��Y���W
	HitFlg = 0;
	HitPeFlg = 0;
	UpCnt = 0;
	DownCnt = 0;
	NowStage = 0;
	
	LoadDivGraph("image/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, EnemyImg[0]);  //�摜�ǂݍ���(�s���N)
	LoadDivGraph("image/Enemy/Enemy_G_Animation.png", 18, 6, 3, 64, 64, EnemyImg[1]);  //�摜�ǂݍ���(�݂ǂ�)
	LoadDivGraph("image/Enemy/Enemy_R_Animation.png", 18, 6, 3, 64, 64, EnemyImg[2]);  //�摜�ǂݍ���(������)
}

// �f�X�g���N�^
Enemy::~Enemy()
{

}

// �`��ȊO�̍X�V����������
void Enemy::Update(int nowstage)
{
	
	Fcnt++;

	NowStage = nowstage;

	// �v���C���[�̍��W�擾
	Px = Player::PlayerX;
	Py = Player::PlayerY;

	srand(time(NULL));

	if (StartFlg == 0 && StartMotion < 4)
	{
		StartMove();
	}
	else
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemy[i].start == 1 && enemy[i].sm < 4)
			{
				StartMove(i);
			}
			else
			{
				if (enemy[i].life == 2)
				{
					enemy[i].ran = rand() % 2 + 1;

					HitStage(i);
					HitFlg = HitEnemy(i);
					HitPeFlg = HitPlayer(i);
					EnemyMove(i);

					// �G��X���W�͈�
					if (enemy[i].x <= 0.0f)
					{
						enemy[i].x = 640.0f;
					}
					else if (enemy[i].x > 640.0f)
					{
						enemy[i].x = 0.0f;
					}

					// �G��Y���W�͈�
					if (enemy[i].y < -19.0f)
					{
						enemy[i].y = -5.0f;
					}
					else if (enemy[i].y > 356.0f)
					{
						enemy[i].y = 356.0f;
					}
				}
				else if (enemy[i].life == 1)
				{
					EnemyPara(i);
				}
				else
				{
					EnemyDie(i);
				}

			}
		}
	}
	

	//�P�b��������t���[���J�E���g
	if (Fcnt > 60) 
	{
		Fcnt = 0;

		if (StartFlg == 0)
		{
			StartMotion++;
		}

		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (enemy[i].start == 1)
			{
				enemy[i].sm++;
			}
		}
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
	DrawFormatString(130, 70, 0xffffff, "Hit:%d", HitPFlg);
	DrawFormatString(130, 90, 0xffffff, "Vx:%f", enemy[0].vecx);
	DrawFormatString(130, 110, 0xffffff, "Vy:%f", enemy[0].vecy);

	

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].life == 2)
		{
			// �G�̓����蔻��\��
			if (enemy[i].state != 3)
			{
				if (StartFlg == 0)
				{
					// �X�^�[�g���[�V������
					DrawBox((int)enemy[i].x, (int)enemy[i].y + 25, (int)enemy[i].x + 50, (int)enemy[i].y + 64, 0xffffff, FALSE);
				}
				else
				{
					// �X�^�[�g�ȊO
					//DrawBox((int)enemy[i].x + 10, (int)enemy[i].y + 12, (int)enemy[i].x + 55, (int)enemy[i].y + 65, 0xffffff, FALSE);

					// �v���C���[�Ɠ������Ă�ꍇ�Ԙg�A�������Ă��Ȃ��ꍇ���g
					if (HitPeFlg == i)
					{
						DrawBox((int)EnXL[i], (int)EnYL[i], (int)EnXR[i], (int)EnYR[i], 0xff0000, FALSE);
					}
					else
					{
						// ���D����̓G�͈̔́i���j
						DrawBox((int)EnXL[i], (int)EnYL[i], (int)EnXR[i], (int)EnYR[i], 0xffffff, FALSE);
						// ���D�����̓G�͈̔́i�΁j
						DrawBox((int)EnXL[i], (int)EnYL[i] + 20, (int)EnXR[i], (int)EnYR[i], 0x00ff00, FALSE);
						// ���D�����̓G�͈̔͂̔����i�j
						DrawBox((int)EnXL[i], (int)EnYL[i]+36, (int)EnXR[i], (int)EnYR[i], 0x0000ff, FALSE);
					}
				}
			}
		}
		else if (enemy[i].life == 1)
		{
		}
	}

#endif // DEBUG

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// �G�摜�̕\��
		if (enemy[i].life == 2)
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
				if (enemy[i].direction < 1)
				{
					DrawGraph((int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);
				}
				else
				{
					DrawTurnGraph((int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);
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
		else
		{
			// �X�^�[�g�ȊO
			// ��ʓ�
			DrawGraph((int)enemy[i].x, (int)enemy[i].y, EnemyImg[enemy[i].state][enemy[i].flg], TRUE);

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

// �G�̏���������
void Enemy::EnemyInit()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].x = ENEMY_X + 85.0f * i;
		enemy[i].y = ENEMY_Y;
		enemy[i].state = 0;
		enemy[i].life = 2;
		enemy[i].sm = 0;
	}
}

// �G�̈ړ�����
void Enemy::EnemyMove(int i)
{
	// �v���C���[���G���E�ɂ���Ƃ��͉E�Ɉړ�����
	if (Px >= enemy[i].x)
	{
		EnemyRight(i);

		// �v���C���[���G����ɂ���Ƃ��͕��シ��
		if (Py < enemy[i].y || enemy[i].ground == 1)
		{
			EnemyUp(i);
		}
		else
		{
			// �v���C���[���G��艺�ɂ���Ƃ��͍~������
			EnemyDown(i);
		}

	}
	else
	{
		// �v���C���[���G��荶�ɂ���Ƃ��͍��Ɉړ�����
		EnemyLeft(i);

		// �v���C���[���G����ɂ���Ƃ��͕��シ��
		if (Py < enemy[i].y || enemy[i].ground == 1)
		{
			EnemyUp(i);
		}
		else
		{
			// �v���C���[���G��艺�ɂ���Ƃ��͍~������
			EnemyDown(i);
		}
	}

	enemy[i].ground = 0;	
}

void Enemy::StartMove()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].life != 0)
		{
			HitPeFlg = HitStart(i);

			if (StartMotion == 0)
			{
				if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
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
				if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
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
				if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
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
				if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
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
		else
		{
			EnemyDie(i);
		}
	}
}

// �G�̃X�^�[�g����
void Enemy::StartMove(int i)
{
	if (enemy[i].life != 0)
	{
		HitPeFlg = HitStart(i);

		if (enemy[i].sm == 0)
		{
			if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
			{
				enemy[i].flg = 0;
			}
			else
			{
				enemy[i].flg = 1;
			}
		}
		else if (enemy[i].sm == 1)
		{
			if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
			{
				enemy[i].flg = 2;
			}
			else
			{
				enemy[i].flg = 3;
			}
		}
		else if (enemy[i].sm == 2)
		{
			if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
			{
				enemy[i].flg = 4;
			}
			else
			{
				enemy[i].flg = 5;
			}
		}
		else if (enemy[i].sm == 3)
		{
			if (Fcnt > 0 && Fcnt < 15 || Fcnt > 31 && Fcnt < 45)
			{
				enemy[i].flg = 6;
			}
			else
			{
				enemy[i].flg = 7;

				if (enemy[i].state != 2)
				{
					enemy[i].state++;
				}

				enemy[i].okballoon = 0;
				enemy[i].start = 0;
				enemy[i].sm = 0;
			}
		}
	}
	else
	{
		EnemyDie(i);
	}
	
}

// �G�̕��ヂ�[�V��������
void Enemy::EnemyUp(int e)
{
	// �p�^�p�^��𓮂������[�V����
	if (Fcnt > 0 && Fcnt < 5 || Fcnt > 11 && Fcnt < 15 || Fcnt > 21 && Fcnt < 25)
	{
		enemy[e].flg = 8;
	}
	else if (Fcnt > 31 && Fcnt < 35 || Fcnt > 41 && Fcnt < 45 || Fcnt > 51 && Fcnt < 55)
	{
		enemy[e].flg = 8;
	}
	else
	{
		enemy[e].flg = 9;
	}

	enemy[e].vecy += 0.05f;

	if (enemy[e].vecy >= 1.0f)
	{
		enemy[e].vecy = 1.0f;
	}

	enemy[e].vecy *= 0.95f;

	enemy[e].y -= enemy[e].vecy;
}

// �G�̍~�����[�V��������
void Enemy::EnemyDown(int e)
{
	// �~�����[�V����
	if (enemy[e].ran == 2)
	{
		if (Fcnt > 0 && Fcnt < 20)
		{
			enemy[e].flg = 11;
		}
		else if (Fcnt > 41 && Fcnt < 60)
		{
			enemy[e].flg = 12;
		}
		else
		{
			enemy[e].flg = 10;

			// 10 11 10 12 10 
		}
	}
	
	enemy[e].vecy += 0.06f;

	if (enemy[e].vecy >= 1.5f)
	{
		enemy[e].vecy = 1.5f;
	}

	enemy[e].vecy *= 0.95f;

	enemy[e].y += enemy[e].vecy;

	if (enemy[e].ran == 1)
	{
		// �p�^�p�^��𓮂������[�V����
		if (Fcnt > 0 && Fcnt < 5 || Fcnt > 11 && Fcnt < 15 || Fcnt > 21 && Fcnt < 25)
		{
			enemy[e].flg = 8;
		}
		else if (Fcnt > 31 && Fcnt < 35 || Fcnt > 41 && Fcnt < 45 || Fcnt > 51 && Fcnt < 55)
		{
			enemy[e].flg = 8;
		}
		else
		{
			enemy[e].flg = 9;
		}

		enemy[e].vecy += 0.05f;

		if (enemy[e].vecy >= 1.0f)
		{
			enemy[e].vecy = 1.0f;
		}

		enemy[e].vecy *= 0.95f;

		enemy[e].y -= enemy[e].vecy;
	}
	
}

// �G�̍��ړ�����
void Enemy::EnemyLeft(int e)
{
	// �v���C���[���G��荶�ɂ���Ƃ��͍��Ɉړ�
    // X���W���Z
	enemy[e].direction = 0;

	enemy[e].vecx += 0.05f;

	if (enemy[e].vecx >= 1.0f)
	{
		enemy[e].vecx = 1.0f;
	}

	enemy[e].vecx *= 0.95f;

	enemy[e].x -= enemy[e].vecx;
}

// �G�̉E�ړ�����
void Enemy::EnemyRight(int e)
{
	// �v���C���[���G���E�ɂ���Ƃ��͉E�Ɉړ�
	// X���W���Z
	enemy[e].direction = 1;

	enemy[e].vecx += 0.05f;

	if (enemy[e].vecx >= 1.0f)
	{
		enemy[e].vecx = 1.0f;
	}

	enemy[e].vecx *= 0.95f;

	enemy[e].x += enemy[e].vecx;

}

// �G�̃p���V���[�g����
void Enemy::EnemyPara(int e)
{
	float amplitude = 0.85f;  // �h��̐U��
	float frequency = 0.9f;   // �h��̎��g��

	if (enemy[e].para <= 1)
	{
		enemy[e].flg = 15;
		enemy[e].para++;
	}
	else if(enemy[e].para <= 4)
	{
		enemy[e].flg = 16;
		enemy[e].para++;
	}
	else
	{
		enemy[e].para = 5;
		enemy[e].flg = 17;
		
		enemy[e].x += amplitude * sin(frequency * GetNowCount() / 1000.0f);

		enemy[e].y += 0.3f;

		// �p���V���[�g��Ԋm�F���R�����g�A�E�g
		/*HitPeFlg = HitPlayer(e);*/

		HitStage(e);

		// �n�ʂɒ������畗�D��c��܂���
		if (enemy[e].ground == 1)
		{
			enemy[e].life = 2;
			enemy[e].start = 1;
		}
	}
}

// �G�̎��S���[�V��������
void Enemy::EnemyDie(int e)
{
	// �p�^�p�^��𓮂������[�V����
	if (Fcnt > 0 && Fcnt < 4 || Fcnt > 9 && Fcnt < 12 || Fcnt > 17 && Fcnt < 20)
	{
		enemy[e].flg = 13;
	}
	else if (Fcnt > 25 && Fcnt < 28 || Fcnt > 33 && Fcnt < 36 || Fcnt > 41 && Fcnt < 44)
	{
		enemy[e].flg = 13;
	}
	else if (Fcnt > 49 && Fcnt < 52 || Fcnt > 57 && Fcnt < 60)
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
	else if (enemy[e].die <= 15)
	{
		enemy[e].die++;
	}
	else if (enemy[e].y <= 490.0f)
	{
		enemy[e].y += 3.0f;
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
		if (enemy[e + 1].life != 0)
		{
			if (EnXL[e] <= EnXR[e + 1] && EnYL[e] <= EnYR[e + 1] && EnXR[e] >= EnXL[e + 1] && EnYR[e] >= EnYL[e])
			{
				enemy[e].x -= 10.0f;
				return 1;
			}
		}
	}
	else if (e == 1)
	{
		if (enemy[e + 1].life != 0)
		{
			if (EnXL[e] <= EnXR[e + 1] && EnYL[e] <= EnYR[e + 1] && EnXR[e] >= EnXL[e + 1] && EnYR[e] >= EnYL[e])
			{
				enemy[e].x -= 10.0f;
				return 2;
			}
		}
	}
	else if (e == 2)
	{
		if (enemy[e - 2].life != 0)
		{
			if (EnXL[e] <= EnXR[e - 2] && EnYL[e] <= EnYR[e - 2] && EnXR[e] >= EnXL[e - 2] && EnYR[e] >= EnYL[e])
			{
				enemy[e].x -= 10.0f;
				return 3;
			}
		}
	}
	
	return 0;
}

// �G�ƃX�e�[�W�̓����蔻�菈��
void Enemy::HitStage(int e)
{
	EnXL[e] = enemy[e].x + 10.0f;//����X
	EnYL[e] = enemy[e].y + 12.0f;//����Y
	EnXR[e] = EnXL[e] + 45.0f;//�E��X
	EnYR[e] = EnYL[e] + 53.0f;//�E��Y

	if (NowStage == 1) {//***************�@�P�X�e�[�W�@***************//
/*******************************************************************************************************************************/
		//���ʂ̓����蔻��//
/*******************************************************************************************************************************/
		if (enemy[e].ground == 0) {
			if (EnXL[e] <= S_Ground_Left_XL && EnYR[e] >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}

			if (EnXR[e] >= S_Ground_Right_XU && EnYR[e] >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}

			if (EnYR[e] >= S_Sky_Ground_0_YU + PlusPx && EnYL[e] <= S_Sky_Ground_0_YL - PlusPx) {//��̑�i���ʁj
				if (EnXL[e] <= S_Sky_Ground_0_XL + PlusPx && EnXR[e] >= S_Sky_Ground_0_XL) {//��̑�̉E
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						enemy[e].vecx += 0.9f;
					}
				}
				else if (EnXR[e] >= S_Sky_Ground_0_XU - PlusPx && EnXR[e] <= S_Sky_Ground_0_XU) {//��̑�̍�
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
						enemy[e].vecx -= 0.9f;
					}
				}
			}
			/*******************************************************************************************************************************/
					//���ӂ̓����蔻��//
			/*******************************************************************************************************************************/
			if (EnYL[e] <= S_Sky_Ground_0_YL - PlusPx && EnYR[e] >= S_Sky_Ground_0_YL) {//��̑�i���Ӂj
				if (EnXL[e] <= S_Sky_Ground_0_XL && EnXR[e] >= S_Sky_Ground_0_XU) {
					enemy[e].vecy *= -COR;
					if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						enemy[e].vecy += 0.9f;
					}
				}
			}

			if (EnYL[e] <= 0) {//��ʏ�̓����蔻��
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		/*******************************************************************************************************************************/
				//��ӂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (EnYR[e] >= S_Ground_Left_YU && EnYR[e] <= S_Ground_Left_YU + PlusPx && EnXL[e] <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Ground_Right_YU && EnYR[e] <= S_Ground_Right_YU + PlusPx && EnXR[e] >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Sky_Ground_0_YU && EnYR[e] <= S_Sky_Ground_0_YU + PlusPx && EnXL[e] <= S_Sky_Ground_0_XL && EnXR[e] >= S_Sky_Ground_0_XU) {//�����Ă��钆���̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else {
			enemy[e].ground = 0;
		}
	}
	else if (NowStage == 2) {//***************�@�Q�X�e�[�W�@***************//
/*******************************************************************************************************************************/
		//���ʂ̓����蔻��//
/*******************************************************************************************************************************/
		if (enemy[e].ground == 0) {
			if (EnXL[e] <= S_Ground_Left_XL && EnYR[e] >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}

			if (EnXR[e] >= S_Ground_Right_XU && EnYR[e] >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}

			if (EnYR[e] >= S_Sky_Ground_0_YU + PlusPx && EnYL[e] <= S_Sky_Ground_0_YL - PlusPx) {//��̑�i���ʁj
				if (EnXL[e] <= S_Sky_Ground_0_XL + PlusPx && EnXR[e] >= S_Sky_Ground_0_XL) {//��̑�̉E
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						enemy[e].vecx += 0.9f;
					}
				}
				else if (EnXR[e] >= S_Sky_Ground_0_XU - PlusPx && EnXR[e] <= S_Sky_Ground_0_XU) {//��̑�̍�
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
						enemy[e].vecx -= 0.9f;
					}
				}
			}

			if (EnYR[e] >= S2_Sky_Ground_0_YU + PlusPx && EnYL[e] <= S2_Sky_Ground_0_YL - PlusPx) {//����̑�i���ʁj
				if (EnXL[e] <= S2_Sky_Ground_0_XL + PlusPx && EnXR[e] >= S2_Sky_Ground_0_XL) {//����̑�̉E
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						enemy[e].vecx += 0.9f;
					}
				}
				else if (EnXR[e] >= S2_Sky_Ground_0_XU - PlusPx && EnXR[e] <= S2_Sky_Ground_0_XU) {//����̑�̍�
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
						enemy[e].vecx -= 0.9f;
					}
				}
			}

			if (EnYR[e] >= S2_Sky_Ground_1_YU + PlusPx && EnYL[e] <= S2_Sky_Ground_1_YL - PlusPx) {//�E��̑�i���ʁj
				if (EnXL[e] <= S2_Sky_Ground_1_XL + PlusPx && EnXR[e] >= S2_Sky_Ground_1_XL) {//�E��̑�̉E
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						enemy[e].vecx += 0.9f;
					}
				}
				else if (EnXR[e] >= S2_Sky_Ground_1_XU - PlusPx && EnXR[e] <= S2_Sky_Ground_1_XU) {//�E��̑�̍�
					enemy[e].vecx *= -COR;
					if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
						enemy[e].vecx -= 0.9f;
					}
				}
			}
			/*******************************************************************************************************************************/
					//���ӂ̓����蔻��//
			/*******************************************************************************************************************************/
			if (EnYL[e] <= S_Sky_Ground_0_YL - PlusPx && EnYR[e] >= S_Sky_Ground_0_YL) {//��̑�i���Ӂj
				if (EnXL[e] <= S_Sky_Ground_0_XL && EnXR[e] >= S_Sky_Ground_0_XU) {
					enemy[e].vecy *= -COR;
					if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						enemy[e].vecy += 0.9f;
					}
				}
			}

			if (EnYL[e] <= S2_Sky_Ground_0_YL - PlusPx && EnYR[e] >= S2_Sky_Ground_0_YL) {//����̑�i���Ӂj
				if (EnXL[e] <= S2_Sky_Ground_0_XL && EnXR[e] >= S2_Sky_Ground_0_XU) {
					enemy[e].vecy *= -COR;
					if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						enemy[e].vecy += 0.9f;
					}
				}
			}

			if (EnYL[e] <= S2_Sky_Ground_1_YL - PlusPx && EnYR[e] >= S2_Sky_Ground_1_YL) {//�E��̑�i���Ӂj
				if (EnXL[e] <= S2_Sky_Ground_1_XL && EnXR[e] >= S2_Sky_Ground_1_XU) {
					enemy[e].vecy *= -COR;
					if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
						enemy[e].vecy += 0.9f;
					}
				}
			}

			if (EnYL[e] <= 0) {//��ʏ�̓����蔻��
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}
		/*******************************************************************************************************************************/
				//��ӂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (EnYR[e] >= S_Ground_Left_YU && EnYR[e] <= S_Ground_Left_YU + PlusPx && EnXL[e] <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Ground_Right_YU && EnYR[e] <= S_Ground_Right_YU + PlusPx && EnXR[e] >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Sky_Ground_0_YU && EnYR[e] <= S_Sky_Ground_0_YU + PlusPx && EnXL[e] <= S_Sky_Ground_0_XL && EnXR[e] >= S_Sky_Ground_0_XU) {//�����Ă��钆���̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S2_Sky_Ground_0_YU && EnYR[e] <= S2_Sky_Ground_0_YU + PlusPx && EnXL[e] <= S2_Sky_Ground_0_XL && EnXR[e] >= S2_Sky_Ground_0_XU) {//�����Ă��鍶��̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S2_Sky_Ground_1_YU && EnYR[e] <= S2_Sky_Ground_1_YU + PlusPx && EnXL[e] <= S2_Sky_Ground_1_XL && EnXR[e] >= S2_Sky_Ground_1_XU) {//�����Ă��鍶��̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else {
			enemy[e].ground = 0;
		}
	}
	else if (NowStage == 3) {//***************�@�R�X�e�[�W�@***************//
/*******************************************************************************************************************************/
		//���ʂ̓����蔻��//
/*******************************************************************************************************************************/
		if (enemy[e].ground == 0) {
			if (EnXL[e] <= S_Ground_Left_XL && EnYR[e] >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}

			if (EnXR[e] >= S_Ground_Right_XU && EnYR[e] >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_SGround_0_YU + PlusPx && EnYL[e] <= S3_Sky_SGround_0_YL - PlusPx) {//���ߓ��΁i�n�ʁj
			if (EnXL[e] <= S3_Sky_SGround_0_XL + PlusPx && EnXR[e] >= S3_Sky_SGround_0_XL) {//���ߓ��΂̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_SGround_0_XU - PlusPx && EnXR[e] <= S3_Sky_SGround_0_XU) {//���ߓ��΂̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_SStone_0_YU + PlusPx && EnYL[e] <= S3_Sky_SStone_0_YL - PlusPx) {//���ߓ��΁i�΁j
			if (EnXL[e] <= S3_Sky_SStone_0_XL + PlusPx && EnXR[e] >= S3_Sky_SStone_0_XL) {//���ߓ��΂̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_SStone_0_XU - PlusPx && EnXR[e] <= S3_Sky_SStone_0_XU) {//���ߓ��΂̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_SGround_1_YU + PlusPx && EnYL[e] <= S3_Sky_SGround_1_YL - PlusPx) {//�����ߓ��΁i�n�ʁj
			if (EnXL[e] <= S3_Sky_SGround_1_XL + PlusPx && EnXR[e] >= S3_Sky_SGround_1_XL) {//�����ߓ��΂̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_SGround_1_XU - PlusPx && EnXR[e] <= S3_Sky_SGround_1_XU) {//�����ߓ��΂̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_SStone_1_YU + PlusPx && EnYL[e] <= S3_Sky_SStone_1_YL - PlusPx) {//�����ߓ��΁i�΁j
			if (EnXL[e] <= S3_Sky_SStone_1_XL + PlusPx && EnXR[e] >= S3_Sky_SStone_1_XL) {//�����ߓ��΂̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_SStone_1_XU - PlusPx && EnXR[e] <= S3_Sky_SStone_1_XU) {//�����ߓ��΂̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_SGround_2_YU + PlusPx && EnYL[e] <= S3_Sky_SGround_2_YL - PlusPx) {//�E�ߓ��΁i�n�ʁj
			if (EnXL[e] <= S3_Sky_SGround_2_XL + PlusPx && EnXR[e] >= S3_Sky_SGround_2_XL) {//�E�ߓ��΂̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_SGround_2_XU - PlusPx && EnXR[e] <= S3_Sky_SGround_2_XU) {//�E�ߓ��΂̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_SStone_2_YU + PlusPx && EnYL[e] <= S3_Sky_SStone_2_YL - PlusPx) {//�E�ߓ��΁i�΁j
			if (EnXL[e] <= S3_Sky_SStone_2_XL + PlusPx && EnXR[e] >= S3_Sky_SStone_2_XL) {//�E�ߓ��΂̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_SStone_2_XU - PlusPx && EnXR[e] <= S3_Sky_SStone_2_XU) {//�E�ߓ��΂̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_Ground_0_YU + PlusPx && EnYL[e] <= S3_Sky_Ground_0_YL - PlusPx) {//��󒆏�
			if (EnXL[e] <= S3_Sky_Ground_0_XL + PlusPx && EnXR[e] >= S3_Sky_Ground_0_XL) {//��󒆏��̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_Ground_0_XU - PlusPx && EnXR[e] <= S3_Sky_Ground_0_XU) {//��󒆏��̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S3_Sky_Ground_1_YU + PlusPx && EnYL[e] <= S3_Sky_Ground_1_YL - PlusPx) {//���󒆏�
			if (EnXL[e] <= S3_Sky_Ground_1_XL + PlusPx && EnXR[e] >= S3_Sky_Ground_1_XL) {//���󒆏��̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S3_Sky_Ground_1_XU - PlusPx && EnXR[e] <= S3_Sky_Ground_1_XU) {//���󒆏��̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}
		/*******************************************************************************************************************************/
				//���ӂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (EnYL[e] <= S3_Sky_SGround_0_YL - PlusPx && EnYR[e] >= S3_Sky_SGround_0_YL) {//���ߓ��΁i�n�ʁj�i���Ӂj
			if (EnXL[e] <= S3_Sky_SGround_0_XL && EnXR[e] >= S3_Sky_SGround_0_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_SStone_0_YL - PlusPx && EnYR[e] >= S3_Sky_SStone_0_YL) {//���ߓ��΁i�΁j�i���Ӂj
			if (EnXL[e] <= S3_Sky_SStone_0_XL && EnXR[e] >= S3_Sky_SStone_0_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_SGround_1_YL - PlusPx && EnYR[e] >= S3_Sky_SGround_1_YL) {//�����ߓ��΁i�n�ʁj�i���Ӂj
			if (EnXL[e] <= S3_Sky_SGround_1_XL && EnXR[e] >= S3_Sky_SGround_1_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_SStone_1_YL - PlusPx && EnYR[e] >= S3_Sky_SStone_1_YL) {//�����ߓ��΁i�΁j�i���Ӂj
			if (EnXL[e] <= S3_Sky_SStone_1_XL && EnXR[e] >= S3_Sky_SStone_1_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_SGround_2_YL - PlusPx && EnYR[e] >= S3_Sky_SGround_2_YL) {//���ߓ��΁i�n�ʁj�i���Ӂj
			if (EnXL[e] <= S3_Sky_SGround_2_XL && EnXR[e] >= S3_Sky_SGround_2_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_SStone_2_YL - PlusPx && EnYR[e] >= S3_Sky_SStone_2_YL) {//���ߓ��΁i�΁j�i���Ӂj
			if (EnXL[e] <= S3_Sky_SStone_2_XL && EnXR[e] >= S3_Sky_SStone_2_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_Ground_0_YL - PlusPx && EnYR[e] >= S3_Sky_Ground_0_YL) {//��󒆏��i���Ӂj
			if (EnXL[e] <= S3_Sky_Ground_0_XL && EnXR[e] >= S3_Sky_Ground_0_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S3_Sky_Ground_1_YL - PlusPx && EnYR[e] >= S3_Sky_Ground_1_YL) {//���󒆏��i���Ӂj
			if (EnXL[e] <= S3_Sky_Ground_1_XL && EnXR[e] >= S3_Sky_Ground_1_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= 0) {//��ʏ�̓����蔻��
			enemy[e].vecy *= -COR;
			if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
				enemy[e].vecy += 0.9f;
			}
		}

		/*******************************************************************************************************************************/
				//��ӂ̓����蔻��//
		/*******************************************************************************************************************************/

		if (EnYR[e] >= S_Ground_Left_YU && EnYR[e] <= S_Ground_Left_YU + PlusPx && EnXL[e] <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Ground_Right_YU && EnYR[e] <= S_Ground_Right_YU + PlusPx && EnXR[e] >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S3_Sky_SGround_0_YU && EnYR[e] <= S3_Sky_SGround_0_YU + PlusPx && EnXL[e] <= S3_Sky_SGround_0_XL && EnXR[e] >= S3_Sky_SGround_0_XU) {//���ߓ��΁i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S3_Sky_SGround_1_YU && EnYR[e] <= S3_Sky_SGround_1_YU + PlusPx && EnXL[e] <= S3_Sky_SGround_1_XL && EnXR[e] >= S3_Sky_SGround_1_XU) {//�����ߓ��΁i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S3_Sky_SGround_2_YU && EnYR[e] <= S3_Sky_SGround_2_YU + PlusPx && EnXL[e] <= S3_Sky_SGround_2_XL && EnXR[e] >= S3_Sky_SGround_2_XU) {//�E�ߓ��΁i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S3_Sky_Ground_0_YU && EnYR[e] <= S3_Sky_Ground_0_YU + PlusPx && EnXL[e] <= S3_Sky_Ground_0_XL && EnXR[e] >= S3_Sky_Ground_0_XU) {//��󒆏��i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S3_Sky_Ground_1_YU && EnYR[e] <= S3_Sky_Ground_1_YU + PlusPx && EnXL[e] <= S3_Sky_Ground_1_XL && EnXR[e] >= S3_Sky_Ground_1_XU) {//���󒆏��i��Ӂj
			enemy[e].ground = 1;
		}
		else {
			enemy[e].ground = 0;
		}
	}
	else if (NowStage == 4) {//***************�@�S�X�e�[�W�@***************//
/*******************************************************************************************************************************/
		//���ʂ̓����蔻��//
/*******************************************************************************************************************************/
		if (enemy[e].ground == 0) {
			if (EnXL[e] <= S_Ground_Left_XL && EnYR[e] >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}

			if (EnXR[e] >= S_Ground_Right_XU && EnYR[e] >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S4_Sky_Ground_0_YU + PlusPx && EnYL[e] <= S4_Sky_Ground_0_YL - PlusPx) {//�P�ԍ�
			if (EnXL[e] <= S4_Sky_Ground_0_XL + PlusPx && EnXR[e] >= S4_Sky_Ground_0_XL) {//�P�ԍ��̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S4_Sky_Ground_0_XU - PlusPx && EnXR[e] <= S4_Sky_Ground_0_XU) {//�P�ԍ��̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S4_Sky_Ground_1_YU + PlusPx && EnYL[e] <= S4_Sky_Ground_1_YL - PlusPx) {//������Q�Ԗ�
			if (EnXL[e] <= S4_Sky_Ground_1_XL + PlusPx && EnXR[e] >= S4_Sky_Ground_1_XL) {//������Q�Ԗڂ̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S4_Sky_Ground_1_XU - PlusPx && EnXR[e] <= S4_Sky_Ground_1_XU) {//������Q�Ԗڂ̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S4_Sky_Ground_2_YU + PlusPx && EnYL[e] <= S4_Sky_Ground_2_YL - PlusPx) {//�P�ԏ�
			if (EnXL[e] <= S4_Sky_Ground_2_XL + PlusPx && EnXR[e] >= S4_Sky_Ground_2_XL) {//�P�ԏ�̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S4_Sky_Ground_2_XU - PlusPx && EnXR[e] <= S4_Sky_Ground_2_XU) {//�P�ԏ�̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S4_Sky_Ground_3_YU + PlusPx && EnYL[e] <= S4_Sky_Ground_3_YL - PlusPx) {//�P�ԉ�
			if (EnXL[e] <= S4_Sky_Ground_3_XL + PlusPx && EnXR[e] >= S4_Sky_Ground_3_XL) {//�P�ԉ��̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S4_Sky_Ground_3_XU - PlusPx && EnXR[e] <= S4_Sky_Ground_3_XU) {//�P�ԉ��̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S4_Sky_Ground_4_YU + PlusPx && EnYL[e] <= S4_Sky_Ground_4_YL - PlusPx) {//�P�ԉE
			if (EnXL[e] <= S4_Sky_Ground_4_XL + PlusPx && EnXR[e] >= S4_Sky_Ground_4_XL) {//�P�ԉE�̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S4_Sky_Ground_4_XU - PlusPx && EnXR[e] <= S4_Sky_Ground_4_XU) {//�P�ԉE�̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}
		/*******************************************************************************************************************************/
				//���ӂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (EnYL[e] <= S4_Sky_Ground_0_YL - PlusPx && EnYR[e] >= S4_Sky_Ground_0_YL) {//�P�ԍ�
			if (EnXL[e] <= S4_Sky_Ground_0_XL && EnXR[e] >= S4_Sky_Ground_0_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S4_Sky_Ground_1_YL - PlusPx && EnYR[e] >= S4_Sky_Ground_1_YL) {//������Q�Ԗ�
			if (EnXL[e] <= S4_Sky_Ground_1_XL && EnXR[e] >= S4_Sky_Ground_1_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S4_Sky_Ground_2_YL - PlusPx && EnYR[e] >= S4_Sky_Ground_2_YL) {//�P�ԏ�
			if (EnXL[e] <= S4_Sky_Ground_2_XL && EnXR[e] >= S4_Sky_Ground_2_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S4_Sky_Ground_3_YL - PlusPx && EnYR[e] >= S4_Sky_Ground_3_YL) {//�P�ԉ�
			if (EnXL[e] <= S4_Sky_Ground_3_XL && EnXR[e] >= S4_Sky_Ground_3_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S4_Sky_Ground_4_YL - PlusPx && EnYR[e] >= S4_Sky_Ground_4_YL) {//�P�ԉE
			if (EnXL[e] <= S4_Sky_Ground_4_XL && EnXR[e] >= S4_Sky_Ground_4_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= 0) {//��ʏ�̓����蔻��
			enemy[e].vecy *= -COR;
			if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
				enemy[e].vecy += 0.9f;
			}
		}

		/*******************************************************************************************************************************/
				//��ӂ̓����蔻��//
		/*******************************************************************************************************************************/

		if (EnYR[e] >= S_Ground_Left_YU && EnYR[e] <= S_Ground_Left_YU + PlusPx && EnXL[e] <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Ground_Right_YU && EnYR[e] <= S_Ground_Right_YU + PlusPx && EnXR[e] >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S4_Sky_Ground_0_YU && EnYR[e] <= S4_Sky_Ground_0_YU + PlusPx && EnXL[e] <= S4_Sky_Ground_0_XL && EnXR[e] >= S4_Sky_Ground_0_XU) {//�P�ԍ��̑�
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S4_Sky_Ground_1_YU && EnYR[e] <= S4_Sky_Ground_1_YU + PlusPx && EnXL[e] <= S4_Sky_Ground_1_XL && EnXR[e] >= S4_Sky_Ground_1_XU) {//������Q�Ԗڂ̑�
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S4_Sky_Ground_2_YU && EnYR[e] <= S4_Sky_Ground_2_YU + PlusPx && EnXL[e] <= S4_Sky_Ground_2_XL && EnXR[e] >= S4_Sky_Ground_2_XU) {//�P�ԏ�̑�
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S4_Sky_Ground_3_YU && EnYR[e] <= S4_Sky_Ground_3_YU + PlusPx && EnXL[e] <= S4_Sky_Ground_3_XL && EnXR[e] >= S4_Sky_Ground_3_XU) {//�P�ԉ��̑�
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S4_Sky_Ground_4_YU && EnYR[e] <= S4_Sky_Ground_4_YU + PlusPx && EnXL[e] <= S4_Sky_Ground_4_XL && EnXR[e] >= S4_Sky_Ground_4_XU) {//�P�ԉE�̑�
			enemy[e].ground = 1;
		}
		else {
			enemy[e].ground = 0;
		}
	}
	else if (NowStage == 5) {//***************�@�T�X�e�[�W�@***************//
/*******************************************************************************************************************************/
		//���ʂ̓����蔻��//
/*******************************************************************************************************************************/
		if (enemy[e].ground == 0) {
			if (EnXL[e] <= S_Ground_Left_XL && EnYR[e] >= S_Ground_Left_YU + PlusPx) {//�����̑�i���ʁj
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}

			if (EnXR[e] >= S_Ground_Right_XU && EnYR[e] >= S_Ground_Right_YU + PlusPx) {//�E���̑�i���ʁj
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S5_Sky_SGround_0_YU + PlusPx && EnYL[e] <= S5_Sky_SGround_0_YL - PlusPx) {//���ߓ���
			if (EnXL[e] <= S5_Sky_SGround_0_XL + PlusPx && EnXR[e] >= S5_Sky_SGround_0_XL) {//���ߓ��΂̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S5_Sky_SGround_0_XU - PlusPx && EnXR[e] <= S5_Sky_SGround_0_XU) {//���ߓ��΂̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S5_Sky_SGround_1_YU + PlusPx && EnYL[e] <= S5_Sky_SGround_1_YL - PlusPx) {//�����ߓ���
			if (EnXL[e] <= S5_Sky_SGround_1_XL + PlusPx && EnXR[e] >= S5_Sky_SGround_1_XL) {//�����ߓ��΂̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S5_Sky_SGround_1_XU - PlusPx && EnXR[e] <= S5_Sky_SGround_1_XU) {//�����ߓ��΂̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S5_Sky_SGround_2_YU + PlusPx && EnYL[e] <= S5_Sky_SGround_2_YL - PlusPx) {//�E�ߓ���
			if (EnXL[e] <= S5_Sky_SGround_2_XL + PlusPx && EnXR[e] >= S5_Sky_SGround_2_XL) {//�E�ߓ��΂̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S5_Sky_SGround_2_XU - PlusPx && EnXR[e] <= S5_Sky_SGround_2_XU) {//�E�ߓ��΂̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S5_Sky_Ground_0_YU + PlusPx && EnYL[e] <= S5_Sky_Ground_0_YL - PlusPx) {//�P�ԏ�
			if (EnXL[e] <= S5_Sky_Ground_0_XL + PlusPx && EnXR[e] >= S5_Sky_Ground_0_XL) {//�P�ԏ�̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S5_Sky_Ground_0_XU - PlusPx && EnXR[e] <= S5_Sky_Ground_0_XU) {//�P�ԏ�̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S5_Sky_Ground_1_YU + PlusPx && EnYL[e] <= S5_Sky_Ground_1_YL - PlusPx) {//���̉E
			if (EnXL[e] <= S5_Sky_Ground_1_XL + PlusPx && EnXR[e] >= S5_Sky_Ground_1_XL) {//���̉E�̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S5_Sky_Ground_1_XU - PlusPx && EnXR[e] <= S5_Sky_Ground_1_XU) {//���̉E�̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}

		if (EnYR[e] >= S5_Sky_Ground_2_YU + PlusPx && EnYL[e] <= S5_Sky_Ground_2_YL - PlusPx) {//���̍�
			if (EnXL[e] <= S5_Sky_Ground_2_XL + PlusPx && EnXR[e] >= S5_Sky_Ground_2_XL) {//���̍��̉E
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecx += 0.9f;
				}
			}
			else if (EnXR[e] >= S5_Sky_Ground_2_XU - PlusPx && EnXR[e] <= S5_Sky_Ground_2_XU) {//���̍��̍�
				enemy[e].vecx *= -COR;
				if (enemy[e].vecx >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl������
					enemy[e].vecx -= 0.9f;
				}
			}
		}
		/*******************************************************************************************************************************/
				//���ӂ̓����蔻��//
		/*******************************************************************************************************************************/
		if (EnYL[e] <= S5_Sky_SGround_0_YL - PlusPx && EnYR[e] >= S5_Sky_SGround_0_YL) {//�E�ߓ���
			if (EnXL[e] <= S5_Sky_SGround_0_XL && EnXR[e] >= S5_Sky_SGround_0_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S5_Sky_SGround_1_YL - PlusPx && EnYR[e] >= S5_Sky_SGround_1_YL) {//�����ߓ���
			if (EnXL[e] <= S5_Sky_SGround_1_XL && EnXR[e] >= S5_Sky_SGround_1_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S5_Sky_SGround_2_YL - PlusPx && EnYR[e] >= S5_Sky_SGround_2_YL) {//�E�ߓ���
			if (EnXL[e] <= S5_Sky_SGround_2_XL && EnXR[e] >= S5_Sky_SGround_2_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S5_Sky_Ground_0_YL - PlusPx && EnYR[e] >= S5_Sky_Ground_0_YL) {//�P�ԏ�
			if (EnXL[e] <= S5_Sky_Ground_0_XL && EnXR[e] >= S5_Sky_Ground_0_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S5_Sky_Ground_1_YL - PlusPx && EnYR[e] >= S5_Sky_Ground_1_YL) {//���̉E
			if (EnXL[e] <= S5_Sky_Ground_1_XL && EnXR[e] >= S5_Sky_Ground_1_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= S5_Sky_Ground_2_YL - PlusPx && EnYR[e] >= S5_Sky_Ground_2_YL) {//���̍�
			if (EnXL[e] <= S5_Sky_Ground_2_XL && EnXR[e] >= S5_Sky_Ground_2_XU) {
				enemy[e].vecy *= -COR;
				if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
					enemy[e].vecy += 0.9f;
				}
			}
		}

		if (EnYL[e] <= 0) {//��ʏ�̓����蔻��
			enemy[e].vecy *= -COR;
			if (enemy[e].vecy >= 0) {//�߂荞�܂Ȃ��悤�ɂ��邽�߂ɉ����x���O�ȏ�ɂȂ�Ɖ����x�ɒl�𑫂�
				enemy[e].vecy += 0.9f;
			}
		}

		/*******************************************************************************************************************************/
				//��ӂ̓����蔻��//
		/*******************************************************************************************************************************/

		if (EnYR[e] >= S_Ground_Left_YU && EnYR[e] <= S_Ground_Left_YU + PlusPx && EnXL[e] <= S_Ground_Left_XL) {//�����̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S_Ground_Right_YU && EnYR[e] <= S_Ground_Right_YU + PlusPx && EnXR[e] >= S_Ground_Right_XU) {//�E���̑�i��Ӂj
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S5_Sky_SGround_0_YU && EnYR[e] <= S5_Sky_SGround_0_YU + PlusPx && EnXL[e] <= S5_Sky_SGround_0_XL && EnXR[e] >= S5_Sky_SGround_0_XU) {//���ߓ���
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S5_Sky_SGround_1_YU && EnYR[e] <= S5_Sky_SGround_1_YU + PlusPx && EnXL[e] <= S5_Sky_SGround_1_XL && EnXR[e] >= S5_Sky_SGround_1_XU) {//�����ߓ���
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S5_Sky_SGround_2_YU && EnYR[e] <= S5_Sky_SGround_2_YU + PlusPx && EnXL[e] <= S5_Sky_SGround_2_XL && EnXR[e] >= S5_Sky_SGround_2_XU) {//�E�ߓ���
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S5_Sky_Ground_0_YU && EnYR[e] <= S5_Sky_Ground_0_YU + PlusPx && EnXL[e] <= S5_Sky_Ground_0_XL && EnXR[e] >= S5_Sky_Ground_0_XU) {//��ԏ�
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S5_Sky_Ground_1_YU && EnYR[e] <= S5_Sky_Ground_1_YU + PlusPx && EnXL[e] <= S5_Sky_Ground_1_XL && EnXR[e] >= S5_Sky_Ground_1_XU) {//���̍�
			enemy[e].ground = 1;
		}
		else if (EnYR[e] >= S5_Sky_Ground_2_YU && EnYR[e] <= S5_Sky_Ground_2_YU + PlusPx && EnXL[e] <= S5_Sky_Ground_2_XL && EnXR[e] >= S5_Sky_Ground_2_XU) {//���̉E
			enemy[e].ground = 1;
		}
		else {
			enemy[e].ground = 0;
		}
  }
}

// �G�ƃv���C���[�̓����蔻��(�X�^�[�g��)
int Enemy::HitStart(int e)
{
	// �v���C���[�̋�`�̍��W
	float PXL, PYL;//����
	float PXR, PYR;//�E��

	PXL = Px + 18;//����X
	PYL = Py + 14;//����Y
	PXR = Px + 40;//�E��X
	PYR = Py + 64;//�E��Y


	EnXL[e] = enemy[e].x;
	EnYL[e] = enemy[e].y + 25.0f;
	EnXR[e] = EnXL[e] + 50.0f;
	EnYR[e] = EnYL[e] + 64.0f;


	if (enemy[e].life != 0)
	{
		if (EnXL[e] <= PXR && EnYL[e] <= PYR && EnXR[e] >= PXL && EnYR[e] >= PYL)
		{
			enemy[e].flg = 17;
			// ��
			enemy[e].life -= 1;

			HitPFlg = 1;  // �v���C���[���G�ɒ��˕Ԃ�

			return e;
		}
	}

	return 3;
}

// �G�ƃv���C���[�̓����蔻��
int Enemy::HitPlayer(int e)
{
	//�v���C���[�̋�`�̍��W
	float PXL, PYL; //����
	float PXR, PYR; //�E��

	PXL = Px + 18;  //����X
	PYL = Py + 14;  //����Y
	PXR = Px + 40;  //�E��X
	PYR = Py+ 64;   //�E��Y

	
	EnXL[e] = enemy[e].x + 10.0f;  //����X
	EnYL[e] = enemy[e].y + 12.0f;  //����Y
	EnXR[e] = EnXL[e] + 45.0f;     //�E��X
	EnYR[e] = EnYL[e] + 53.0f;     //�E��Y

	if (enemy[e].life == 2) // �G�����D��Ԃ̂Ƃ�
	{
		if (EnXL[e] <= PXR && EnYL[e] <= PYR && EnXR[e] >= PXL && EnYR[e] >= PYL)
		{
			if (PYR < (EnYL[e] + 36))    // �v���C���[�̈ʒu(����)���G�L����(���D�������l�̕���)�̔�������ɂ���ꍇ
			{
				enemy[e].flg = 17;
				// ��
				enemy[e].life -= 1;

				HitPFlg = 1; // �v���C���[���G�ɒ��˕Ԃ�

				return e;

			}
			else if (EnYR[e] > (PYL + 37)) // �G�̈ʒu(����)���v���C���[(���D�������l�̕���)�̔�������ɂ���ꍇ
			{
				enemy[e].flg = 17;

				HitPFlg = 2; // �v���C���[���G�ɒ��˕Ԃ�(���D����)�A�v���C���[�̕��D�������

				return 3;
			}
			else // �G�̈ʒu�ƃv���C���̈ʒu(����)�ɏ�L�ȏ�̍����Ȃ��ꍇ
			{
				enemy[e].flg = 17;

				HitPFlg = 1; // �v���C���[���G�ɒ��˕Ԃ�

				return 3;
			}
		}
	}
	else if(enemy[e].life == 1)  // �G���p���V���[�g��Ԃ̂Ƃ�
	{
		if (EnXL[e] <= PXR && EnYL[e] <= PYR && EnXR[e] >= PXL && EnYR[e] >= PYL)
		{
			if (PYR < (EnYL[e] + 36))    // �v���C���[�̈ʒu(����)���G�L����(���D�������l�̕���)�̔�������ɂ���ꍇ
			{
				enemy[e].flg = 17;
				// ��
				enemy[e].life -= 1;

				HitPFlg = 1; // �v���C���[���G�ɒ��˕Ԃ�

				return e;

			}
			else // ��L�ȏ�̏ꍇ
			{
				enemy[e].flg = 17;

				HitPFlg = 1; // �v���C���[���G�ɒ��˕Ԃ�

				return 3;
			}
		}	
	}
	else
	{
		return 3;
	}
		
	return 3;
}