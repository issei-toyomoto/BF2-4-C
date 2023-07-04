#include "DxLib.h"
#include "AbstractScene.h"
#include "Player.h"
#include"bubble.h"
#include "Enemy.h"

class GameMain :public AbstractScene
{
private:
	Player player;
	bubble BUBBLE;
	Enemy enemy;
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

