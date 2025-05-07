#pragma once
#include "DisplayableObject.h"
#include "SimpleImage.h"
#include "ImageManager.h"
#include "Utilities.h"

class Save :
    public DisplayableObject
{
protected:
    SimpleImage save;
    int activateTimer = 0;
    int type;
    Utilities::coordinate pos;
public:
    Save(BaseEngine* pEngine, int tp, Utilities::coordinate position) :DisplayableObject(pEngine)
    {
        if (tp == 0)
        {
            save = ImageManager::loadImage("resources/img/Save/redWuss.png");
        }
        else
        {
            save = ImageManager::loadImage("resources/img/Save/redSave.png");
        }
        pos = position;
        m_iCurrentScreenX = position.x * 32;
        m_iCurrentScreenY = position.y * 32;
        type = tp;
        m_iDrawHeight = 32;
        m_iDrawWidth = 32;
        m_iStartDrawPosX = 0;
        m_iStartDrawPosY = 0;
    }

    void virtDraw() override;
    void virtDoUpdate(int iCurrent) override;
    bool virtIsPositionWithinObject(int x, int y) override;
};

