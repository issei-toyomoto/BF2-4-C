#pragma once
#include "AbstractScene.h"
#include "DxLib.h"
#include "Player.h"
class gStage
{
private:

    int gGameImg[14];
    int gSeaImg;
    int MousePointx;
    int MousePointy;
    int gGameState;
    int SeaPos;
    int SeaAnim[3];
    int SeaAnimCount;
    float px, py;
    int Seax, Seay;
    bool DeathFlg;
    
public:
    void Draw() const;

    void Update();

    void StageState();
    void SeaBottom();

    gStage();

    void DrawStage1() const;

    void DrawStage2() const;

    void DrawStage3() const;

    void DrawStage4() const;

    void DrawStage5() const;
};
//class gStage2 : public AbstractScene
//{
//private:
//
//
//    int gPlayerImg;
//    int gFootImg1;
//    int gFootImg2;
//    int gFootImg3;
//    int gFootImg4;
//    int gFootImg5;
//    int gFootImg6;
//    int gFootImg7;
//    int gFootImg8;
//    int gLlandImg1;
//    int gLlandImg2;
//    int gRlandImg1;
//    int gRlandImg2;
//    int gSeaImg;
//    int MousePointx;
//    int MousePointy;
//
//public:
//
//    gStage2();
//
//    virtual AbstractScene* Update() override;
//
//    virtual void Draw() const  override;
//};
//class gStage3 : public AbstractScene
//{
//private:
//
//    int gPlayerImg;
//    int gFootImg1;
//    int gFootImg2;
//    int gFootImg3;
//    int gFootImg4;
//    int gFootImg5;
//    int gFootImg6;
//    int gFootImg7;
//    int gFootImg8;
//    int gLlandImg1;
//    int gLlandImg2;
//    int gRlandImg1;
//    int gRlandImg2;
//    int gSeaImg;
//    int MousePointx;
//    int MousePointy;
//public:
//    gStage3();
//
//    virtual AbstractScene* Update() override;
//
//    virtual void Draw() const  override;
//};
//class gStage4 : public AbstractScene
//{
//private:
//
//    int gPlayerImg;
//    int gFootImg1;
//    int gFootImg2;
//    int gFootImg3;
//    int gFootImg4;
//    int gFootImg5;
//    int gFootImg6;
//    int gFootImg7;
//    int gFootImg8;
//    int gLlandImg1;
//    int gLlandImg2;
//    int gRlandImg1;
//    int gRlandImg2;
//    int gSeaImg;
//    int MousePointx;
//    int MousePointy;
//
//public:
//
//    gStage4();
//
//    virtual AbstractScene* Update() override;
//
//    virtual void Draw() const  override;
//};
//class gStage5 : public AbstractScene
//{
//private:
//
//    int gPlayerImg;
//    int gFootImg1;
//    int gFootImg2;
//    int gFootImg3;
//    int gFootImg4;
//    int gFootImg5;
//    int gFootImg6;
//    int gFootImg7;
//    int gFootImg8;
//    int gLlandImg1;
//    int gLlandImg2;
//    int gRlandImg1;
//    int gRlandImg2;
//    int gSeaImg;
//    int MousePointx;
//    int MousePointy;
//
//public:
//    gStage5();
//
//    virtual AbstractScene* Update() override;
//
//    virtual void Draw() const  override;
//};



