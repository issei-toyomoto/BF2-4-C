#pragma once
#include "DxLib.h"
#include "bubble.h"
#include "GameMain.h"

class  UI
{
private:
	bubble Bubble;
	GameMain gamemain;
	int UIScore;
	int UITop;
	int UIStock;
	int UINumber[9];
	int bubleScore;
	int TotalScore;
	int Score1;
	int Score10;
	int Score100;
	int Score1000;
	int Score10000;
	int Score100000;
	int HighScore;

public:
	// �R���X�g���N�^
	UI();

	// �f�X�g���N�^
	~UI();
	// �`��ȊO�̍X�V����������
	void Update();
	// �`��Ɋւ��邱�Ƃ���������
	void Draw() const;

};