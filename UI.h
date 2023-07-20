#pragma once
#include "DxLib.h"
#include "GameMain.h"

class  UI
{
private:
	int UINumber[9];

public:
	// コンストラクタ
	UI() {
		LoadDivGraph("images-20230711T024428Z-001/images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, UINumber);
	 }

	// デストラクタ
	virtual ~UI() {};
	// 描画以外の更新を実装する
	virtual void Update();
	// 描画に関することを実装する
	void Draw(void) const;

};