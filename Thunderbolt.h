#pragma once

class Thunder
{
private:
	int gCloudImg = LoadGraph("Stage_Cloud01.png");
	int ThunderX, ThunderY;// ���̍��W
	int ThunderMoveX, ThunderMoveY;
	int Speed;// ���̑��x
	float ThunderAngle = 0.575f;// ���̊p�x
	int ThunderFlg; // ���̏�ԁi0...�ړ��� 1...���ɐڐG 2...�X�^�[�g��ԁj
	int WaitTime;// �҂�����
	void ChangeAngle();
	void MoveThunder();

	//�R���X�g���N�^
	Thunder() {};

	//�f�X�g���N�^
	~Thunder() {};

	//�`��ȊO�̍X�V����������
	void Update();

	//�`��Ɋւ��邱�Ƃ���������
	void Draw() const;
};