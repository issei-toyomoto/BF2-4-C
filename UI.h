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
	// コンストラクタ
	UI();

	// デストラクタ
	~UI();
	// 描画以外の更新を実装する
	void Update();
	// 描画に関することを実装する
	void Draw() const;

};