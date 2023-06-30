#pragma once
#include"AbstractScene.h"
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
	virtual ~Thunder() {};

	//�`��ȊO�̍X�V����������
	virtual AbstractScene* Update() override;

	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw() const  override;
};