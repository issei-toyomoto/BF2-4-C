#pragma once
#include "DxLib.h"

class  UI
{
private:
	int UIScore;
	int UITop;
	int UIStock;
	int UINumber[9];
	int bubleScore;
	int TotalScore;

public:
	// �R���X�g���N�^
	UI() {
		LoadDivGraph("images-20230711T024428Z-001/images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, UINumber);
		UIScore = LoadGraph("images-20230711T024428Z-001/images/UI/UI_Score.png",TRUE);
		UITop = LoadGraph("images-20230711T024428Z-001/images/UI/UI_HiScore.png", TRUE);
		UIStock = LoadGraph("images-20230711T024428Z-001/images/UI/UI_Stock.png", TRUE);
	};

	// �f�X�g���N�^
	~UI() {};
	// �`��ȊO�̍X�V����������
	void Update();
	// �`��Ɋւ��邱�Ƃ���������
	void Draw() const;

};