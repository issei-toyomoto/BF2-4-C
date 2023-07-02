#pragma once
//**********画像変数の配列要素番号**********//
//待機状態（風船２個）
#define P_Img_Wait_Ballon_2_0 0
#define P_Img_Wait_Ballon_2_1 1
#define P_Img_Wait_Ballon_2_2 2
//待機状態（風船１個）
#define P_Img_Wait_Ballon_1_0 3
#define P_Img_Wait_Ballon_1_1 4
#define P_Img_Wait_Ballon_1_2 5
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
#define P_Img_FlyStop_Ballon_2_4 20
//浮く（風船１個）
#define P_Img_Fly_Ballon_1_0 24
#define P_Img_Fly_Ballon_1_1 25
#define P_Img_Fly_Ballon_1_2 26
#define P_Img_Fly_Ballon_1_3 27
#define P_Img_FlyStop_Ballon_1_4 28
//落下
#define P_Img_Drop_0 21
#define P_Img_Drop_1 22
#define P_Img_Drop_2 23
//雷に当たる
#define P_Img_Thunder_0 29
#define P_Img_Thunder_1 30
//*******************************************//
//プレイヤーの状態
#define P_State_Wait    0 //待機状態
#define P_State_Run     1 //走る
#define P_State_Fly     2 //浮く
#define P_State_Drop    3 //落下
#define P_State_Thunder 4 //雷に当たる

#define Init_BallonNum 2//風船の初期数

#define Right 0 //右
#define Left  1 //左

class Player
{
private:
	int FPSCnt;

	int PlayerImg[32];	//プレイヤー画像
	int NowPlayerImg;	//現在のプレイヤー画像配列の要素

	int PlayerX;		//プレイヤーX座標
	int PlayerY;		//プレイヤーY座標
	int VectorX;		//ベクトルX
	int VectorY;		//ベクトルY
	int Direction;		//向いてる方向
	
	int PlayerState;	//プレイヤーの状態
	int BalloonNum;		//現在の風船の数

	int XStick;//ステック上下
	int YStick;//ステック左右

public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player() {};
	//描画以外の更新を実装する
	void Update();
	//描画の更新を実装する
	void Draw() const;

	//移動（地面）の画像処理
	void UpdatePlayerImgRun();

	//移動（空中）の画像処理
	void UpdatePlayerImgFly();

	//待機状態の画像処理
	void UpdatePlayerImgWait();

	//雷に当たるの画像処理
	void UpdatePlayerImgThunder();
};