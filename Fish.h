#pragma once
#include"Player.h"
#include"Enemy.h"

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
	bool P_SpawnFlg;
	bool E_SpawnFlg;

	//画像用変数
	int FishImage[10];	
	bool TurnFlg;

	//魚のアニメーション用変数
	int f_Count;		//カウント	
	int FishAnim;		//フラグ

	//ターゲット用変数 0:無し　1:プレイヤー　２～４:敵（色別）
	int Target;			

	//プレイヤー座標
	Player p;			
	float P_X;			
	float P_Y;		

	//敵情報
	float E_X;
	float E_Y;
	int E_Color;
	bool E_Flg;
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
	void P_MoveFish();			//プレイヤーを襲う処理
	void E_MoveFish();			//敵を襲う処理
	void InitFish();			//初期化
	bool GetFishFlg();			//魚に食べられたとき用変数取得関数(プレイヤー)
	bool E_GetFishFlg();		//魚に食べられたとき用変数取得関数(敵)
};