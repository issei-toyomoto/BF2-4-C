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
		int X;
		int Y;
		int VX;
		int VY;
		int AnimCnt;
	};	
	T thunder[2];


	struct C {
		int Img[3];
		int X;
		int Y;
		int AnimCnt;
	};
	//雲
	
	C Cloud[2];

	int Speed;// 雷の速度
	
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
	void CloudAnim();
};