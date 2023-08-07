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

	//出現判定　TRUE：出現　FALSE：未出現
	bool SpawnFlg;

	//画像用変数
	int FishImage[10];	
	bool TurnFlg;

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

	//魚に食べられたときプレイヤー用
	static bool P_FishFlg;

	//魚に食べられたとき敵用
	static bool E_FishFlg;

	Fish();						//コンストラクタ
	void Draw() const;			//魚生成
	void DrawRight() const;		//右向き描画
	void DrawLeft() const;		//左向き描画
	void Update();				//出現エリア判定
	void CheckPlayer();			//プレイヤー判定
	void CheckEnemy();			//エネミー判定
	void MoveFish();			//魚移動
	void TargetPlayer();		//プレイヤーを襲う処理
	void TargetEnemy();			//敵を襲う処理
	void InitFish();			//初期化
	bool GetFishFlg();			//魚に食べられたとき用変数取得関数(プレイヤー)
	bool E_GetFishFlg();		//魚に食べられたとき用変数取得関数(敵)
};