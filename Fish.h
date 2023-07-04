#pragma once
class Fish
{
private:
	int WaitTime;
	int Count;
	int f_Count;
	int Second;
	int FishRand;
	int f_PosX, f_PosY;
	bool FishFlg;
	/*int FishImage;*/
public:
	Fish();		//コンストラクタ
	void CreateFish();	//魚生成
	void FishArea();	//出現エリア判定
	void MoveFish();	//魚移動
};