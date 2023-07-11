#pragma once

class Thunder
{
private:
	int gCloudImg = LoadGraph("images/Stage_Cloud01.png");
	int gThunderImg= DrawBox(ThunderX, ThunderY, ThunderX +10, ThunderY + 10, GetColor(255, 0, 0), TRUE);
	int ThunderX=125, ThunderY=125;// 雷の座標
	int ThunderMoveX, ThunderMoveY;
	int Speed;// 雷の速度
	float ThunderAngle = 0.575f;// 雷の角度
	int ThunderFlg; // 雷の状態（0...移動中 1...物に接触 2...スタート状態）
	int WaitTime;// 待ち時間
	void ChangeAngle();
	
public:

	void MoveThunder();

	//コンストラクタ
	Thunder() {};

	//デストラクタ
	~Thunder() {};

	//描画以外の更新を実装する
	void Update();

	//描画に関することを実装する
	void Draw() const;
};