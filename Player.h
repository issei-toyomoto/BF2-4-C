#pragma once

class Player
{
private:
	int PlayerX;//プレイヤーX座標
	int PlayerY;//プレイヤーY座標
	int VectorX;//ベクトルX
	int VectorY;//ベクトルY
	
	int XStick;
	int YStick;

public:
	//コンストラクタ
	Player() {};
	//デストラクタ
	~Player() {};
	//描画以外の更新を実装する
	void Update();
	//描画の更新を実装する
	void Draw() const;
};