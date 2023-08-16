#pragma once

class Thunder
{
private:
	int Num;
	int NowNum;

	int Img[3];
	int NowImg[2];

	int X[2];
	int Y[2];
	int VectorX[2];
	int VectorY[2];
	
	int AnimCnt[2];

	bool FinThunderboltAnimFlg[2];

	int Position[2];

public:
	static bool State[2];//(false:���g�p true:�g�p)
	static bool HitFlg[2];
	static bool InitFlg[2];
	static bool ThunderUnderSea[2];

	//�R���X�g���N�^
	Thunder();
	//�f�X�g���N�^
	~Thunder() {};

	//�`��ȊO�̍X�V����������
	void Update(int Stage);
	//�`��̍X�V����������
	void Draw()const;

	void ThunderPosition(int i, int Stage);
	void ThunderCollision(int i, int Stage);

	void ThunderAnim(int i);	//���̃A�j���[�V����
};

