#pragma once
class Soundstorage
{
private:

public:
	static int gStartSE;
	static int gStageClearSE;
	static int gSplashSE;
	static int gRestartSE;
	static int PlayerWalkSE;
	static int PlayerJumpSE;
	static int PerfectSE;
	static int ParachuteSE; // �p���V���[�g
	static int GameOverSE;
	static int FallingSE;
	static int EnemyMoveSE;
	static int EatableSE;
	static int DefeatTheEnemySE; 
	static int CrackSE;
	static int BubbleSE;
	static int TripBGM;

	// �R���X�g���N�^
	Soundstorage();
	// �f�X�g���N�^
	~Soundstorage() {};

	//�`��ȊO�̍X�V����������
	void Update();
	
};

