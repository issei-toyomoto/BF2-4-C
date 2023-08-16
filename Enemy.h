#pragma once

#define ENEMY_X 200    // �G[0]��X���W
#define ENEMY_Y 185    // �G[0]��Y���W
#define ENEMY_W 55     // �G�̕�
#define ENEMY_H 65     // �G�̍���
#define ENEMY_MAX 3    // �G�̍ő吔

struct ENEMY2
{
	float x = 0.0f;
	float y = 0.0f;     // �G��Y���W
	int state = 0;      // �G�̏��(0:�s���N 1:�� 2:���F)
};

class Enemy
{
private:
	int StartFlg;      // �X�^�[�g��Ԃ����肷��p
	int EnemyImg[3][24];  // �G�̉摜�i�[�p
	int ScoreImg[3];
	int Fcnt;        // FPS�J�E���g
	int StartMotion;   // �X�^�[�g���A�G�̃��[�V�����Ǘ��p
	float Px, Py;      // �v���C���[��X���W�AY���W
	int HitFlg;        // �G���m�̓����蔻��p 
	int HitPeFlg;
	float EnXL[ENEMY_MAX], EnYL[ENEMY_MAX]; //�G�̍�����W
	float EnXR[ENEMY_MAX], EnYR[ENEMY_MAX]; //�G�̉E�����W
	float MaxSpeed;      // �ő呬�x
	float acceleration;  // �����x
	float friction;      // ���C�W��
	int NowStage;
	
	const float MinY = -19.0f;
	
	// �G�̃f�[�^(�\����)
	struct ENEMY
	{
		float x = 0.0f;     // �G��X���W
		float y = 0.0f;     // �G��Y���W
		float oldx = 0.0f;
		float oldy = 0.0f;
		float vecx = 0.0f;  // �G�̈ړ���X
		float vecy = 0.0f;  // �G�̈ړ���Y
		int state = 0;      // �G�̏��(0:�s���N 1:�� 2:���F)
		int life = 2;       // �G��HP(0:���S 1:�p���V���[�g��� 2:���D1���)
		int start = 0;      // �p���V���[�g��Ԍ�̕��D�c��܂���p
		int flg = 0;        // �G�̉摜�ԍ��p
		int direction = 0;  // �G�̌����Ă����(0:�� 1:�E)
		int ground = 0;     // �n�ʂɐG��Ă��邩(0:�G��ĂȂ� 1:�G��Ă���)
		int die = 0;        // �G���S���p
		int ran = 0;
		int para = 0;
		int sm = 0;
		int waittime = 0;
		int okballoon = 0;
		int hitflg = 0;
		int hitpflg = 0;
		int score = -1;

	};

	struct ENEMY enemy[ENEMY_MAX];   // �G�̃f�[�^(�ϐ��錾)

public:
	 static int HitPFlg;       // �v���C���[�ƓG�̓����蔻��(�v���C���[�ɒl��n��)

	 static ENEMY2 EnemyData[ENEMY_MAX]; // �G�̍��W�A��ԁi�F�j�n���p

	 static int EnemyScore;

	Enemy();   // �R���X�g���N�^
	~Enemy();  // �f�X�g���N�^

	void EnemyInit();       // �G�̏���������
	void EnemyMove(int i);  // �G�̈ړ�����
	void StartMove();       // �G�̃X�^�[�g����
	void StartMove(int i);  // �G�̃X�^�[�g����(�p���V���[�g��)
	void EnemyUp(int e);    // �G�̕��ヂ�[�V��������
	void EnemyDown(int e);  // �G�̍~�����[�V��������
	void EnemyLeft(int e);  // �G�̍��ړ�����
	void EnemyRight(int e); // �G�̉E�ړ�����
	void HitStage(int e);   // �G�ƃX�e�[�W�̓����蔻��
	int HitEnemy(int e,int e2);    // �G���m�̓����蔻��
	int HitStart(int e);    // �G�ƃv���C���[�̓����蔻��(�X�^�[�g��)
	int HitPlayer(int e);   // �G�ƃv���C���[�̓����蔻��
	void EnemyDie(int e);   // �G�̎��S���[�V��������
	void EnemyPara(int e);  // �G�̃p���V���[�g����
	void EnMove(int e);
	void SetEnemyData(int e);

	//�`��ȊO�̍X�V����������
	void Update(int nowstage);
	//�`��̍X�V����������
	void Draw() const;
};

