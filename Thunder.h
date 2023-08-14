#pragma once
#define NO_USE 0
#define USE 1

class Thunder
{
private:
	int Num;

	int Img[3];
	int NowImg[2];

	int X[2];
	int Y[2];
	int VectorX[2];
	int VectorY[2];
	int State[2];//(0:未使用 1:使用)
	int AnimCnt[2];

	bool FinThunderboltAnimFlg[2];

public:
	//コンストラクタ
	Thunder();
	//デストラクタ
	~Thunder() {};

	//描画以外の更新を実装する
	void Update();
	//描画の更新を実装する
	void Draw()const;

	void ThunderAnim(int i);	//雷のアニメーション
};

