#pragma once
#include "DxLib.h"
#include "bubble.h"
#include"Player.h"
class  UI
{
private:
	bubble Bubble;
	Player player;
	int UIScore;
	int UITop;
	int UIStock;
	int UINumber[10];
	int bubleScore;
	int TotalScore;
	int TScore1;
	int TScore10;
	int TScore100;
	int TScore1000;
	int TScore10000;
	int TScore100000;
	int HScore1;
	int HScore10;
	int HScore100;
	int HScore1000;
	int HScore10000;
	int HScore100000;
	int LifeCnt;

	int UIflg;     // �f�o�b�O�p

public:
	// �R���X�g���N�^
	UI();

	// �f�X�g���N�^
	~UI();
	// �`��ȊO�̍X�V����������
	void Update(int flg);
	// �`��Ɋւ��邱�Ƃ���������
	void Draw() const;
	static int HighScore;
};