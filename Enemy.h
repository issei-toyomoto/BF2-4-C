#pragma once

#define ENEMY_X 200
#define ENEMY_Y 185

struct EnemyData
{
	float x;
	float y;
	int state;
	int life;
	int flg;
	float speed;
};

class Enemy
{
private:
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

