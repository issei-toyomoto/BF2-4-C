#pragma once
#include "AbstractScene.h"

//シーンマネージャー
//各シーンの切り替えを管理する
class SceneManager :public AbstractScene
{
private:
	AbstractScene* mScene;//現在のシーン

public:
	//コンストラクタ
	SceneManager(AbstractScene* scene) :mScene(scene) {};

	//デストラクタ
	~SceneManager() {
		delete mScene;
	}

	//描画以外の更新を実装する
	AbstractScene* Update() override;

	//描画に関することを実装する
	void Draw()const override;
};

