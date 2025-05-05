#pragma once
#include "header.h"
#include "TileManager.h"


class MapTileManager :
    public TileManager
{
private:
    std::vector<SimpleImage> m_vecTileImages;
    SimpleImage image;
    // std::vector<std::vector<int>> iMapValue;
public:
    MapTileManager()
        : TileManager(32, 32, 40, 25)
    {
        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Block/tubeHorizontal.png", true));    // 0
        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Block/tubeVerticle.png", true));      // 1
        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Block/tubeNode.png", true));          // 2

        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Block/brick.png", true));             // 3
        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Block/brickTop.png", true));          // 4

        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Block/castleBrick.png", true));       // 5
        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Block/castleBrickTop.png", true));    // 6

        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Block/dirt.png", true));              // 7
        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Block/dirtTop.png", true));           // 8

        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Spike/down.png", true));              // 9
        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Spike/left.png", true));              // 10
        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Spike/right.png", true));             // 11
        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Spike/up.png", true));                // 12

        m_vecTileImages.push_back(ImageManager::loadImage("resources/img/Tile/Water/water.png", true));             // 13
    }
    void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const override;

};

