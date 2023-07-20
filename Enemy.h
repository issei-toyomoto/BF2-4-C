#pragma once

#define ENEMY_X 200    // �G[1]��X���W
#define ENEMY_Y 185    // �G[1]��Y���W
#define ENEMY_W 55     // �G[1]�̕�
#define ENEMY_H 65     // �G[1]�̍���
#define ENEMY_MAX 3    // �G�̍ő吔

class Enemy
{
private:
	int StartFlg;      // �X�^�[�g��Ԃ����肷��p
	int EnemyImg[24];  // �G�̉摜�i�[�p
	int FPScnt;        // FPS�J�E���g
	int StartMotion;   // �X�^�[�g���A�G�̃��[�V�����Ǘ��p
	float Px, Py;      // �v���C���[��X���W�AY���W
	int HitFlg;        // �G���m�̓����蔻��p 
	int HitPFlg;       // �v���C���[�ƓG�̓����蔻��p
	float EnXL[ENEMY_MAX], EnYL[ENEMY_MAX]; //����
	float EnXR[ENEMY_MAX], EnYR[ENEMY_MAX]; //�E��

	// �G�̃f�[�^(�\����)
	struct ENEMY
	{
		float x = 0;        // �G��X���W
		float y = 0;        // �G��Y���W
		int state = 0;      // �G�̏��(0:�s���N 1:�� 2:���F)
		int life = 2;       // �G��HP(0:���S 1:�p���V���[�g��� 2:���D1���)
		int flg = 0;        // �G�̉摜�ԍ��p
		float speed = 0.6f; // �G�̈ړ����x
		int direction = 0;  // �G�̌����Ă����(0:�� 1:�E)
		int ground = 0;     // �n�ʂɐG��Ă��邩(0:�G��ĂȂ� 1:�G��Ă���)
	};

	struct ENEMY enemy[ENEMY_MAX];   // �G�̃f�[�^(�ϐ��錾)

public:
	Enemy();   // �R���X�g���N�^
	~Enemy();  // �f�X�g���N�^

	void EnemyInit();  // �G�̏���������
	void EnemyMove();  // �G�̈ړ�����
	void StartMove();  // �G�̃X�^�[�g����
	void EnemyUp();    // �G�̕��ヂ�[�V��������
	void EnemyDown();  // �G�̍~�����[�V��������
	int HitEnemy();    // �G���m�̓����蔻��
	int HitPlayer();   // �G�ƃv���C���[�̓����蔻��
	void HitStage();   // �G�ƃX�e�[�W�̓����蔻��

	
	//�`��ȊO�̍X�V����������
	void Update();
	//�`��̍X�V����������
	void Draw() const;
};

