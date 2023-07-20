#pragma once

#define ENEMY_X 200
#define ENEMY_Y 185
#define ENEMY_W 55
#define ENEMY_H 65
#define ENEMY_MAX 3

class Enemy
{
private:
	int StartFlg;      // スタート状態か判定する用
	int EnemyImg[24];  // 敵の画像格納用
	int FPScnt;        // FPSカウント
	int StartMotion;   // スタート時、敵のモーション管理用
	float Px, Py;      // プレイヤーのX座標、Y座標

	// 敵のデータ(構造体)
	struct ENEMY
	{
		float x = 0;     // 敵のX座標
		float y = 0;     // 敵のY座標
		int state = 0;   // 敵の状態(0:ピンク 1:緑 2:黄色)
		int life = 2;    // 敵のHP
		int flg = 0;     // 敵の画像番号用
		float speed = 0.4f; // 敵の移動速度
	};

	struct ENEMY enemy[ENEMY_MAX];   // 敵のデータ(変数宣言)

public:
	Enemy();   // コンストラクタ
	~Enemy();  // デストラクタ

	void EnemyInit();       // 敵の初期化処理
	void EnemyMove();       // 敵の移動処理
	void StartMove();       // 敵のスタート処理
	void EnemyUp();         // 敵の浮上モーション処理
	void EnemyDown();       // 敵の降下モーション処理
	void EnemyCollision();  // 敵同士の当たり判定
	void StageCollision();  // 敵とステージの当たり判定

	
	//描画以外の更新を実装する
	void Update();
	//描画の更新を実装する
	void Draw() const;
};

