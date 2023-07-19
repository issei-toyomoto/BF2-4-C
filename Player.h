#pragma once
//**********�摜�ϐ��̔z��v�f�ԍ�**********//
//�ҋ@��ԁi���D�Q�j
#define P_Img_Wait_Ballon_2_0 0
#define P_Img_Wait_Ballon_2_1 1
#define P_Img_Wait_Ballon_2_2 2
#define P_Img_Wait_Red_Ballon_2 3
//�ҋ@��ԁi���D�P�j
#define P_Img_Wait_Ballon_1_0 4
#define P_Img_Wait_Ballon_1_1 5
#define P_Img_Wait_Ballon_1_2 6
#define P_Img_Wait_Red_Ballon_1 7
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
//���S
#define P_Img_Dead_0 21
#define P_Img_Dead_1 22
#define P_Img_Dead_2 23
//�����i���D�P�j
#define P_Img_Fly_Ballon_1_0 24
#define P_Img_Fly_Ballon_1_1 25
#define P_Img_Fly_Ballon_1_2 26
#define P_Img_Fly_Ballon_1_3 27
#define P_Img_FlyStop_Ballon_1_4 28

//���ɓ�����
#define P_Img_Thunder_0 29
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

#define P_Right  0 //�E
#define P_Left   1 //��

#define ON_FlyBtn  true	//��ԃ{�^���������Ă���
#define OFF_FlyBtn false//��ԃ{�^���������Ă��Ȃ�

#define Ground     true	//�n�ʂƐڐG���Ă���
#define Not_Ground false//�n�ʂƐڐG���Ă��Ȃ�

#define Touch      true	//�n�ʈȊO�ɐG��Ă���
#define Not_Touch  false//�n�ʈȊO�ɐG��ĂȂ�

#define FivePx 5 //5px��������i�����蔻��j

class Player
{
private:
	int FPSCnt;			//FPS�J�E���g

	int PlayerImg[32];	//�v���C���[�摜
	int NowPlayerImg;	//���݂̃v���C���[�摜�z��̗v�f

	float VectorX;			//�x�N�g��X
	float VectorY;			//�x�N�g��Y
	int Angle;				//�����Ă����
	
	int PlayerState;	//�v���C���[�̏��
	int BalloonNum;		//���݂̕��D�̐�

	int XStick;			//�X�e�b�N�㉺
	int YStick;			//�X�e�b�N���E

	int MoX;			//�}�E�X�J�[�\��X���W
	int MoY;			//�}�E�X�J�[�\��Y���W

	int NowStage;		//���݂̃X�e�[�W

	static int NowFraem;//���݂̃t���[��
	static int OldFraem;//�v���J�n���̃t���[��

	bool FlyBtnFlg;		//(true;��ԃ{�^���������Ă��� false:��ԃ{�^���������Ă��Ȃ�)
	bool GroundFlg;		//(true:�n�ʂɐڐG���Ă���     false:�n�ʂɐڐG���Ă��Ȃ�    )
	bool TouchFlg;		//(treu:�n�ʈȊO�ɐG��Ă���   false:�n�ʈȊO�ɐG��Ă��Ȃ��@)
	bool Abtn;

	int AbtnCnt = 0;
	int Anti_AbtnCnt = 0;
public:
	static float PlayerX;	//�v���C���[X���W(�摜�̍���X���W)
	static float PlayerY;	//�v���C���[Y���W(�摜�̍���Y���W)

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

	//�v���C���[�̍��W�擾
	float GetPlayerX();
	float GetPlayerY();

};