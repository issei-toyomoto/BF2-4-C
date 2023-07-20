#pragma once

#define ENEMY_X 200
#define ENEMY_Y 185
#define ENEMY_W 55
#define ENEMY_H 65
#define ENEMY_MAX 3

class Enemy
{
private:
	int StartFlg;      // �X�^�[�g��Ԃ����肷��p
	int EnemyImg[24];  // �G�̉摜�i�[�p
	int FPScnt;        // FPS�J�E���g
	int StartMotion;   // �X�^�[�g���A�G�̃��[�V�����Ǘ��p
	float Px, Py;      // �v���C���[��X���W�AY���W

	// �G�̃f�[�^(�\����)
	struct ENEMY
	{
		float x = 0;     // �G��X���W
		float y = 0;     // �G��Y���W
		int state = 0;   // �G�̏��(0:�s���N 1:�� 2:���F)
		int life = 2;    // �G��HP
		int flg = 0;     // �G�̉摜�ԍ��p
		float speed = 0.4f; // �G�̈ړ����x
	};

	struct ENEMY enemy[ENEMY_MAX];   // �G�̃f�[�^(�ϐ��錾)

public:
	Enemy();   // �R���X�g���N�^
	~Enemy();  // �f�X�g���N�^

	void EnemyInit();       // �G�̏���������
	void EnemyMove();       // �G�̈ړ�����
	void StartMove();       // �G�̃X�^�[�g����
	void EnemyUp();         // �G�̕��ヂ�[�V��������
	void EnemyDown();       // �G�̍~�����[�V��������
	void EnemyCollision();  // �G���m�̓����蔻��
	void StageCollision();  // �G�ƃX�e�[�W�̓����蔻��

	
	//�`��ȊO�̍X�V����������
	void Update();
	//�`��̍X�V����������
	void Draw() const;
};

