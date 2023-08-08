#pragma once
class Cloud
{
private:
public:
	//コンストラクタ
	Cloud();
	//デストラクタ
	~Cloud() {};

	//描画以外の更新を実装する
	void Update();
	//描画の更新を実装する
	void Draw() const;
};

