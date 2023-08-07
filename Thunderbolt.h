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

#define Thunder_Hide    0
#define Thunder_Display 1
#define Thuner_Touch    2

#define Cloud_Hide    0
#define Cloud_Display 1

class Thunder
{
private:
	int ThunderNum;//ステージの雷の数
	int CloudNum;//ステージの雲の数

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
		int StateFlg;//（０：表示されていない　１：表示されている　２：プレイヤーと接触した）
	};
	T thunder[2];
	
	//雷が出るときの雷
	struct OT{
		int Img[5];
		int Now_Img;
		int X;
		int Y;
		int OTAnimCnt;
		bool OTFlg;
	};
	OT OutThunder[2];

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
		int StateFlg;//(0:表示されていない 1:表示されている)
	};
	C Cloud[2];

	int Speed;// 雷の速度

	int NowStage;//現在のステージ

	bool TouchFlg;//雷と触れたことをプレイヤーに伝えるよう
		
public:
	//コンストラクタ
	Thunder ();

	//デストラクタ
	~Thunder() {};

	//描画以外の更新を実装する
	void Update(int i, int Stage);

	//描画に関することを実装する
	void Draw(int i) const;

	void DrawThunder() const;
	void DrawCloud() const;
	void DrawOutThunder() const;

	void StageCollision(int i);

	void ThunderAnim(int i);	//雷のアニメーション
	void CloudAnim(int i);		//雲のアニメーション
	void OutThunderAnim(int i);	//雷が出るときのアニメーション

	void InitCloud();//雲の初期化
	void CloudPosition();//ステージごとの雲の位置
};