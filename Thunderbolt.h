#pragma once

class Thunderbolt
{
private:
	int Num;//�摜�z��p

	int Img[6];
	int NowImg[2];
	int X[2];
	int Y[2];
	int Position[2];//���̃|�W�V�������ߗp�̕ϐ�(�_����@0:����@1:�E�� 2:���� 3:�E��)
	int AnimCnt[2];
	bool FinCloudAnimFlg[2];
	
		
public:
	static bool FinAnimFlg[2];
	//�R���X�g���N�^
	Thunderbolt();

	//�f�X�g���N�^
	~Thunderbolt() {};

	//�`��ȊO�̍X�V����������
	void Update(int Stage);

	//�`��Ɋւ��邱�Ƃ���������
	void Draw(int Stage) const;

	
	void ThunderboltAnim(int i);	//�����o��Ƃ��̃A�j���[�V����
	void ThunderboltPosition(int i, int Stage);
};