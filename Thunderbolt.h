#pragma once

class Thunderbolt
{
private:
	int Num;//画像配列用

	int Img[6];
	int NowImg[2];
	int X[2];
	int Y[2];
	int Position[2];//雷のポジション決め用の変数(雲から　0:左上　1:右上 2:左下 3:右下)
	int AnimCnt[2];
	bool FinCloudAnimFlg[2];
	
		
public:
	static bool FinAnimFlg[2];
	//コンストラクタ
	Thunderbolt();

	//デストラクタ
	~Thunderbolt() {};

	//描画以外の更新を実装する
	void Update(int Stage);

	//描画に関することを実装する
	void Draw(int Stage) const;

	
	void ThunderboltAnim(int i);	//雷が出るときのアニメーション
	void ThunderboltPosition(int i, int Stage);
};