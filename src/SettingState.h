#pragma once
#include "header.h"
#include "GameState.h"

class SettingState :
    public GameState
{
private:
    SimpleImage kidImage;
    Font* CR2;
    Font* CR4;

    int pos = 0;
    bool flag = false;
    bool flag2 = true;

public:
    SettingState(MyEngine* pEngine, int maxX, int maxY) : GameState(pEngine, maxX, maxY)
    {
        kidImage = ImageManager::loadImage("resources/img/Origin/Kid/leftKid1Origin.png", true);
        CR2 = engine->fontManager.getFont("Cornerstone Regular.ttf", 20);
        CR4 = engine->fontManager.getFont("Cornerstone Regular.ttf", 40);
    }
    void virtSetupBackground() override;
    void virtUpdateBackground(int iCurrent) override;
    void virtKeyDown(int iKeyCode) override;
    void virtMouseDown(int iButton, int iX, int iY) override;
    bool checkOccupation(int iKeyCode);
};
