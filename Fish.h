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
	Fish();		//�R���X�g���N�^
	void CreateFish();	//������
	void FishArea();	//�o���G���A����
	void MoveFish();	//���ړ�
};