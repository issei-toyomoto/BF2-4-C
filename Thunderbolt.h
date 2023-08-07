#pragma once
//**�X�e�[�W���Ƃ̉_�̈ʒu**//
//�X�e�[�W�P
#define Stage_1_X 
#define Stage_1_Y
//�X�e�[�W�Q


//**************************//
#define PlusPx 3		//px��������i�����蔻��j
#define Sea_Level 470	//�C�ʂ̍���
#define Inversion 1     //�����p

#define Thunder_Hide    0
#define Thunder_Display 1
#define Thuner_Touch    2

#define Cloud_Hide    0
#define Cloud_Display 1

class Thunder
{
private:
	int ThunderNum;//�X�e�[�W�̗��̐�
	int CloudNum;//�X�e�[�W�̉_�̐�

	//��
	struct T {
		int Img[3];
		int T_NowImg;//���݂̗��̉摜
		int X;
		int Y;
		int VX;
		int VY;
		int AnimCnt;//�A�j���[�V�����̃t���[���J�E���g
		int WaitTime;//�A�j���[�V�����܂ł̃J�E���g
		int StateFlg;//�i�O�F�\������Ă��Ȃ��@�P�F�\������Ă���@�Q�F�v���C���[�ƐڐG�����j
	};
	T thunder[2];
	
	//�����o��Ƃ��̗�
	struct OT{
		int Img[5];
		int Now_Img;
		int X;
		int Y;
		int OTAnimCnt;
		bool OTFlg;
	};
	OT OutThunder[2];

	//�_
	struct C {
		int Img[3];
		int C_NowImg;//���݂̉_�̉摜
		int X;
		int Y;
		int AnimCnt;
		int WaitTimeFlg;
		int WaitTime;
		int WaitTimeCnt;
		int StopAnimCnt;
		int StateFlg;//(0:�\������Ă��Ȃ� 1:�\������Ă���)
	};
	C Cloud[2];

	int Speed;// ���̑��x

	int NowStage;//���݂̃X�e�[�W

	bool TouchFlg;//���ƐG�ꂽ���Ƃ��v���C���[�ɓ`����悤
		
public:
	//�R���X�g���N�^
	Thunder ();

	//�f�X�g���N�^
	~Thunder() {};

	//�`��ȊO�̍X�V����������
	void Update(int i, int Stage);

	//�`��Ɋւ��邱�Ƃ���������
	void Draw(int i) const;

	void DrawThunder() const;
	void DrawCloud() const;
	void DrawOutThunder() const;

	void StageCollision(int i);

	void ThunderAnim(int i);	//���̃A�j���[�V����
	void CloudAnim(int i);		//�_�̃A�j���[�V����
	void OutThunderAnim(int i);	//�����o��Ƃ��̃A�j���[�V����

	void InitCloud();//�_�̏�����
	void CloudPosition();//�X�e�[�W���Ƃ̉_�̈ʒu
};