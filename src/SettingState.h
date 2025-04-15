#pragma once
#include "header.h"
#include "GameState.h"

class SettingState :
    public GameState
{
private:
    SimpleImage kidImage;
public:
    SettingState(MyEngine* pEngine, int maxX, int maxY) : GameState(pEngine, maxX, maxY)
    {
        kidImage = ImageManager::loadImage("resources/img/Origin/Kid/leftKid1Origin.png", true);
    }
    void virtSetupBackground() override;
    void virtUpdateBackground(int iCurrent) override;
};
