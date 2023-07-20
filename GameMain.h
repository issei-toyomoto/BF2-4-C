#include "DxLib.h"
#include "AbstractScene.h"
#include "Player.h"
#include "bubble.h"
#include "Enemy.h"
#include "Thunderbolt.h"
#include "Fish.h"
#include "Stage.h"
#include "UI.h"

class GameMain :public AbstractScene
{
private:
	Player player;
	bubble BUBBLE;
	Enemy enemy;
	Thunder thunder;
	Fish fish;
	UI ui;

	int gGameImg[14];
	int gStageState;
	struct StageDate
	{
		int flg;
		int x, y;
	};

public:
	//コンストラクタ
	GameMain() {
		gGameImg[0] = LoadGraph("images/Stage_Footing01.png");      // ステージの足場1
		gGameImg[1] = LoadGraph("images/Stage_Footing02.png");      // ステージの足場2
		gGameImg[2] = LoadGraph("images/Stage_Footing03.png");      // ステージの足場3
		gGameImg[3] = LoadGraph("images/Stage_Footing04.png");      // ステージの足場4
		gGameImg[4] = LoadGraph("images/Stage_Footing05.png");      // ステージの足場5
		gGameImg[5] = LoadGraph("images/Stage_Footing06.png");      // ステージの足場6
		gGameImg[6] = LoadGraph("images/Stage_Footing07.png");      // ステージの足場7
		gGameImg[7] = LoadGraph("images/Stage_Footing08.png");      // ステージの足場8
		gGameImg[8] = LoadGraph("images/Stage_Land_Left01.png");    // ステージ左下の足場1
		gGameImg[9] = LoadGraph("images/Stage_Land_Left02.png");    // ステージ左下の足場2
		gGameImg[10] = LoadGraph("images/Stage_Land_Right01.png");   // ステージ右下の足場1
		gGameImg[11] = LoadGraph("images/Stage_Land_Right02.png");   // ステージ右下の足場2
		gGameImg[12] = LoadGraph("images/Stage_Sea01.png");          // 海の画像
		gGameImg[13] = LoadGraph("images/ningen.png");               // プレイヤー画像
		gStageState = 1;
	};

	//デストラクタ
	virtual ~GameMain() {};

	//描画以外の更新を実装する
	virtual AbstractScene* Update() override;

	//描画に関することを実装する
	virtual void Draw() const  override;
};

