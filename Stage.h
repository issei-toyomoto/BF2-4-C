#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
#include "InputKey.h"
class gStage1 : public AbstractScene
{
private:
    struct PLAYER
    {
        int flg;			//�g�p�t���O
        float x, y;			//���W
        float w, h;			//���E����
        double angle;		//�@�̂̌���
        int count;			//�^�C�~���O�p
        float speed;			//�ړ����x
    };
    struct PLAYER gPlayer;

    int gPlayerImg = LoadGraph("image/ningen.png");
    int gStageImg1 = LoadGraph("image/seihoukei.png");
public:
    virtual AbstractScene* Update() override;

    virtual void Draw() const  override;
};

