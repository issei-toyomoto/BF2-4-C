#pragma once
class bubble  {
private:
	int bubbleX=320;// �V���{���ʂ�X��
	int bubbleY=480;// �V���{���ʂ�Y��
	int FPSCount=0; // �t���[���J�E���g
	int VectorBubbleX=-1;
	
public:
	void GenerationBubble() const;
	void UpdateBubble();
};