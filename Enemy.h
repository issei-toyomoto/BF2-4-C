#pragma once

#define ENEMY_X 200    // �G[0]��X���W
#define ENEMY_Y 185    // �G[0]��Y���W
#define ENEMY_W 55     // �G�̕�
#define ENEMY_H 65     // �G�̍���
#define ENEMY_MAX 3    // �G�̍ő吔

class Enemy
{
private:
	int StartFlg;      // �X�^�[�g��Ԃ����肷��p
	int EnemyImg[3][24];  // �G�̉摜�i�[�p
	int FPScnt;        // FPS�J�E���g
	int StartMotion;   // �X�^�[�g���A�G�̃��[�V�����Ǘ��p
	float Px, Py;      // �v���C���[��X���W�AY���W
	int HitFlg;        // �G���m�̓����蔻��p 
	int HitPFlg;       // �v���C���[�ƓG�̓����蔻��p
	float EnXL[ENEMY_MAX], EnYL[ENEMY_MAX]; //�G�̍�����W
	float EnXR[ENEMY_MAX], EnYR[ENEMY_MAX]; //�G�̉E�����W

	float VectorX,VectorY;

	int UpCnt, DownCnt;

	const float MinY = -19.0f;
	
	// �G�̃f�[�^(�\����)
	struct ENEMY
	{
		float x = 0.0f;        // �G��X���W
		float y = 0.0f;        // �G��Y���W
		int state = 0;      // �G�̏��(0:�s���N 1:�� 2:���F)
		int life = 2;       // �G��HP(0:���S 1:�p���V���[�g��� 2:���D1���)
		int flg = 0;        // �G�̉摜�ԍ��p
		int direction = 0;  // �G�̌����Ă����(0:�� 1:�E)
		int ground = 0;     // �n�ʂɐG��Ă��邩(0:�G��ĂȂ� 1:�G��Ă���)
		int die = 0;        // �G���S���p
		int ran = 0;
	};

	struct ENEMY enemy[ENEMY_MAX];   // �G�̃f�[�^(�ϐ��錾)

public:
	Enemy();   // �R���X�g���N�^
	~Enemy();  // �f�X�g���N�^

	void EnemyInit();  // �G�̏���������
	void EnemyMove(int i);  // �G�̈ړ�����
	void StartMove();  // �G�̃X�^�[�g����
	void EnemyUp(int e);    // �G�̕��ヂ�[�V��������
	void EnemyDown(int e);  // �G�̍~�����[�V��������
	void EnemyLeft(int e);  // �G�̍��ړ�����
	void EnemyRight(int e); // �G�̉E�ړ�����
	int HitEnemy(int e);    // �G���m�̓����蔻��
	int HitPlayer(int e);   // �G�ƃv���C���[�̓����蔻��
	void HitStage(int e);   // �G�ƃX�e�[�W�̓����蔻��
	int HitStart(int e);    // �G�ƃv���C���[�̓����蔻��(�X�^�[�g��)
	void EnemyDie(int e);   // �G�̎��S���[�V��������

	void EnemyMoveX(int e);  // �G�̈ړ�����
	void EnemyMoveY(int e);  // �G�̈ړ�����
	
	//�`��ȊO�̍X�V����������
	void Update();
	//�`��̍X�V����������
	void Draw() const;
};

