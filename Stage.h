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
        float speed;			//移動速度
    };
    struct PLAYER gPlayer;

    int gPlayerImg = LoadGraph("image/ningen.png");
    int gStageImg1 = LoadGraph("image/seihoukei.png");
public:
    virtual AbstractScene* Update() override;

    virtual void Draw() const  override;
};

