#pragma once

#define PlusPx 3			//px��������i�����蔻��j
#define COR 1
#define Sea_Level 470		//�C�ʂ̍���

class Thunder
{
private:
	int gThunderImg[3];
	int gCloudImg[3];

	int ThunderX = 100;
	int ThunderY = 100;// ���̍��W
	int VectorX;
	int VectorY;

	int Speed;// ���̑��x
	int ThunderAnimCnt;  
	int FlashFlg;

	int NowImg;
	int NowStage;
		
public:
	//�R���X�g���N�^
	Thunder ();

	//�f�X�g���N�^
	~Thunder() {};

	//�`��ȊO�̍X�V����������
	void Update(int Stage);

	//�`��Ɋւ��邱�Ƃ���������
	void Draw() const;

	void MoveThunderX();
	void MoveThunderY();

	void StageCollision();

	void ThunderAnim();
};