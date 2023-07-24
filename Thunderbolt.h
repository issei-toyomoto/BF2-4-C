#pragma once

class Thunder
{
private:
	int gCloudImg = LoadGraph("images/Stage_Cloud01.png");
	int gThunderImg[2];

	int ThunderX=125, ThunderY=125;// 雷の座標

	int Speed;// 雷の速度
	int ThunderFlg; // 雷の状態（0...移動中 1...物に接触 2...スタート状態）
	int WaitTime=5;// 待ち時間
	
	
public:
	int ThunderMoveX, ThunderMoveY;
	float ThunderAngle = 0.575f;// 雷の角度
	void MoveThunder();

	//コンストラクタ
	Thunder ();

	//デストラクタ
	~Thunder() {};

	//描画以外の更新を実装する
	void Update();

	//描画に関することを実装する
	void Draw() const;

	void ChangeAngle();
};