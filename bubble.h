#pragma once
class bubble  {
private:
	int i;
	int y;
	float bubbleX=320;// シャボン玉のX軸
	float bubbleY=480;// シャボン玉のY軸
	int FPSCount=0; // フレームカウント
	int VectorBubbleX=-1; 
	
public:
	int BubbleFlg;

	void GenerationBubble() const; 
	void UpdateBubble();
};