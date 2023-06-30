#pragma once
class bubble  {
private:
	int bubbleX=320;// シャボン玉のX軸
	int bubbleY=480;// シャボン玉のY軸
	int FPSCount=0; // フレームカウント
public:
	void GenerationBubble() const;
	void UpdateBubble();
};