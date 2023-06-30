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
        int speedx;			//�ړ����x7
        int speedy;     
    };
    struct PLAYER gPlayer;

    int gPlayerImg = LoadGraph("image/ningen.png");
    int gStageImg1 = LoadGraph("image/StageScaffold1.png");
    int gStageImg2 = LoadGraph("image/StageScaffold2.png");
    int gSeaImg = LoadGraph("image/Sea.png");
public:
    virtual AbstractScene* Update() override;

    virtual void Draw() const  override;
};
class gStage2 : public AbstractScene
{
private:
    struct PLAYER
    {
        int flg;			//�g�p�t���O
        float x, y;			//���W
        float w, h;			//���E����
        double angle;		//�@�̂̌���
        int count;			//�^�C�~���O�p
        int speedx;			//�ړ����x
        int speedy;
    };
    struct PLAYER gPlayer;

    int gPlayerImg = LoadGraph("image/ningen.png");
    int gStageImg1 = LoadGraph("image/StageScaffold1.png");
    int gStageImg2 = LoadGraph("image/StageScaffold2.png");
    int gStageImg3 = LoadGraph("image/StageScaffold3.png");
    int gSeaImg = LoadGraph("image/Sea.png");
public:
    virtual AbstractScene* Update() override;

    virtual void Draw() const  override;
};
class gStage3 : public AbstractScene
{
private:
    struct PLAYER
    {
        int flg;			//�g�p�t���O
        float x, y;			//���W
        float w, h;			//���E����
        double angle;		//�@�̂̌���
        int count;			//�^�C�~���O�p
        int speedx;			//�ړ����x
        int speedy;
    };
    struct PLAYER gPlayer;

    int gPlayerImg = LoadGraph("image/ningen.png");
    int gStageImg1 = LoadGraph("image/StageScaffold1.png");
    int gStageImg2 = LoadGraph("image/StageScaffold2.png");
    int gStageImg4 = LoadGraph("image/StageScaffold4.png");
    int gSeaImg = LoadGraph("image/Sea.png");
public:
    virtual AbstractScene* Update() override;

    virtual void Draw() const  override;
};
class gStage4 : public AbstractScene
{
private:
    struct PLAYER
    {
        int flg;			//�g�p�t���O
        float x, y;			//���W
        float w, h;			//���E����
        double angle;		//�@�̂̌���
        int count;			//�^�C�~���O�p
        int speedx;			//�ړ����x
        int speedy;
    };
    struct PLAYER gPlayer;

    int gPlayerImg = LoadGraph("image/ningen.png");
    int gStageImg1 = LoadGraph("image/StageScaffold1.png");
    int gStageImg2 = LoadGraph("image/StageScaffold2.png");
    int gSeaImg = LoadGraph("image/Sea.png");
public:
    virtual AbstractScene* Update() override;

    virtual void Draw() const  override;
};
class gStage5 : public AbstractScene
{
private:
    struct PLAYER
    {
        int flg;			//�g�p�t���O
        float x, y;			//���W
        float w, h;			//���E����
        double angle;		//�@�̂̌���
        int count;			//�^�C�~���O�p
        int speedx;			//�ړ����x
        int speedy;
    };
    struct PLAYER gPlayer;

    int gPlayerImg = LoadGraph("image/ningen.png");
    int gStageImg1 = LoadGraph("image/StageScaffold1.png");
    int gStageImg2 = LoadGraph("image/StageScaffold2.png");
    int gSeaImg = LoadGraph("image/Sea.png");
public:
    virtual AbstractScene* Update() override;

    virtual void Draw() const  override;
};

