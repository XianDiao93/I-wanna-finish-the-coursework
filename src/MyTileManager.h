#pragma once
#include "header.h"
#include "TileManager.h"

class MyTileManager :
    public TileManager
{
private:
    std::vector<SimpleImage> m_vecTileImages;
    SimpleImage image;
public:
    MyTileManager()
        : TileManager(32, 32, 6, 10)
    {
        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Block/tubeHorizontal.png", true));
        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Block/tubeVerticle.png", true));
        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Block/tubeNode.png", true));
    }
    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const override;
};

