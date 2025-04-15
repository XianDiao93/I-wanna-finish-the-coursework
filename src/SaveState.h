#pragma once
#include "header.h"
#include "GameState.h"

class SaveState :
    public GameState
{
private:
    SimpleImage rightKid;
    SimpleImage kidImage;
    int selected;
    int selectStage;
protected:
    MyTileManager tm;
public:
    SaveState(MyEngine* pEngine, int maxX, int maxY) : GameState(pEngine, maxX, maxY) {
        rightKid = ImageManager::loadImage("resources/img/Kid/rightKid1.png", true);
        kidImage = ImageManager::loadImage("resources/img/Origin/Kid/leftKid1Origin.png", true);
        selected = 1;
        selectStage = 1;
    }
    void virtSetupBackground() override;
    void virtUpdateBackground(int iCurrent) override;
    void virtDrawImage(SimpleImage image, int iX, int iY) override;
    void virtKeyDown(int iKeyCode) override;
    void virtMouseDown(int iButton, int iX, int iY);
};

