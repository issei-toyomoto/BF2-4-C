#pragma once
#include"AbstractScene.h"
class Thunder
{
private:
	int gCloudImg = LoadGraph("Stage_Cloud01.png");
	int ThunderX, ThunderY;// 雷の座標
	int ThunderMoveX, ThunderMoveY;
	int Speed;// 雷の速度
	float ThunderAngle = 0.575f;// 雷の角度
	int ThunderFlg; // 雷の状態（0...移動中 1...物に接触 2...スタート状態）
	int WaitTime;// 待ち時間
	void ChangeAngle();
	void MoveThunder();

	//コンストラクタ
	Thunder() {};

	//デストラクタ
	virtual ~Thunder() {};

	//描画以外の更新を実装する
	virtual AbstractScene* Update() override;

	//描画に関することを実装する
	virtual void Draw() const  override;
};