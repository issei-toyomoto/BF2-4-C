#pragma once
#include"Player.h"
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
	int FishImage[10];
	Player p;
public:
	Fish();		//�R���X�g���N�^
	void Draw();	//������
	void Update();	//�o���G���A����
	void MoveFish();	//���ړ�
};