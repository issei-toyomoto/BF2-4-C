#pragma once

class Enemy
{
private:
	int EnemyX;
	int EnemyY;

public:
	Enemy();   // �R���X�g���N�^
	~Enemy();  // �f�X�g���N�^
	//�`��ȊO�̍X�V����������
	void Update();
	//�`��̍X�V����������
	void Draw() const;
};

