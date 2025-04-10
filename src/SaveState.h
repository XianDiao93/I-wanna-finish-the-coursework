#pragma once
#include "header.h"
#include "GameState.h"

class SaveState :
    public GameState
{
private:

protected:
    std::vector<std::vector<int>> backgroundPixels;
public:
    SaveState(MyEngine* pEngine, int maxX, int maxY) : GameState(pEngine, maxX, maxY) {
        backgroundPixels.resize(maxY + 10, std::vector<int>(maxX, 0));
    }
    void virtSetupBackground() override;
    void virtUpdateBackground(int iCurrent) override;
    void virtDrawImage(SimpleImage image, int iX, int iY) override;
    void virtKeyDown(int iKeyCode) override;
};

