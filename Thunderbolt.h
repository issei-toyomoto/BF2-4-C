#pragma once
//**ステージごとの雲の位置**//
//ステージ１
#define Stage_1_X 
#define Stage_1_Y
//ステージ２


//**************************//
#define PlusPx 3		//px太くする（当たり判定）
#define Sea_Level 470	//海面の高さ
#define Inversion 1     //反発用

class Thunder
{
private:

	//雷
	struct T {
		int Img[3];
		int T_NowImg;//現在の雷の画像
		int X;
		int Y;
		int VX;
		int VY;
		int AnimCnt;//アニメーションのフレームカウント
		int WaitTime;//アニメーションまでのカウント
	};	
	T thunder[2];

	//雲
	struct C {
		int Img[3];
		int C_NowImg;//現在の雲の画像
		int X;
		int Y;
		int AnimCnt;
		int WaitTimeFlg;
		int WaitTime;
		int WaitTimeCnt;
		int StopAnimCnt;
	};
	C Cloud[2];

	int Speed;// 雷の速度
	
	int FlashFlg;

	
	

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

	void DrawThunder() const;
	void DrawCloud() const;

	void MoveThunderX();
	void MoveThunderY();

	void StageCollision();

	void ThunderAnim();
	void CloudAnim();

	void CloudPosition();
};