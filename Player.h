#pragma once

class Player
{
private:
	int PlayerX;//�v���C���[X���W
	int PlayerY;//�v���C���[Y���W
	int VectorX;//�x�N�g��X
	int VectorY;//�x�N�g��Y
	
	int XStick;
	int YStick;

public:
	//�R���X�g���N�^
	Player() {};
	//�f�X�g���N�^
	~Player() {};
	//�`��ȊO�̍X�V����������
	void Update();
	//�`��̍X�V����������
	void Draw() const;
};