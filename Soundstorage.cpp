#include "Soundstorage.h"
#include"Dxlib.h"

int Soundstorage::gRestartSE;
int Soundstorage::gStartSE;
int Soundstorage::gStageClearSE;
int Soundstorage::gSplashSE;
int Soundstorage::PlayerWalkSE;
int Soundstorage::PlayerJumpSE;
int Soundstorage::PerfectSE;
int Soundstorage::ParachuteSE;
int Soundstorage::GameOverSE;
int Soundstorage::FallingSE;
int Soundstorage::EnemyMoveSE;
int Soundstorage::EatableSE;
int Soundstorage::DefeatTheEnemySE;
int Soundstorage::CrackSE;
int Soundstorage::BubbleSE;
int Soundstorage::TripBGM;
Soundstorage::Soundstorage() 
{
	 gStartSE=LoadSoundMem("sounds/SE_Start.wav");
	 gStageClearSE= LoadSoundMem("sounds/SE_StageClear.wav");
	 gSplashSE= LoadSoundMem("sounds/SE_Splash.wav");
	 gRestartSE= LoadSoundMem("sounds/SE_Restart.wav");
	 PlayerWalkSE= LoadSoundMem("sounds/SE_PlayerWalk.wav");
	 PlayerJumpSE= LoadSoundMem("sounds/SE_PlayerJump.wav");
	 PerfectSE= LoadSoundMem("sounds/SE_Perfect.wav");
	 ParachuteSE= LoadSoundMem("sounds/SE_parachute.wav");
	 GameOverSE= LoadSoundMem("sounds/SE_GameOver.wav");
	 FallingSE= LoadSoundMem("sounds/SE_Falling.wav");
	 EnemyMoveSE= LoadSoundMem("sounds/SE_EnemyMove.wav");
	 EatableSE= LoadSoundMem("sounds/SE_Eatable.wav");
	 DefeatTheEnemySE= LoadSoundMem("sounds/SE_DefeatTheEnemy.wav");
	 CrackSE= LoadSoundMem("sounds/SE_crack.wav");
	 BubbleSE= LoadSoundMem("sounds/SE_Bubble.wav");
	 TripBGM= LoadSoundMem("sounds/BGM_Trip.wav");
}

void Soundstorage::Update()
{

}
