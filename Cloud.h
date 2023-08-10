#pragma once
//**ステージごとの雲の位置**//
//ステージ１
#define Stage_1_X 300
#define Stage_1_Y 70
//ステージ２
#define Stage_2_X_0 50
#define Stage_2_Y_0 150 
#define Stage_2_X_1 450
#define Stage_2_Y_1 150
//ステージ３

//**************************//

#define No_Anim 0
#define Anim     1

class Cloud
{
private:
	int Num;			//配列番号用

	int Img[3];			//画像配列
	int NowImg[2];		//現在のステージ
	int AnimCnt[2];		//アニメーションのフレームカウント用
	int WaitTimeCnt[2]; //アニメーションまでのカウント
	int WaitTime[2];	//アニメーションまでの時間
	int WaitTimeFlg[2];	//アニメーションの時間を決める用
	int CloudState[2];  //雲の状態(0: 通常　1:アニメーション)

public:
	//コンストラクタ
	Cloud();
	//デストラクタ
	~Cloud() {};

	//描画以外の更新を実装する
	void Update();
	//描画の更新を実装する
	void Draw(int Stage) const;

	//ステージごとの雲の位置
	void StageDrawCloud(int Stage) const;

	//雲のアニメーション
	void AnimCloud(int i);
};

