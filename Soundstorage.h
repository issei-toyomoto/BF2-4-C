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

	// �C���X�g���N�^
	Soundstorage() {};
	// �f�X�g���N�^
	~Soundstorage() {};

	//�`��ȊO�̍X�V����������
	void Update();
	
};

