#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
#include "InputKey.h"
class gStage1 : public AbstractScene
{
private:
    struct PLAYER
    {
        int flg;			//使用フラグ
        float x, y;			//座標
        float w, h;			//幅・高さ
        double angle;		//機体の向き
        int count;			//タイミング用
        int speedx;			//移動速度7
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
        int flg;			//使用フラグ
        float x, y;			//座標
        float w, h;			//幅・高さ
        double angle;		//機体の向き
        int count;			//タイミング用
        int speedx;			//移動速度
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
        int flg;			//使用フラグ
        float x, y;			//座標
        float w, h;			//幅・高さ
        double angle;		//機体の向き
        int count;			//タイミング用
        int speedx;			//移動速度
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
        int flg;			//使用フラグ
        float x, y;			//座標
        float w, h;			//幅・高さ
        double angle;		//機体の向き
        int count;			//タイミング用
        int speedx;			//移動速度
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
        int flg;			//使用フラグ
        float x, y;			//座標
        float w, h;			//幅・高さ
        double angle;		//機体の向き
        int count;			//タイミング用
        int speedx;			//移動速度
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

