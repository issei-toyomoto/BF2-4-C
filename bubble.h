#pragma once
#define BUBBLE_X 320
#define BUBBLE_Y 480
class bubble  {
private:
	int i;
	int y;
	float bubbleX=320;// シャボン玉のX軸
	float bubbleY=480;// シャボン玉のY軸
	int FPSCount=0; // フレームカウント
	int VectorBubbleX=-1; 
	int BubbleImg[3];
	int BubleAnim;

	float px, py;
	//int HitBoxPlayer(Player* p, bubble* e);
public:
	int BubbleFlg;

	bubble();
	~bubble() {};

   
    void Update();
	void Draw() const;
	void BubleCollision();
};