#pragma once
#include"Soundstorage.h"
#define DEBUG
//#define BUBBLE_X 320
//#define BUBBLE_Y 480
class bubble  {
private:
	Soundstorage soundstorage;
	/*int i;*/
	/*int y;*/
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
	//float bubbleX;// シャボン玉のX軸
	//float bubbleY;// シャボン玉のY軸
	int FPSCount; // フレームカウント
	/*int BubbleImg[4];
	int BubbleFlg;
	int Bubbledetection;
	int BubbleAnimCount;*/
	int BubbleAnimFase[4];
	int BubbleScoreImg;
	/*int BubbleX_Old;
	int BubbleY_Old;*/
	float px, py;
	int BubbleNumber;
	float Bubble_X;
	float Bubble_X_Old;
	int BubbleVEnemy[10];     // 敵完成までの仮想敵
	float BEnemyX;
	float BEnemyY;
	/*float px_old;*/

public:

	bubble();
	~bubble() {};

   
    void Update(int flg);
	void Draw() const;
	void BubbleSpawn(int n);
	void BubleCollision(int n);

	static int BubleScore;
};