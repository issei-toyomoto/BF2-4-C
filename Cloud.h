#pragma once
//**�X�e�[�W���Ƃ̉_�̈ʒu**//
//�X�e�[�W�P
#define Stage_1_X 300
#define Stage_1_Y 70
//�X�e�[�W�Q
#define Stage_2_X_0 50
#define Stage_2_Y_0 150 
#define Stage_2_X_1 450
#define Stage_2_Y_1 150
//�X�e�[�W�R

//**************************//

class Cloud
{
private:
	int Num;

	int Img[3];			//�摜�z��
	int NowImg[2];		//���݂̃X�e�[�W
	int AnimCnt[2];		//�A�j���[�V�����̃t���[���J�E���g�p
	int WaitTime[2];	//�A�j���[�V�����܂ł̎���
	int WaitTimeFlg[2];	//�A�j���[�V�����̎��Ԃ����߂�p

public:
	//�R���X�g���N�^
	Cloud();
	//�f�X�g���N�^
	~Cloud() {};

	//�`��ȊO�̍X�V����������
	void Update();
	//�`��̍X�V����������
	void Draw(int Stage) const;

	//�X�e�[�W���Ƃ̉_�̈ʒu
	void StageDrawCloud(int Stage) const;

	//�_�̃A�j���[�V����
	void AnimCloud();
};

