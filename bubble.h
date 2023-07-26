#pragma once
//#define BUBBLE_X 320
//#define BUBBLE_Y 480
class bubble  {
private:
	/*int i;*/
	/*int y;*/
	float bubbleX;// シャボン玉のX軸
	float bubbleY;// シャボン玉のY軸
	int FPSCount; // フレームカウント
	int VectorBubbleX=-1; 
	int BubbleImg[4];
	int BubbleFlg;
	float Bubbledetection;
	int BubbleAnimCount;
	int BubbleAnimFase[4];


	float px, py;
	//int HitBoxPlayer(Player* p, bubble* e);
public:

	bubble();
	~bubble() {};

   
    void Update();
	void Draw() const;
	void BubleCollision();
	void BubbleScore();

	static int BubleScore;
};