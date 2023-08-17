#pragma once
#include"Soundstorage.h"
#define DEBUG
class bubble  {
private:
	Soundstorage ss;
	// シャボン玉の構造体
	struct BubbleSet
	{
		float X;
		float Y;
		float detection;
		bool Flg;
		int Score;
		float X_Old;
		float Y_Old;
		int Img[4];
		int AnimCount;
		int Event;
		int Count;

	};
	struct BubbleSet Bubble[6];
	int FPSCount; // フレームカウント
	int BubbleScoreImg;    // バブルのスコアカウント
	float px, py;          // プレイヤーの座標を入れる変数
	int BubbleNumber;      // シャボン玉の添え字
	int BubbleVEnemy[10];     // 敵完成までの仮想敵
	float BEnemyX;	
	float BEnemyY;

public:

	bubble();
	~bubble() {};

   
    void Update(int flg);
	void Draw() const;

	static int BubleScore;
};