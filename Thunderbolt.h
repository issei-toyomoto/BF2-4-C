#pragma once
#include"bubble.h"
class Thunder
{
private:
	int gCloudImg = LoadGraph("images/Stage_Cloud01.png");
	int gThunderImg[2];

	int ThunderX = 100;
	int ThunderY = 100;// 雷の座標

	int Speed;// 雷の速度
	int ThunderFlg; // 雷の状態（0...移動中 1...物に接触 2...スタート状態）
	int WaitTime = 5;// 待ち時間
	int FPSCount;  // 点滅用
	int FlashFlg;  // 点滅用フラグ
	int Timer;
public:
	int ThunderMoveX, ThunderMoveY;
	float ThunderAngle = 0.575f;// 雷の角度
	void MoveThunderX();
	void MoveThunderY();

	//コンストラクタ
	Thunder ();

	//デストラクタ
	~Thunder() {};

	//描画以外の更新を実装する
	void Update();

	//描画に関することを実装する
	void Draw() const;

	
};