#pragma once

#define PlusPx 3		//px��������i�����蔻��j
#define Sea_Level 470	//�C�ʂ̍���
#define Inversion 1     //�����p

#define Thunder_Hide    0
#define Thunder_Display 1
#define Thuner_Touch    2

#define Cloud_Hide    0
#define Cloud_Display 1

class Thunder
{
private:
	int ThunderNum;//�X�e�[�W�̗��̐�
	int CloudNum;//�X�e�[�W�̉_�̐�

	//��
	struct T {
		int Img[3];
		int T_NowImg;//���݂̗��̉摜
		int X;
		int Y;
		int VX;
		int VY;
		int AnimCnt;//�A�j���[�V�����̃t���[���J�E���g
		int WaitTime;//�A�j���[�V�����܂ł̃J�E���g
		int StateFlg;//�i�O�F�\������Ă��Ȃ��@�P�F�\������Ă���@�Q�F�v���C���[�ƐڐG�����j
	};
	T thunder[2];
	
	//�����o��Ƃ��̗�
	struct OT{
		int Img[5];
		int Now_Img;
		int X;
		int Y;
		int OTAnimCnt;
		bool OTFlg;
	};
	OT OutThunder[2];

	int NowStage;//���݂̃X�e�[�W
		
public:
	//�R���X�g���N�^
	Thunder ();

	//�f�X�g���N�^
	~Thunder() {};

	//�`��ȊO�̍X�V����������
	void Update(int Stage);

	//�`��Ɋւ��邱�Ƃ���������
	void Draw() const;

	void ThunderAnim(int i);	//���̃A�j���[�V����
	void OutThunderAnim(int i);	//�����o��Ƃ��̃A�j���[�V����
};