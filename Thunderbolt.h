#pragma once
class Thunder 
{
private:
	int ThunderX,ThunderY;// 雷の座標
	int ThunderMoveX, ThunderMoveY;
	int Speed;// 雷の速度
	float ThunderAngle=0.575f;// 雷の角度
	int ThunderFlg; // 雷の状態（0...移動中 1...物に接触 2...スタート状態）
	int WaitTime;// 待ち時間
	void ChangeAngle();
};