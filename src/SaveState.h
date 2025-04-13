#pragma once
#include "header.h"
#include "GameState.h"

class SaveState :
    public GameState
{
private:
    SimpleImage saveImage;
    SimpleImage rightKid;
    int imgWidth, imgHeight, xOffset, yOffset;
protected:
    std::vector<std::vector<int>> backgroundPixels;
public:
    SaveState(MyEngine* pEngine, int maxX, int maxY) : GameState(pEngine, maxX, maxY) {
        backgroundPixels.resize(maxY + 10, std::vector<int>(maxX, 0));
        saveImage = ImageManager::loadImage("resources/img/save.png", true);
        rightKid = ImageManager::loadImage("resources/img/Kid/rightKid1.png", true);
        imgWidth = rightKid.getWidth();
        imgHeight = rightKid.getHeight();
        xOffset = 0;
        yOffset = 0;
    }
    void virtSetupBackground() override;
    void virtUpdateBackground(int iCurrent) override;
    void virtDrawImage(SimpleImage image, int iX, int iY) override;
    void virtKeyDown(int iKeyCode) override;
};

