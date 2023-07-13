#pragma once

class Thunder
{
private:
	int gCloudImg = LoadGraph("images/Stage_Cloud01.png");
	int gThunderImg= DrawBox(ThunderX, ThunderY, ThunderX +10, ThunderY + 10, GetColor(255, 0, 0), TRUE);
	int ThunderX=125, ThunderY=125;// ���̍��W
	int ThunderMoveX, ThunderMoveY;
	int Speed;// ���̑��x
	float ThunderAngle = 0.575f;// ���̊p�x
	int ThunderFlg; // ���̏�ԁi0...�ړ��� 1...���ɐڐG 2...�X�^�[�g��ԁj
	int WaitTime;// �҂�����
	void ChangeAngle();
	
public:

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