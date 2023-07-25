#include "UI.h"
#include "bubble.h"

void UI::Update()
{
	TotalScore = 0;
	bubleScore = 0;
	TotalScore = bubleScore; /*+ EnemyScore*/
}

void UI::Draw() const
{
	for (int i = 0; i < 6; i++) {
		DrawGraph(50 + i * 20, 0, UINumber[i/* TotalScore*/], TRUE);     // プレイヤースコアに反映されるUI
		DrawGraph(235 + i * 20, 0, UINumber[0], TRUE);     // ハイスコアに反映されるUI
	}
	DrawGraph(35, 7, UIScore, TRUE);
	DrawGraph(200, 8, UITop, TRUE);
	DrawGraph(135, 28, UIStock, TRUE);
	DrawGraph(150, 28, UIStock, TRUE);
}
