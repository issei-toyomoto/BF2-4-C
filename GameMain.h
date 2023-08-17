#include "DxLib.h"
#include "AbstractScene.h"
#include "Player.h"
#include "bubble.h"
#include "Enemy.h"
#include "Thunderbolt.h"
#include "Fish.h"
#include "Stage.h"
#include "UI.h"
#include "InputKey.h"
#include "Soundstorage.h"
#include "Cloud.h"
#include "Thunder.h"

class GameMain : public AbstractScene
{
private:
	Player player;
	bubble BUBBLE;
	Enemy enemy;
	Thunderbolt thunderbolt;
	Fish fish;
	UI ui;
	gStage stage;
	InputKey inputkey;
	Soundstorage ss;
	Cloud cloud;
	Thunder thunder;

	int SeaImg;
	int gStageState;
	struct StageDate
	{
		int flg;
		int x, y;
	};
	int ClearFlg;
	int ClearWTime;

public:
	static int GameOverFlg;    // ゲームオーバーフラグ 0 :ゲームオーバーではない 1 : ゲームオーバー
	static int GameOverFont;   // ゲームオーバーのフォント文字
	static int PauseWTime;     // ポーズ状態に入った後からカウントする
	static int GameOverWTime;  // ゲームオーバー状態に入った後にカウントする
	static int PauseFlg;       // ポーズフラグ 0 : ポーズ状態ではない 1 : ポーズ状態
	static bool SoundFlg;      // サウンドフラグ 0 : スタートBGMのみが流れている 1 : 特定のBGMが流れてる
	//コンストラクタ
	GameMain() {
		//gGameImg[0] = LoadGraph("images/Stage_Footing01.png");      // ステージの足場1
		//gGameImg[1] = LoadGraph("images/Stage_Footing02.png");      // ステージの足場2
		//gGameImg[2] = LoadGraph("images/Stage_Footing03.png");      // ステージの足場3
		//gGameImg[3] = LoadGraph("images/Stage_Footing04.png");      // ステージの足場4
		//gGameImg[4] = LoadGraph("images/Stage_Footing05.png");      // ステージの足場5
		//gGameImg[5] = LoadGraph("images/Stage_Footing06.png");      // ステージの足場6
		//gGameImg[6] = LoadGraph("images/Stage_Footing07.png");      // ステージの足場7
		//gGameImg[7] = LoadGraph("images/Stage_Footing08.png");      // ステージの足場8
		//gGameImg[8] = LoadGraph("images/Stage_Land_Left01.png");    // ステージ左下の足場1
		//gGameImg[9] = LoadGraph("images/Stage_Land_Left02.png");    // ステージ左下の足場2
		//gGameImg[10] = LoadGraph("images/Stage_Land_Right01.png");   // ステージ右下の足場1
		//gGameImg[11] = LoadGraph("images/Stage_Land_Right02.png");   // ステージ右下の足場2
		SeaImg = LoadGraph("images/Stage_Sea01.png");          // 海の画像
		//gGameImg[13] = LoadGraph("images/ningen.png");               // プレイヤー画像
		gStageState = 1;
		GameOverFont = LoadGraph("images-20230711T024428Z-001/images/UI/UI_GameOver.png");
		PauseWTime = 0;
		GameOverWTime = 0;
		PauseFlg = 0;
		ClearFlg = 0;
		ClearWTime = 0;
	};

	//デストラクタ
	virtual ~GameMain() {};

	//描画以外の更新を実装する
	virtual AbstractScene* Update() override;

	//描画に関することを実装する
	virtual void Draw() const  override;

	static void GameOver();
	static void Pause();
};

