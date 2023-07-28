#pragma once

#define PlusPx 3			//px太くする（当たり判定）
#define COR 1
#define Sea_Level 470		//海面の高さ

class Thunder
{
private:
	int gThunderImg[3];
	int gCloudImg[3];

	int ThunderX = 100;
	int ThunderY = 100;// 雷の座標
	int VectorX;
	int VectorY;

	int Speed;// 雷の速度
	int ThunderAnimCnt;  
	int FlashFlg;

	int NowImg;
	int NowStage;
		
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
};