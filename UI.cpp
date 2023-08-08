#include "UI.h"
#include "bubble.h"
#include "GameMain.h"
#include "Common.h"
#include <math.h>

#define DEBUG

UI::UI()
{
	LoadDivGraph("images-20230711T024428Z-001/images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, UINumber);
	UIScore = LoadGraph("images-20230711T024428Z-001/images/UI/UI_Score.png", TRUE);
	UITop = LoadGraph("images-20230711T024428Z-001/images/UI/UI_HiScore.png", TRUE);
	UIStock = LoadGraph("images-20230711T024428Z-001/images/UI/UI_Stock.png", TRUE);
	TotalScore = 0;
	bubleScore = 0;
	Score1 = 0;
	Score10 = 0;
	Score100 = 0;
	Score1000 = 0;
	Score10000 = 0;
	Score100000 = 0;
	HighScore = 0;
};
UI::~UI()
{
}
void UI::Update()
{
	bubleScore = Bubble.BubleScore;
	TotalScore = bubleScore;
	Score1      = TotalScore % 10;
	Score10     = (TotalScore % 100) / 10;
	Score100    = (TotalScore % 1000) / 100;
	Score1000   = (TotalScore % 10000) / 1000;
	Score10000  = (TotalScore % 100000) / 10000;
	Score100000 = TotalScore / 100000;
	if (gamemain.GameOverFlg == 1) {
		if (TotalScore > HighScore) {
			HighScore = TotalScore;
			TotalScore = 0;
		}
		TotalScore = 0;
	}
}

void UI::Draw() const
{
	// プレイヤースコアに反映されるUI
	DrawGraph(50, 0, UINumber[Score100000], TRUE);
	DrawGraph(70, 0, UINumber[Score10000], TRUE); 
	DrawGraph(90, 0, UINumber[Score1000], TRUE);
	DrawGraph(110, 0, UINumber[Score100], TRUE);
	DrawGraph(130, 0, UINumber[Score10], TRUE);
	DrawGraph(150, 0, UINumber[Score1], TRUE);
	// ハイスコアに反映されるUI
	DrawGraph(235, 0, UINumber[Score100000], TRUE);    
	DrawGraph(255, 0, UINumber[Score10000], TRUE);
	DrawGraph(275, 0, UINumber[Score1000], TRUE);
	DrawGraph(295, 0, UINumber[Score100], TRUE);
	DrawGraph(315, 0, UINumber[Score10], TRUE);
	DrawGraph(335, 0, UINumber[Score1], TRUE);
	DrawGraph(35, 7, UIScore, TRUE);
	DrawGraph(200, 8, UITop, TRUE);
	DrawGraph(135, 28, UIStock, TRUE);
	DrawGraph(150, 28, UIStock, TRUE);

#ifdef DEBUG
	DrawFormatString(200, 0, C_RED, "%d", TotalScore);
#endif // DEBUG

}
