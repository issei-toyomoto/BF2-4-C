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
	struct StageDate
	{
		int flg;
		int x, y;
	};
	int ClearFlg;
	int ClearWTime;
	int PhaseUI;
	int PhaseFlg;
	int FPSCount;
	int PhaseCount;
	int UINumber[10];

public:
	static int GameOverFlg;    // ゲームオーバーフラグ 0 :ゲームオーバーではない 1 : ゲームオーバー
	static int GameOverFont;   // ゲームオーバーのフォント文字
	static int PauseWTime;     // ポーズ状態に入った後からカウントする
	static int GameOverWTime;  // ゲームオーバー状態に入った後にカウントする
	static int PauseFlg;       // ポーズフラグ 0 : ポーズ状態ではない 1 : ポーズ状態
	static bool SoundFlg;      // サウンドフラグ 0 : スタートBGMのみが流れている 1 : 特定のBGMが流れてる
	static int gStageState;
	//コンストラクタ
	GameMain() {
		SeaImg = LoadGraph("images/Stage_Sea01.png");          // 海の画像
		GameOverFont = LoadGraph("images-20230711T024428Z-001/images/UI/UI_GameOver.png");
		LoadDivGraph("images-20230711T024428Z-001/images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, UINumber);
		PhaseUI = LoadGraph("images-20230711T024428Z-001/images/UI/UI_Phase.png");
		PauseWTime = 0;
		GameOverWTime = 0;
		PauseFlg = 0;
		ClearFlg = 0;
		ClearWTime = 0;
		PhaseFlg = 0;
		PhaseCount = 0;
		FPSCount = 0;
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

