#pragma once

class Enemy
{
private:
	int EnemyX;
	int EnemyY;

public:
	Enemy();   // コンストラクタ
	~Enemy();  // デストラクタ
	//描画以外の更新を実装する
	void Update();
	//描画の更新を実装する
	void Draw() const;
};

