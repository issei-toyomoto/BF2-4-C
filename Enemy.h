#pragma once
#include "Player.h"

#define ENEMY_X 200
#define ENEMY_Y 185

// �G�̃f�[�^(�\����)
struct EnemyData
{
	float x;     // �G��X���W
	float y;     // �G��Y���W
	int state;   // �G�̏��(0:�s���N 1:�� 2:���F)
	int life;    // �G��HP
	int flg;     // �G�̉摜�ԍ��p
	float speed; // �G�̈ړ����x
};

class Enemy
{
private:
	int StartFlg;      // �X�^�[�g��Ԃ����肷��p
	int EnemyImg[24];  // �G�̉摜�i�[�p
	int FPScnt;        // FPS�J�E���g
	int i;             // �X�^�[�g���A�G�̃��[�V�����Ǘ��p
	EnemyData enemy;   // �G�̃f�[�^(�ϐ��錾)

	Player player;     // �v���C���[�I�u�W�F�N�g��
	float Px,Py;         // �v���C���[��X���W�AY���W

public:
	Enemy();   // �R���X�g���N�^
	~Enemy();  // �f�X�g���N�^

	void EnemyMove();       // �G�̈ړ�����
	void StartMove();       // �G�̃X�^�[�g����
	void EnemyCollision();  // �G�ƃX�e�[�W�̓����蔻�菈��

	//�`��ȊO�̍X�V����������
	void Update();
	//�`��̍X�V����������
	void Draw() const;
};

