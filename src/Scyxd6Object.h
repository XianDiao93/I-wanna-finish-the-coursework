#pragma once

#include "header.h"
#include "DisplayableObject.h"

class Scyxd6Object :
    public DisplayableObject
{
public:
    Scyxd6Object(BaseEngine* pEngine) : DisplayableObject(pEngine) {
        m_iCurrentScreenX = 200;
        m_iCurrentScreenY = 200;
        m_iDrawWidth = 100;
        m_iDrawHeight = 100;
    }
    void virtDraw();
    void virtDoUpdate(int iCurrentTime);
};


