#pragma once
#include"Soundstorage.h"
#define DEBUG
class bubble  {
private:
	Soundstorage ss;
	// �V���{���ʂ̍\����
	struct BubbleSet
	{
		float X;
		float Y;
		float detection;
		bool Flg;
		int Score;
		float X_Old;
		float Y_Old;
		int Img[4];
		int AnimCount;
		int Event;
		int Count;

	};
	struct BubbleSet Bubble[6];
	int FPSCount; // �t���[���J�E���g
	int BubbleScoreImg;    // �o�u���̃X�R�A�J�E���g
	float px, py;          // �v���C���[�̍��W������ϐ�
	int BubbleNumber;      // �V���{���ʂ̓Y����
	int BubbleVEnemy[10];     // �G�����܂ł̉��z�G
	float BEnemyX;	
	float BEnemyY;

public:

	bubble();
	~bubble() {};

   
    void Update(int flg);
	void Draw() const;

	static int BubleScore;
};