#pragma once
#include "header.h"
#include "GameState.h"

#include <cstdlib>

class MyEngine;

class StartState :
    public GameState
{
protected:
    std::vector<std::vector<int>> backgroundPixels;
public:
    StartState(MyEngine* pEngine, int maxX, int maxY) : GameState(pEngine, maxX, maxY) {
        backgroundPixels.resize(2 * maxY + 10, std::vector<int>(maxX, 0));
    }
    void virtSetupBackground() override;
    void virtUpdateBackground(int iCurrent) override;
};

