#pragma once
//#define BUBBLE_X 320
//#define BUBBLE_Y 480
class bubble  {
private:
	/*int i;*/
	/*int y;*/
	float bubbleX;// �V���{���ʂ�X��
	float bubbleY;// �V���{���ʂ�Y��
	int FPSCount; // �t���[���J�E���g
	int VectorBubbleX=-1; 
	int BubbleImg[4];
	int BubleFlg;
	int BubbleFlg;
	int BubleScore;

	float px, py;
	//int HitBoxPlayer(Player* p, bubble* e);
public:

	bubble();
	~bubble() {};

   
    void Update();
	void Draw() const;
	void BubleCollision();
	void BubbleScore(int score);
};