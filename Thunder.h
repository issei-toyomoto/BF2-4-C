#pragma once

class Thunder
{
private:
	int Num;
	int NowNum;

	int Img[3];
	int NowImg[2];

	int X[2];
	int Y[2];
	int VectorX[2];
	int VectorY[2];
	
	int AnimCnt[2];

	bool FinThunderboltAnimFlg[2];

	int Position[2];

public:
	static bool State[2];//(false:未使用 true:使用)
	static bool HitFlg[2];
	static bool InitFlg[2];
	static bool ThunderUnderSea[2];

	//コンストラクタ
	Thunder();
	//デストラクタ
	~Thunder() {};

	//描画以外の更新を実装する
	void Update(int Stage);
	//描画の更新を実装する
	void Draw()const;

	void ThunderPosition(int i, int Stage);
	void ThunderCollision(int i, int Stage);

	void ThunderAnim(int i);	//雷のアニメーション
};

