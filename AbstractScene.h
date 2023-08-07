#pragma once

//デフォルトの抽象化シーンクラス
//ユーザーはこれを継承してシーンを実装すると楽
class AbstractScene
{
private:

public:
	//デストラクタ
	virtual~AbstractScene() {};

	//描画以外の更新を実装する
	virtual AbstractScene* Update() = 0;

	//描画に関することを実装する
	virtual void Draw()const = 0;
};
