#pragma once
class Fish
{
private:
	int WaitTime;
	int PosX, PosY;
public:
	void CreateFish();	//������
	void HitBoxArea();	//�o���G���A����
	void DrawFish();	//���`��
	void MoveFish();	//���ړ�
};