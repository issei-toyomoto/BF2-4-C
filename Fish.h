#pragma once
#include"Player.h"
class Fish
{
private:
	int WaitTime;		//待機時間用変数
	int Count;			//時間計測用変数
	int Second;			//秒数計測用変数
	int FishRand;		//魚の出現率

	//魚座標
	float f_PosX;		
	float f_PosY;		

	bool FishFlg;		//出現判定　TRUE：出現　FALSE：未出現
	int FishImage[10];	//画像用変数

	//魚のアニメーション用変数
	int f_Count;		//カウント	
	int FishAnim;		//フラグ

	//ターゲット用変数 0:無し　1:プレイヤー
	int Target;			

	//プレイヤー座標
	Player p;			
	float P_X;			
	float P_Y;		

public:
	Fish();					//コンストラクタ
	void Draw() const;		//魚生成
	void Update();			//出現エリア判定
	void MoveFish();		//魚移動
	void TargetPlayer();	//プレイヤーを襲う処理
	void InitFish();		//初期化
};