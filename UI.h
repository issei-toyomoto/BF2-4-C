#pragma once
#include "DxLib.h"
#include "GameMain.h"

class  UI
{
private:
	int UINumber[9];

public:
	// �R���X�g���N�^
	UI() {
		LoadDivGraph("images-20230711T024428Z-001/images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, UINumber);
	 }

	// �f�X�g���N�^
	virtual ~UI() {};
	// �`��ȊO�̍X�V����������
	virtual void Update();
	// �`��Ɋւ��邱�Ƃ���������
	void Draw(void) const;

};