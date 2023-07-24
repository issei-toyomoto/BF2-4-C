#pragma once
#include"Player.h"
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
	bool SpawnFlg;

	//�摜�p�ϐ�
	int FishImage[10];	
	bool TurnFlg;

	//���̃A�j���[�V�����p�ϐ�
	int f_Count;		//�J�E���g	
	int FishAnim;		//�t���O

	//�^�[�Q�b�g�p�ϐ� 0:�����@1:�v���C���[
	int Target;			

	//�v���C���[���W
	Player p;			
	float P_X;			
	float P_Y;		

public:

	//���ɐH�ׂ�ꂽ�Ƃ��v���C���[�p
	bool P_FishFlg;

	//���ɐH�ׂ�ꂽ�Ƃ��G�p
	bool E_FishFlg;

	Fish();					//�R���X�g���N�^
	void Draw() const;		//������
	void DrawRight() const;		//�E�����`��
	void DrawLeft() const;		//�������`��
	void Update();			//�o���G���A����
	void MoveFish();		//���ړ�
	void TargetPlayer();	//�v���C���[���P������
	void TargetEnemy();		//�G���P������
	void InitFish();		//������
	bool GetFishFlg();		//���ɐH�ׂ�ꂽ�Ƃ��p�ϐ��擾�֐�
};