#pragma once
//**********�摜�ϐ��̔z��v�f�ԍ�**********//
//�ҋ@��ԁi���D�Q�j
#define P_Img_Wait_Ballon_2_0 0
#define P_Img_Wait_Ballon_2_1 1
#define P_Img_Wait_Ballon_2_2 2
//�ҋ@��ԁi���D�P�j
#define P_Img_Wait_Ballon_1_0 3
#define P_Img_Wait_Ballon_1_1 4
#define P_Img_Wait_Ballon_1_2 5
//����i���D�Q�j
#define P_Img_Run_Ballon_2_0     8
#define P_Img_Run_Ballon_2_1     9
#define P_Img_Run_Ballon_2_2     10
#define P_Img_RunStop_Ballon_2_3 11
//����i���D�P�j
#define P_Img_Run_Ballon_1_0     12
#define P_Img_Run_Ballon_1_1     13
#define P_Img_Run_Ballon_1_2     14
#define P_Img_RunStop_Ballon_1_3 15
//�����i���D�Q�j
#define P_Img_Fly_Ballon_2_0 16
#define P_Img_Fly_Ballon_2_1 17
#define P_Img_Fly_Ballon_2_2 18
#define P_Img_Fly_Ballon_2_3 19
#define P_Img_FlyStop_Ballon_2_4 20
//�����i���D�P�j
#define P_Img_Fly_Ballon_1_0 24
#define P_Img_Fly_Ballon_1_1 25
#define P_Img_Fly_Ballon_1_2 26
#define P_Img_Fly_Ballon_1_3 27
#define P_Img_FlyStop_Ballon_1_4 28
//���S
#define P_Img_Dead_0 21
#define P_Img_Dead_1 22
#define P_Img_Dead_2 23
//���ɓ�����
#define P_Img_Thunder_0 29
#define P_Img_Thunder_1 30
//*******************************************//
// �摜�T�C�Y�i�U�S�~�U�S�j
#define P_Img_Size 64

//�v���C���[�̏��
#define P_State_Wait    0 //�ҋ@���
#define P_State_Run     1 //����
#define P_State_Fly     2 //����
#define P_State_Dead    3 //����
#define P_State_Thunder 4 //���ɓ�����

#define Init_BallonNum 2//���D�̏�����

#define Right  0 //�E
#define Left   1 //��

//�X�e�[�W���W
#define S_Ground_0_XU 0			//�����̑�
#define S_Ground_0_YU 420
#define S_Ground_0_XL 155
#define S_Ground_0_YL 455

#define S_Sky_Ground_0_XU 180	//�����̑�
#define S_Sky_Ground_0_YU 250
#define S_Sky_Ground_0_XL 460
#define S_Sky_Ground_0_YL 265

#define S_Ground_1_XU 460		//�E���̑�
#define S_Ground_1_YU 420
#define S_Ground_1_XL 620
#define S_Ground_1_YL 455

class Player
{
private:
	int FPSCnt;			//FPS�J�E���g

	int PlayerImg[32];	//�v���C���[�摜
	int NowPlayerImg;	//���݂̃v���C���[�摜�z��̗v�f

	float PlayerX;		//�v���C���[X���W
	float PlayerY;		//�v���C���[Y���W
	float VectorX;		//�x�N�g��X
	float VectorY;		//�x�N�g��Y
	int Angle;			//�����Ă����
	
	int PlayerState;	//�v���C���[�̏��
	int BalloonNum;		//���݂̕��D�̐�

	int XStick;//�X�e�b�N�㉺
	int YStick;//�X�e�b�N���E

	int MoX;
	int MoY;

	int NowStage;

	bool RunFlg;//(true:���� false;�����ĂȂ�)
	bool FlyFlg;//(true;��� false: ���ł��Ȃ�)
	bool Ground;//(true:�n�ʂ̏� false:�n�ʂ̏�ł͂Ȃ�)

public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player() {};
	//�`��ȊO�̍X�V����������
	void Update(int Stage);
	//�`��̍X�V����������
	void Draw() const;

	//�ړ������iX�����j
	void UpdatePlayerX();
	//�ړ������iY�����j
	void UpdatePlayerY();

	//�X�e�[�W�Ƃ̓����蔻�菈��
	void UpdateStageCollision();

	//�ړ��i�n�ʁj�̉摜����
	void UpdatePlayerImgRun();

	//�ړ��i�󒆁j�̉摜����
	void UpdatePlayerImgFly();

	//�ҋ@��Ԃ̉摜����
	void UpdatePlayerImgWait();

	//���ɓ�����̉摜����
	void UpdatePlayerImgThunder();

	//���S���̉摜����
	void UpdatePlayerImgDead();
};