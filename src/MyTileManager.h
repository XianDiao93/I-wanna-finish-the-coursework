#pragma once
#include "header.h"
#include "TileManager.h"

class MyTileManager :
    public TileManager
{
public:
    MyTileManager()
        : TileManager(25, 25, 20, 20)
    {
    }
    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const override;
};

