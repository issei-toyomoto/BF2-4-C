#pragma once

#define PlusPx 3			//px太くする（当たり判定）
#define COR 1
#define Sea_Level 470		//海面の高さ

class Thunder
{
private:
	int gThunderImg[3];
	int gCloudImg[3];
	int glightningImg[5];
	int ThunderX = 100;
	int ThunderY = 100;// 雷の座標
	int CloudX;
	int CloudY; // 雲の座標
	int lightningX;
	int lightningY;// 稲光の座標
	int VectorX;
	int VectorY;

	int Speed;// 雷の速度
	int ThunderAnimCnt; 
	int CloudAnimCount;
	int lightningAnimCount;
	int FlashFlg;

	int NowImg;
	int NowStage;
	int CNowImg; // 雲の現在の画像
	int LNowImg;
	int gWaitTime;
	int gWaitTime2;
		
public:
	//コンストラクタ
	Thunder ();

	//デストラクタ
	~Thunder() {};

	//描画以外の更新を実装する
	void Update(int Stage);

	//描画に関することを実装する
	void Draw() const;

	void MoveThunderX();
	void MoveThunderY();

	void StageCollision();

	void ThunderAnim();
	void CloudAnim();
	void LightningAnim();
};