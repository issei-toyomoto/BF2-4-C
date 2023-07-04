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
	Enemy();   // コンストラクタ
	~Enemy();  // デストラクタ

	void Enemyballoon();
	void EnemyMove();

	//描画以外の更新を実装する
	void Update();
	//描画の更新を実装する
	void Draw() const;
};

