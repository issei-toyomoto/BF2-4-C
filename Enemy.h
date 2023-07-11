#pragma once

#define ENEMY_X 200
#define ENEMY_Y 185

struct EnemyData
{
	int x;
	int y;
	int state;
	int life;
	int flg;
	int speed;
};

class Enemy
{
private:
	/*int EnemyX;
	int EnemyY;
	int EnemyState;
	int EnemyLife;
	int EnemyFlg;*/
	int StartFlg;
	int EnemyImg[24];
	int FPScnt;
	int WaitTime;
	int i;
	EnemyData enemy;

public:
	Enemy();   // �R���X�g���N�^
	~Enemy();  // �f�X�g���N�^

	void EnemyMove();
	void StartMove();
	void EnemyCollision();

	//�`��ȊO�̍X�V����������
	void Update();
	//�`��̍X�V����������
	void Draw() const;
};

