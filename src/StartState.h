#pragma once
#include "header.h"
#include "GameState.h"

#include <cstdlib>

class MyEngine;

class StartState :
    public GameState
{
private:
    bool hasStoppedScrolling = false;
    bool hasFlashed = false;
    int flashTimer = 0;
    int flashStage = 0;

    SimpleImage kidImage;

public:
    StartState(MyEngine* pEngine, int maxX, int maxY) : GameState(pEngine, maxX, maxY) {
        kidImage = ImageManager::loadImage("resources/img/Origin/Kid/leftKid1Origin.png", true);
    }
    void virtSetupBackground() override;
    void virtUpdateBackground(int iCurrent) override;
    void virtDrawImage(SimpleImage image, int iX, int iY) override;
    void virtKeyDown(int iKeyCode) override;
    void virtMouseDown(int iButton, int iX, int iY) override;
};

