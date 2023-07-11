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
	Enemy();   // コンストラクタ
	~Enemy();  // デストラクタ

	void Enemyballoon();
	void EnemyMove();
	void StartMove();
	void EnemyCollision();

	//描画以外の更新を実装する
	void Update();
	//描画の更新を実装する
	void Draw() const;
};

