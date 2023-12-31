#pragma once
//**********画像変数の配列要素番号**********//
//待機状態（風船２個）
#define P_Img_Wait_Ballon_2_0 0
#define P_Img_Wait_Ballon_2_1 1
#define P_Img_Wait_Ballon_2_2 2
#define P_Img_Wait_Red_Ballon_2 3
//待機状態（風船１個）
#define P_Img_Wait_Ballon_1_0 4
#define P_Img_Wait_Ballon_1_1 5
#define P_Img_Wait_Ballon_1_2 6
#define P_Img_Wait_Red_Ballon_1 7
//走る（風船２個）
#define P_Img_Run_Ballon_2_0     8
#define P_Img_Run_Ballon_2_1     9
#define P_Img_Run_Ballon_2_2     10
#define P_Img_RunStop_Ballon_2_3 11
//走る（風船１個）
#define P_Img_Run_Ballon_1_0     12
#define P_Img_Run_Ballon_1_1     13
#define P_Img_Run_Ballon_1_2     14
#define P_Img_RunStop_Ballon_1_3 15
//浮く（風船２個）
#define P_Img_Fly_Ballon_2_0 16
#define P_Img_Fly_Ballon_2_1 17
#define P_Img_Fly_Ballon_2_2 18
#define P_Img_Fly_Ballon_2_3 19
#define P_Img_Fly_Ballon_2_4 20
//死亡
#define P_Img_Dead_0 21
#define P_Img_Dead_1 22
#define P_Img_Dead_2 23
//浮く（風船１個）
#define P_Img_Fly_Ballon_1_0 24
#define P_Img_Fly_Ballon_1_1 25
#define P_Img_Fly_Ballon_1_2 26
#define P_Img_Fly_Ballon_1_3 27
#define P_Img_Fly_Ballon_1_4 28

//雷に当たる
#define P_Img_Thunder_0 29
//*******************************************//
// 画像サイズ（６４×６４）
#define P_Img_Size 64

//プレイヤーの状態
#define P_State_Wait    0 //待機状態
#define P_State_Run     1 //走る
#define P_State_Fly     2 //浮く
#define P_State_Dead    3 //落下
#define P_State_Thunder 4 //雷に当たる

#define Init_BallonNum 2//風船の初期数

#define P_Right  0 //右
#define P_Left   1 //左

#define ON_FlyBtn  true	//飛ぶボタンを押している
#define OFF_FlyBtn false//飛ぶボタンを押していない

#define Ground     true	//地面と接触している
#define Not_Ground false//地面と接触していない

#define Touch      true	//地面以外に触れている
#define Not_Touch  false//地面以外に触れてない

#define AbtnIntervalFream 8 //Aボタンのインターバルフレーム数

#define COR 0.8f			//反発係数(coefficient of repulsion)

#define Sea_Level 470		//海面の高さ

#define RespawnTime 30		//リスポーンまでの時間

#define Balloon_Crack    1	//風船が割られた
#define Balloon_NotCrack 0	//風船が割られてない

class Player
{
private:
	int FPSCnt;			//FPSカウント（６０FPS）
	int AbtnFPSCnt;		//Aボタン用のFPSカウント
	int WaitFPSCnt;		//ステックを倒していない時のFPSカウント
	int DeathCnt;		//死んだ後の点滅処理の間隔
	int RespawnCnt;     //リスポーンするまでの間隔

	int PlayerImg[33];	//プレイヤー画像
	int NowPlayerImg;	//現在のプレイヤー画像配列の要素

	float VectorX;		//ベクトルX
	float VectorY;		//ベクトルY
	int Angle;			//向いてる方向
	
	int PlayerState;	//プレイヤーの状態
	int BalloonNum;		//現在の風船の数

	int XStick;			//ステック上下
	int YStick;			//ステック左右

	int NowStage;		//現在のステージ

	bool FlyBtnFlg;		//(true;飛ぶボタンを押している false:飛ぶボタンを押していない)
	bool GroundFlg;		//(true:地面に接触している     false:地面に接触していない    )
	bool TouchFlg;		//(treu:地面以外に触れている   false:地面以外に触れていない　)
	bool Abtn;			//(treu:Aボタン押している      false:Aボタン押していない　   )
	bool Respawn;		//(treu:リスポーンした         false:リスポーンしてない　  　)
	bool Hide;			//(true:プレイヤーを表示しない false:プレイヤーを表示        )

	bool FishFlg;		//(true:魚に食べられた         false:魚に食べられていない    )*Fish.cppから値を取得している*

	int Anti_AbtnCnt = 0;	//Aボタンを押していない時をカウント

	int OldStage;
	int BalloonCrack;	//風船の数を割られた時の変数（0:割られてない　１：割られた）*Enemy.cppから値を取得する*（未完成）

	bool ReStartSoundFlg;

	int DeathVectorY;

	int ThunderHit;
	int MoveStopThunderCnt;
	int MoveDeathCnt;

public:
	static float PlayerX;	//プレイヤーX座標(画像の左上X座標)
	static float PlayerY;	//プレイヤーY座標(画像の左上Y座標)

	static bool Death;		//(true:死亡した               false:死亡していない          )

	static int Life;		//残機数

	static bool HitThunder;

	//コンストラクタ
	Player();
	//デストラクタ
	~Player() {};
	//描画以外の更新を実装する
	void Update(int Stage);
	//描画の更新を実装する
	void Draw() const;

	//移動処理（X方向）
	void UpdatePlayerX();
	//移動処理（Y方向）
	void UpdatePlayerY();

	//ステージとの当たり判定処理
	void UpdateStageCollision();

	//移動（地面）の画像処理
	void UpdatePlayerImgRun();

	//移動（空中）の画像処理
	void UpdatePlayerImgFly();

	//待機状態の画像処理
	void UpdatePlayerImgWait();

	//雷に当たるの画像処理
	void UpdatePlayerImgThunder();

	//死亡時の画像処理
	void UpdatePlayerImgDead();

	//初期位置へ戻す処理（無敵時間の処理もここでやる予定）
	void SetInitLocation();

	//プレイヤーの座標取得
	float GetPlayerX();
	float GetPlayerY();

	//風船がすべて割られる時
	void PlayerDeathMove();
	//雷に当たった時
	void PlayerThunderMove();

	void SeaInit();

	void EnemyCollison();
};