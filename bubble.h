#pragma once
class bubble  {
private:
	int i;
	int y;
	float bubbleX=320;// �V���{���ʂ�X��
	float bubbleY=480;// �V���{���ʂ�Y��
	int FPSCount=0; // �t���[���J�E���g
	int VectorBubbleX=-1; 
	
public:
	int BubbleFlg;

	void GenerationBubble() const; 
	void UpdateBubble();
};