#pragma once

#define ENEMY_X 200
#define ENEMY_Y 185

struct EnemyData
{

};

class Enemy
{
private:
	int EnemyX;
	int EnemyY;
	int EnemyState;
	int EnemyLife;
	int EnemyFlg;
	int StartFlg;
	int EnemyImg[24];
	int FPScnt;
	int WaitTime;
	int i;

public:
	Enemy();   // �R���X�g���N�^
	~Enemy();  // �f�X�g���N�^

	void Enemyballoon();
	void EnemyMove();
	void StartMove();
	void EnemyCollision();

	//�`��ȊO�̍X�V����������
	void Update();
	//�`��̍X�V����������
	void Draw() const;
};

