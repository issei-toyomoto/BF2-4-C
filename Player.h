#pragma once

class Player
{
private:
	int PlayerX;//�v���C���[���W
	int PlayerY;//�v���C���[���W


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