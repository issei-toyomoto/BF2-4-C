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
	int ScoreImg[5];  // �X�R�A�摜�p
	int Fcnt;        // FPS�J�E���g
	int StartMotion;   // �X�^�[�g���A�G�̃��[�V�����Ǘ��p
	float Px, Py;      // �v���C���[��X���W�AY���W
	int HitFlg;        // �G���m�̓����蔻��p 
	int HitPeFlg;      // �G�ƃv���C���[�̓����蔻��p
	float EnXL[ENEMY_MAX], EnYL[ENEMY_MAX]; //�G�̍�����W
	float EnXR[ENEMY_MAX], EnYR[ENEMY_MAX]; //�G�̉E�����W
	float MaxSpeed;      // �ő呬�x
	float acceleration;  // �����x
	float friction;      // ���C�W��
	const int EnemyMax[5] = { 3,5,3,4,5 }; //�X�e�[�W���Ƃ̓G�̍ő吔(2�X�e�[�W�ȍ~�̐��͐��K�ł͂Ȃ�)
	int OldStage;  // �X�e�[�W�J�ڂ����Ƃ��p
	int EnMax;     // �G�̍ő吔�i�[
	int NowStage;  // ���݂̃X�e�[�W
	int StageFlg;  // �X�e�[�W�J�ڂ����Ƃ���x�����G�̏���������p
	
	// �G�̃f�[�^(�\����)
	struct ENEMY
	{
		float x = 0.0f;     // �G��X���W
		float y = 0.0f;     // �G��Y���W
		float oldx = 0.0f;  // �G���v���C���[�ɓ����������̃X�R�A�\���p
		float oldy = 0.0f;  // �G���v���C���[�ɓ����������̃X�R�A�\���p
		float vecx = 0.0f;  // �G�̈ړ���X
		float vecy = 0.0f;  // �G�̈ړ���Y
		int state = 0;      // �G�̏��(0:�s���N 1:�� 2:���F)
		int life = 2;       // �G��HP(0:���S 1:�p���V���[�g��� 2:���D1���)
		int start = 0;      // �p���V���[�g��Ԍ�̕��D�c��܂���p
		int flg = 0;        // �G�̉摜�ԍ��p
		int direction = 0;  // �G�̌����Ă����(0:�� 1:�E)
		int ground = 0;     // �n�ʂɐG��Ă��邩(0:�G��ĂȂ� 1:�G��Ă���)
		int die = 0;        // �G���S���p
		int para = 0;       // �p���V���[�g���[�V�����p
		int sm = 0;         // ���ڂ̃X�^�[�g�p
		int waittime = 0;   // �p���V���[�g��ԂŒn�ʂɂ��ĕ��D��c��܂���܂ł̑ҋ@���ԗp
		int score = -1;     // �X�R�A�p

	};

	struct ENEMY enemy[ENEMY_MAX];   // �G�̃f�[�^(�ϐ��錾)

public:
	 static int HitPFlg;       // �v���C���[�ƓG�̓����蔻��(�v���C���[�ɒl��n��)
	 static ENEMY2 EnemyData[ENEMY_MAX]; // �G�̍��W�A��ԁi�F�j�n���p
	 static int EnemyTotalScore;  // �X�R�A���Z�p

	Enemy();   // �R���X�g���N�^
	~Enemy();  // �f�X�g���N�^

	void EnemyInit(int nowstage);  // �G�̏���������
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
	void EnMove(int e);     // �G�̈ړ�����
	void SetEnemyData(int e); // �G�̃f�[�^���i�[

	//�`��ȊO�̍X�V����������
	void Update(int nowstage);
	//�`��̍X�V����������
	void Draw() const;
};

