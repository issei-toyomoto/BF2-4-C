#pragma once

class Player
{
private:
	int MoveX;//�n�ʂł̈ړ�
	int MoveY;//�n�ʂł̈ړ�
	int BalloonNum;//���D�̐�
	int FloatingX;//�󒆂ł̈ړ�
	int FloatingY;//�󒆂ł̈ړ�
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