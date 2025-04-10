#pragma once

#include "header.h"
#include "BaseEngine.h"
#include "ImageManager.h"
#include "Scyxd6TileManager.h"
#include "FontManager.h"
#include "GameState.h"

class GameState;

class MyEngine :
    public BaseEngine
{
public:
    FontManager fontManager;

protected:
    Scyxd6TileManager tm;

private:
    GameState* currentState;
    bool changingState = false;

public:
    void virtSetupBackgroundBuffer() override;
    void virtMouseDown(int iButton, int iX, int iY) override;
    void virtDrawStringsOnTop()override;
    void virtKeyDown(int iKeyCode) override;
    int virtInitialiseObjects() override;
    void updateAllObjects(int iCurrentTime) override;
    int virtInitialise() override;
    void virtMainLoopDoBeforeUpdate() override;
    void changeState(int code);
};

