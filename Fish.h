#pragma once
#include"Player.h"
#include"Enemy.h"

class Fish
{
private:
	int WaitTime;		//�ҋ@���ԗp�ϐ�
	int Count;			//���Ԍv���p�ϐ�
	int Second;			//�b���v���p�ϐ�
	int FishRand;		//���̏o����

	//�����W
	float f_PosX;		
	float f_PosY;		

	//�o������@TRUE�F�o���@FALSE�F���o��
	bool P_SpawnFlg;
	bool E_SpawnFlg;

	//�摜�p�ϐ�
	int FishImage[10];	
	bool TurnFlg;

	//���̃A�j���[�V�����p�ϐ�
	int f_Count;		//�J�E���g	
	int FishAnim;		//�t���O

	//�^�[�Q�b�g�p�ϐ� 0:�����@1:�v���C���[�@�Q�`�S:�G�i�F�ʁj
	int Target;			

	//�v���C���[���W
	Player p;			
	float P_X;			
	float P_Y;		

	//�G���
	float E_X;
	float E_Y;
	int E_Color;
	bool E_Flg;
public:

	//���ɐH�ׂ�ꂽ�Ƃ��v���C���[�p
	static bool P_FishFlg;

	//���ɐH�ׂ�ꂽ�Ƃ��G�p
	static bool E_FishFlg;

	Fish();						//�R���X�g���N�^
	void Draw() const;			//������
	void DrawRight() const;		//�E�����`��
	void DrawLeft() const;		//�������`��
	void Update();				//�o���G���A����
	void CheckPlayer();			//�v���C���[����
	void CheckEnemy();			//�G�l�~�[����
	void P_MoveFish();			//�v���C���[���P������
	void E_MoveFish();			//�G���P������
	void InitFish();			//������
	bool GetFishFlg();			//���ɐH�ׂ�ꂽ�Ƃ��p�ϐ��擾�֐�(�v���C���[)
	bool E_GetFishFlg();		//���ɐH�ׂ�ꂽ�Ƃ��p�ϐ��擾�֐�(�G)
};