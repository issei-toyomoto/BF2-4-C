#pragma once
class Soundstorage
{
private:

public:
	int gStartSE;
	int gStageClearSE;
	int gSplashSE;
	int gRestartSE;
	int PlayerWalkSE;
	int PlayerJumpSE;
	int PerfectSE;
	int ParachuteSE;
	int GameOverSE;
	int FallingSE;
	int EnemyMoveSE;
	int EatableSE;
	int DefeatTheEnemySE;
	int CrackSE;
	int BubbleSE;
	int TripBGM;

	// インストラクタ
	Soundstorage() {};
	// デストラクタ
	~Soundstorage() {};

	//描画以外の更新を実装する
	void Update();
	
};

