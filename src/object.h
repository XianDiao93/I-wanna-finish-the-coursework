#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "Utilities.h"
#include "SimpleImage.h"

class object :
    public DisplayableObject
{
private:
    Utilities::coordinate pos;
    SimpleImage image;
    int type;
public:
    object(BaseEngine* pEngine, int tp, Utilities::coordinate position) : DisplayableObject(pEngine)
    {
        pos.x = position.x;
        pos.y = position.y;
        type = tp;
        image = Utilities::objectImages[tp];
        if (type == 0 || type == 1)
        {
            m_iCurrentScreenX = pos.x;
            m_iCurrentScreenY = pos.y;
            m_iDrawHeight = 26;
            m_iDrawWidth = 26;
            m_iStartDrawPosX = 3;
            m_iStartDrawPosY = 3;
        }
        else
        {
            m_iCurrentScreenX = pos.x;
            m_iCurrentScreenY = pos.y;
            m_iDrawHeight = 22;
            m_iDrawWidth = 22;
            m_iStartDrawPosX = 0;
            m_iStartDrawPosY = 0;
        }
    }
    void virtDoUpdate(int iCurrent) override;
    void virtDraw() override;
};

