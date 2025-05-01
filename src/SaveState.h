#pragma once
#include "header.h"
#include "GameState.h"

class SaveState :
    public GameState
{
private:
    SimpleImage rightKid;
    SimpleImage kidImage;
    int selectStage;
    bool flag = false;
    std::string difficulties[5] = {"continue", "medium", "hard", "very hard", "impossible"};

    Font* CR2;
    Font* CR3;
    Font* CR6;
protected:
    MyTileManager tm;
public:
    SaveState(MyEngine* pEngine, int maxX, int maxY) : GameState(pEngine, maxX, maxY) {
        rightKid = ImageManager::loadImage("resources/img/Kid/rightKid1.png", true);
        kidImage = ImageManager::loadImage("resources/img/Origin/Kid/leftKid1Origin.png", true);
        selectStage = 1;

        CR2 = engine->fontManager.getFont("Cornerstone Regular.ttf", 20);
        CR3 = engine->fontManager.getFont("Cornerstone Regular.ttf", 30);
        CR6 = engine->fontManager.getFont("Cornerstone Regular.ttf", 60);
    }
    void virtSetupBackground() override;
    void virtUpdateBackground(int iCurrent) override;
    void virtDrawImage(SimpleImage image, int iX, int iY) override;
    void virtKeyDown(int iKeyCode) override;
    void virtMouseDown(int iButton, int iX, int iY);
};

