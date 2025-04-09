#pragma once

#include "header.h"
#include "DisplayableObject.h"

class AutomatedObject :
    public DisplayableObject
{
public:
    AutomatedObject(BaseEngine* pEngine, int velocity) : DisplayableObject(pEngine) {
        m_iCurrentScreenX = 200;
        m_iCurrentScreenY = 200;
        m_iDrawWidth = 100;
        m_iDrawHeight = 100;
        this->velocity = velocity;
    }
    AutomatedObject(BaseEngine* pEngine)
        : AutomatedObject(pEngine, 0) {
    }
    void virtDraw();
    void virtDoUpdate(int iCurrentTime);
protected:
    int hDirection = 1;
    int vDirection = 1;
};

