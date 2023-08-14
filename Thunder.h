#pragma once
#define NO_USE 0
#define USE 1

class Thunder
{
private:
	int Num;

	int Img[3];
	int NowImg[2];

	int X[2];
	int Y[2];
	int VectorX[2];
	int VectorY[2];
	int State[2];//(0:���g�p 1:�g�p)
	int AnimCnt[2];

	bool FinThunderboltAnimFlg[2];

public:
	//�R���X�g���N�^
	Thunder();
	//�f�X�g���N�^
	~Thunder() {};

	//�`��ȊO�̍X�V����������
	void Update();
	//�`��̍X�V����������
	void Draw()const;

	void ThunderAnim(int i);	//���̃A�j���[�V����
};

