#pragma once
#include "Player.h"

#define ENEMY_X 200
#define ENEMY_Y 185

// 敵のデータ(構造体)
struct EnemyData
{
	float x;     // 敵のX座標
	float y;     // 敵のY座標
	int state;   // 敵の状態(0:ピンク 1:緑 2:黄色)
	int life;    // 敵のHP
	int flg;     // 敵の画像番号用
	float speed; // 敵の移動速度
};

class Enemy
{
private:
	int StartFlg;      // スタート状態か判定する用
	int EnemyImg[24];  // 敵の画像格納用
	int FPScnt;        // FPSカウント
	int i;             // スタート時、敵のモーション管理用
	EnemyData enemy;   // 敵のデータ(変数宣言)

	Player player;     // プレイヤーオブジェクト化
	float Px,Py;         // プレイヤーのX座標、Y座標

public:
	Enemy();   // コンストラクタ
	~Enemy();  // デストラクタ

	void EnemyMove();       // 敵の移動処理
	void StartMove();       // 敵のスタート処理
	void EnemyCollision();  // 敵とステージの当たり判定処理

	//描画以外の更新を実装する
	void Update();
	//描画の更新を実装する
	void Draw() const;
};

