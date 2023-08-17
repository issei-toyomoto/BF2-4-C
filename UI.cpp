#include "UI.h"
#include "bubble.h"
#include "Common.h"
#include "Enemy.h"
#include <math.h>

//#define DEBUG
int UI::HighScore;

UI::UI()
{
	LoadDivGraph("images-20230711T024428Z-001/images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, UINumber);
	UIScore = LoadGraph("images-20230711T024428Z-001/images/UI/UI_Score.png", TRUE);
	UITop = LoadGraph("images-20230711T024428Z-001/images/UI/UI_HiScore.png", TRUE);
	UIStock = LoadGraph("images-20230711T024428Z-001/images/UI/UI_Stock.png", TRUE);
	TotalScore = 0;
	bubleScore = 0;
	EnemyScore = 0;
	TScore1 = 0;
	HScore1 = 0;
	TScore10 = 0;
	HScore10 = 0;
	TScore100 = 0;
	HScore100 = 0;
	TScore1000 = 0;
	HScore1000 = 0;
	TScore10000 = 0;
	HScore10000 = 0;
	TScore100000 = 0;
	HScore100000 = 0;
	LifeCnt = 0;
	UIflg = 0;
};
UI::~UI()
{
}
void UI::Update(int flg)
{
	LifeCnt = player.Life;
	bubleScore = Bubble.BubleScore;
	TotalScore = bubleScore + Enemy::EnemyTotalScore;
	if (TotalScore > HighScore) {
		HighScore = TotalScore;
	}
	TScore1      = TotalScore % 10;
	TScore10     = (TotalScore % 100) / 10;
	TScore100    = (TotalScore % 1000) / 100;
	TScore1000   = (TotalScore % 10000) / 1000;
	TScore10000  = (TotalScore % 100000) / 10000;
	TScore100000 = TotalScore / 100000;
	HScore1      = HighScore % 10;
	HScore10 = (HighScore % 100) / 10;
	HScore100 = (HighScore % 1000) / 100;
	HScore1000 = (HighScore % 10000) / 1000;
	HScore10000 = (HighScore % 100000) / 10000;
	HScore100000 = HighScore / 100000;
	if (flg == 1) {
		if (TotalScore > HighScore) {
			/*UIflg = flg;*/
			HighScore = TotalScore;
			/*TotalScore = 0;*/
		}
		/*UIflg = flg;*/
		bubleScore = 0;
		TotalScore = 0;
	}
}

void UI::Draw() const
{
	for (int i = 0; i < LifeCnt; i++) {
		DrawGraph(135 + 15 * i, 28, UIStock, TRUE);
	}
	// プレイヤースコアに反映されるUI
	DrawGraph(50, 0, UINumber[TScore100000], TRUE);
	DrawGraph(70, 0, UINumber[TScore10000], TRUE); 
	DrawGraph(90, 0, UINumber[TScore1000], TRUE);
	DrawGraph(110, 0, UINumber[TScore100], TRUE);
	DrawGraph(130, 0, UINumber[TScore10], TRUE);
	DrawGraph(150, 0, UINumber[TScore1], TRUE);
	// ハイスコアに反映されるUI
	DrawGraph(235, 0, UINumber[HScore100000], TRUE);    
	DrawGraph(255, 0, UINumber[HScore10000], TRUE);
	DrawGraph(275, 0, UINumber[HScore1000], TRUE);
	DrawGraph(295, 0, UINumber[HScore100], TRUE);
	DrawGraph(315, 0, UINumber[HScore10], TRUE);
	DrawGraph(335, 0, UINumber[HScore1], TRUE);
	DrawGraph(35, 7, UIScore, TRUE);
	DrawGraph(200, 8, UITop, TRUE);

}
