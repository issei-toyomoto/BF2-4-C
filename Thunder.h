#pragma once
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

	bool FinThunderboltAnimFlg[2];

public:
	//�R���X�g���N�^
	Thunder();
	//�f�X�g���N�^
	~Thunder() {};

	//�`��ȊO�̍X�V����������
	void Update();
	//�`��̍X�V����������
	void Draw();

	void ThunderAnim(int i);	//���̃A�j���[�V����
};

