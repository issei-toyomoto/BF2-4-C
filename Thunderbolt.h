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
		int X;
		int Y;
		int VX;
		int VY;
		int AnimCnt;
	};	
	T thunder[2];


	struct C {
		int Img[3];
		int X;
		int Y;
		int AnimCnt;
	};
	//�_
	
	C Cloud[2];

	int Speed;// ���̑��x
	
	int FlashFlg;

	int NowImg;
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

	void MoveThunderX();
	void MoveThunderY();

	void StageCollision();

	void ThunderAnim();
	void CloudAnim();
};