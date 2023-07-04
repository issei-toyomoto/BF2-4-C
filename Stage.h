#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
#include "InputKey.h"
class gStage1 : public AbstractScene
{
private:
    //struct PLAYER
    //{
    //    int flg;			//使用フラグ
    //    float x, y;			//座標
    //    float w, h;			//幅・高さ
    //    double angle;		//機体の向き
    //    int count;			//タイミング用
    //    int speedx;			//移動速度7
    //    int speedy;     
    //};
    /*struct PLAYER gPlayer;*/
    
    int gPlayerImg;
    int gFootImg1;
    int gFootImg2;
    int gFootImg3;
    int gFootImg4;
    int gFootImg5;
    int gFootImg6;
    int gFootImg7;
    int gFootImg8;
    int gLlandImg1;
    int gLlandImg2;
    int gRlandImg1;
    int gRlandImg2;
    int gSeaImg;
    int MousePointx;
    int MousePointy;
    
public:

    virtual AbstractScene* Update() override;

    gStage1();

    virtual void Draw() const  override;
};
class gStage2 : public AbstractScene
{
private:
    //struct PLAYER
    //{
    //    int flg;			//使用フラグ
    //    float x, y;			//座標
    //    float w, h;			//幅・高さ
    //    double angle;		//機体の向き
    //    int count;			//タイミング用
    //    int speedx;			//移動速度
    //    int speedy;
    //};
    //struct PLAYER gPlayer;


    int gPlayerImg;
    int gFootImg1;
    int gFootImg2;
    int gFootImg3;
    int gFootImg4;
    int gFootImg5;
    int gFootImg6;
    int gFootImg7;
    int gFootImg8;
    int gLlandImg1;
    int gLlandImg2;
    int gRlandImg1;
    int gRlandImg2;
    int gSeaImg;
    int MousePointx;
    int MousePointy;

public:

    gStage2();

    virtual AbstractScene* Update() override;

    virtual void Draw() const  override;
};
class gStage3 : public AbstractScene
{
private:
    //struct PLAYER
    //{
    //    int flg;			//使用フラグ
    //    float x, y;			//座標
    //    float w, h;			//幅・高さ
    //    double angle;		//機体の向き
    //    int count;			//タイミング用
    //    int speedx;			//移動速度
    //    int speedy;
    //};
    //struct PLAYER gPlayer;

    int gPlayerImg;
    int gFootImg1;
    int gFootImg2;
    int gFootImg3;
    int gFootImg4;
    int gFootImg5;
    int gFootImg6;
    int gFootImg7;
    int gFootImg8;
    int gLlandImg1;
    int gLlandImg2;
    int gRlandImg1;
    int gRlandImg2;
    int gSeaImg;
    int MousePointx;
    int MousePointy;
public:
    gStage3();

    virtual AbstractScene* Update() override;

    virtual void Draw() const  override;
};
class gStage4 : public AbstractScene
{
private:
    //struct PLAYER
    //{
    //    int flg;			//使用フラグ
    //    float x, y;			//座標
    //    float w, h;			//幅・高さ
    //    double angle;		//機体の向き
    //    int count;			//タイミング用
    //    int speedx;			//移動速度
    //    int speedy;
    //};
    //struct PLAYER gPlayer;

    int gPlayerImg;
    int gFootImg1;
    int gFootImg2;
    int gFootImg3;
    int gFootImg4;
    int gFootImg5;
    int gFootImg6;
    int gFootImg7;
    int gFootImg8;
    int gLlandImg1;
    int gLlandImg2;
    int gRlandImg1;
    int gRlandImg2;
    int gSeaImg;
    int MousePointx;
    int MousePointy;

public:

    gStage4();

    virtual AbstractScene* Update() override;

    virtual void Draw() const  override;
};
class gStage5 : public AbstractScene
{
private:
    //struct PLAYER
    //{
    //    int flg;			//使用フラグ
    //    float x, y;			//座標
    //    float w, h;			//幅・高さ
    //    double angle;		//機体の向き
    //    int count;			//タイミング用
    //    int speedx;			//移動速度
    //    int speedy;
    //};
    //struct PLAYER gPlayer;

    int gPlayerImg;
    int gFootImg1;
    int gFootImg2;
    int gFootImg3;
    int gFootImg4;
    int gFootImg5;
    int gFootImg6;
    int gFootImg7;
    int gFootImg8;
    int gLlandImg1;
    int gLlandImg2;
    int gRlandImg1;
    int gRlandImg2;
    int gSeaImg;
    int MousePointx;
    int MousePointy;

public:
    gStage5();

    virtual AbstractScene* Update() override;

    virtual void Draw() const  override;
};

