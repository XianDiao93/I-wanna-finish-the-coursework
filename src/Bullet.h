#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "SimpleImage.h"
#include "ImageManager.h"
#include "Utilities.h"
#include "MapTileManager.h"

class Bullet :
    public DisplayableObject
{
protected:
    SimpleImage bullet;
    int direction;
    Utilities::coordinate pos;
    MapTileManager* tm;

public:
    Bullet(BaseEngine* pEngine, int dir, Utilities::coordinate position, MapTileManager* tile) : DisplayableObject(pEngine)
    {
        direction = dir;
        bullet = ImageManager::loadImage("resources/img/Object/Bullet/white.png", true);
        pos = position;
        m_iCurrentScreenX = pos.x;
        m_iCurrentScreenY = pos.y;
        tm = tile;
        m_iDrawHeight = 4;
        m_iDrawWidth = 4;
        m_iStartDrawPosX = 0;
        m_iStartDrawPosY = 0;
    }
    void virtDoUpdate(int iCurrent) override;
    void virtDraw() override;
};

