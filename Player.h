#pragma once

class Player
{
private:
	int PlayerX;//プレイヤー座標
	int PlayerY;//プレイヤー座標


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