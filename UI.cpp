#include"UI.h"

void UI::Update()
{
}

void UI::Draw() const
{
	for (int i = 0; i < 6; i++) {
		DrawGraph(50 + i * 20, 0, UINumber[0], TRUE);     // �v���C���[�X�R�A�ɔ��f�����UI
		DrawGraph(235 + i * 20, 0, UINumber[0], TRUE);     // �n�C�X�R�A�ɔ��f�����UI
	}
	DrawGraph(35, 7, UIScore, TRUE);
	DrawGraph(200, 8, UITop, TRUE);
	DrawGraph(135, 28, UIStock, TRUE);
	DrawGraph(150, 28, UIStock, TRUE);
}
