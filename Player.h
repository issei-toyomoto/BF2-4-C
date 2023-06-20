#pragma once

class Player
{
private:
	int MoveX;//地面での移動
	int MoveY;//地面での移動
	int BalloonNum;//風船の数
	int FloatingX;//空中での移動
	int FloatingY;//空中での移動
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