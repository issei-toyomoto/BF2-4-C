#pragma once

#define ENEMY_X 200    // 敵[1]のX座標
#define ENEMY_Y 185    // 敵[1]のY座標
#define ENEMY_W 55     // 敵[1]の幅
#define ENEMY_H 65     // 敵[1]の高さ
#define ENEMY_MAX 3    // 敵の最大数

class Enemy
{
private:
	int StartFlg;      // スタート状態か判定する用
	int EnemyImg[24];  // 敵の画像格納用
	int FPScnt;        // FPSカウント
	int StartMotion;   // スタート時、敵のモーション管理用
	float Px, Py;      // プレイヤーのX座標、Y座標
	int HitFlg;        // 敵同士の当たり判定用 
	int HitPFlg;       // プレイヤーと敵の当たり判定用
	float EnXL[ENEMY_MAX], EnYL[ENEMY_MAX]; //左上
	float EnXR[ENEMY_MAX], EnYR[ENEMY_MAX]; //右下

	// 敵のデータ(構造体)
	struct ENEMY
	{
		float x = 0;        // 敵のX座標
		float y = 0;        // 敵のY座標
		int state = 0;      // 敵の状態(0:ピンク 1:緑 2:黄色)
		int life = 2;       // 敵のHP(0:死亡 1:パラシュート状態 2:風船1個状態)
		int flg = 0;        // 敵の画像番号用
		float speed = 0.6f; // 敵の移動速度
		int direction = 0;  // 敵の向いてる向き(0:左 1:右)
		int ground = 0;     // 地面に触れているか(0:触れてない 1:触れている)
	};

	struct ENEMY enemy[ENEMY_MAX];   // 敵のデータ(変数宣言)

public:
	Enemy();   // コンストラクタ
	~Enemy();  // デストラクタ

	void EnemyInit();  // 敵の初期化処理
	void EnemyMove();  // 敵の移動処理
	void StartMove();  // 敵のスタート処理
	void EnemyUp();    // 敵の浮上モーション処理
	void EnemyDown();  // 敵の降下モーション処理
	int HitEnemy();    // 敵同士の当たり判定
	int HitPlayer();   // 敵とプレイヤーの当たり判定
	void HitStage();   // 敵とステージの当たり判定

	
	//描画以外の更新を実装する
	void Update();
	//描画の更新を実装する
	void Draw() const;
};

