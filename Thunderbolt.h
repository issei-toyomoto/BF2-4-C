#pragma once

class Thunder
{
private:
	int gCloudImg = LoadGraph("images/Stage_Cloud01.png");
	int gThunderImg[2];

	int ThunderX=125, ThunderY=125;// ���̍��W

	int Speed;// ���̑��x
	int ThunderFlg; // ���̏�ԁi0...�ړ��� 1...���ɐڐG 2...�X�^�[�g��ԁj
	int WaitTime=5;// �҂�����
	
	
public:
	int ThunderMoveX, ThunderMoveY;
	float ThunderAngle = 0.575f;// ���̊p�x
	void MoveThunder();

	//�R���X�g���N�^
	Thunder ();

	//�f�X�g���N�^
	~Thunder() {};

	//�`��ȊO�̍X�V����������
	void Update();

	//�`��Ɋւ��邱�Ƃ���������
	void Draw() const;

	void ChangeAngle();
};