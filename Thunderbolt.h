#pragma once
class Thunder 
{
private:
	int ThunderX,ThunderY;// ���̍��W
	int ThunderMoveX, ThunderMoveY;
	int Speed;// ���̑��x
	float ThunderAngle=0.575f;// ���̊p�x
	int ThunderFlg; // ���̏�ԁi0...�ړ��� 1...���ɐڐG 2...�X�^�[�g��ԁj
	int WaitTime;// �҂�����
	void ChangeAngle();
};