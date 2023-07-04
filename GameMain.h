#include "DxLib.h"
#include "AbstractScene.h"
#include "Stage.h"

class GameMain :public AbstractScene
{
private:
	gStage1 gstage1;
	/*int gPlayerImg;*/
public:
	//コンストラクタ
	GameMain() {};

	//デストラクタ
	virtual ~GameMain() {};

	//描画以外の更新を実装する
	virtual AbstractScene* Update() override;

	//描画に関することを実装する
	virtual void Draw() const  override;
};

