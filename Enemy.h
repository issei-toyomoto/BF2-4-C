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

public:
	Enemy();   // コンストラクタ
	~Enemy();  // デストラクタ

	void EnemyStart();

	//描画以外の更新を実装する
	void Update();
	//描画の更新を実装する
	void Draw() const;
};

