#pragma once
#define BUBBLE_X 320
#define BUBBLE_Y 480
class bubble  {
private:
	int i;
	int y;
	float bubbleX=320;// �V���{���ʂ�X��
	float bubbleY=480;// �V���{���ʂ�Y��
	int FPSCount=0; // �t���[���J�E���g
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