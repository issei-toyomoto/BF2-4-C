#pragma once

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
	int WaitTime;

public:
	Enemy();   // �R���X�g���N�^
	~Enemy();  // �f�X�g���N�^

	void Enemyballoon();
	void EnemyMove();

	//�`��ȊO�̍X�V����������
	void Update();
	//�`��̍X�V����������
	void Draw() const;
};

