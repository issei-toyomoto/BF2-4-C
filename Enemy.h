#pragma once

#define ENEMY_X 200    // 敵[0]のX座標
#define ENEMY_Y 185    // 敵[0]のY座標
#define ENEMY_W 55     // 敵の幅
#define ENEMY_H 65     // 敵の高さ
#define ENEMY_MAX 3    // 敵の最大数

class Enemy
{
private:
	int StartFlg;      // スタート状態か判定する用
	int EnemyImg[3][24];  // 敵の画像格納用
	int Fcnt;        // FPSカウント
	int StartMotion;   // スタート時、敵のモーション管理用
	float Px, Py;      // プレイヤーのX座標、Y座標
	int HitFlg;        // 敵同士の当たり判定用 
	int HitPeFlg;
	float EnXL[ENEMY_MAX], EnYL[ENEMY_MAX]; //敵の左上座標
	float EnXR[ENEMY_MAX], EnYR[ENEMY_MAX]; //敵の右下座標
	int UpCnt, DownCnt;

	const float MinY = -19.0f;
	
	// 敵のデータ(構造体)
	struct ENEMY
	{
		float x = 0.0f;        // 敵のX座標
		float y = 0.0f;        // 敵のY座標
		float vecx = 0.0f;  // 敵の移動量X
		float vecy = 0.0f;  // 敵の移動量Y
		int state = 0;      // 敵の状態(0:ピンク 1:緑 2:黄色)
		int life = 2;       // 敵のHP(0:死亡 1:パラシュート状態 2:風船1個状態)
		int flg = 0;        // 敵の画像番号用
		int direction = 0;  // 敵の向いてる向き(0:左 1:右)
		int ground = 0;     // 地面に触れているか(0:触れてない 1:触れている)
		int die = 0;        // 敵死亡時用
		int ran = 0;
	};

	struct ENEMY enemy[ENEMY_MAX];   // 敵のデータ(変数宣言)

public:
	 static int HitPFlg;       // プレイヤーと敵の当たり判定用

	Enemy();   // コンストラクタ
	~Enemy();  // デストラクタ

	void EnemyInit();       // 敵の初期化処理
	void EnemyMove(int i);  // 敵の移動処理
	void StartMove();       // 敵のスタート処理
	void EnemyUp(int e);    // 敵の浮上モーション処理
	void EnemyDown(int e);  // 敵の降下モーション処理
	void EnemyLeft(int e);  // 敵の左移動処理
	void EnemyRight(int e); // 敵の右移動処理
	void HitStage(int e);   // 敵とステージの当たり判定
	int HitEnemy(int e);    // 敵同士の当たり判定
	int HitStart(int e);    // 敵とプレイヤーの当たり判定(スタート時)
	int HitPlayer(int e);   // 敵とプレイヤーの当たり判定
	void EnemyDie(int e);   // 敵の死亡モーション処理
	void EnemyPara(int e);  // 敵のパラシュート処理
	
	//描画以外の更新を実装する
	void Update();
	//描画の更新を実装する
	void Draw() const;
};

