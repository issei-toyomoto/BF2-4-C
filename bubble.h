#pragma once
//#define BUBBLE_X 320
//#define BUBBLE_Y 480
class bubble  {
private:
	/*int i;*/
	/*int y;*/
	struct BubbleSet
	{
		float X;
		float Y;
		float detection;
		bool Flg;
		int Score;
		int X_Old;
		int Y_Old;
		int Img[4];
		int AnimCount;
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
public:

	bubble();
	~bubble() {};

   
    void Update();
	void Draw() const;
	void BubleCollision();

	static int BubleScore;
};