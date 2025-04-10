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
protected:
    std::vector<std::vector<int>> backgroundPixels;
public:
    StartState(MyEngine* pEngine, int maxX, int maxY) : GameState(pEngine, maxX, maxY) {
        backgroundPixels.resize(2 * maxY + 10, std::vector<int>(maxX, 0));
        kidImage = ImageManager::loadImage("resources/img/Kid.png", true);
        kidImage.setTransparencyColour(0x000000);
    }
    void virtSetupBackground() override;
    void virtUpdateBackground(int iCurrent) override;
    void virtDrawImage(SimpleImage image, int iX, int iY) override;
    void virtKeyDown(int iKeyCode) override;
};

