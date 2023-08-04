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

class Thunder
{
private:

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
	};	
	T thunder[2];

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
	};
	C Cloud[2];

	int Speed;// ���̑��x
	
	int FlashFlg;

	
	

	int NowStage;
		
public:
	//�R���X�g���N�^
	Thunder ();

	//�f�X�g���N�^
	~Thunder() {};

	//�`��ȊO�̍X�V����������
	void Update(int Stage);

	//�`��Ɋւ��邱�Ƃ���������
	void Draw() const;

	void DrawThunder() const;
	void DrawCloud() const;

	void MoveThunderX();
	void MoveThunderY();

	void StageCollision();

	void ThunderAnim();
	void CloudAnim();

	void CloudPosition();
};