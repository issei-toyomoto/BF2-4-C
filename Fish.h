#pragma once
#include"Player.h"
class Fish
{
private:
	int Count;
	int f_Count;
	int Second;
	int FishRand;
	float f_PosX;
	float f_PosY;
	bool FishFlg;
	int FishImage[10];
	int FishAnim;
	Player p;
	float P_X;
	float P_Y;
	int Target;
public:
	Fish();		//�R���X�g���N�^
	void Draw() const;	//������
	void Update();	//�o���G���A����
	void MoveFish();	//���ړ�
};