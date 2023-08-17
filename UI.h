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

	int UIflg;     // デバッグ用

public:
	// コンストラクタ
	UI();

	// デストラクタ
	~UI();
	// 描画以外の更新を実装する
	void Update(int flg);
	// 描画に関することを実装する
	void Draw() const;
	static int HighScore;
};