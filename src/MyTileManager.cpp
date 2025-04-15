#include "header.h"
#include "MyTileManager.h"

void MyTileManager::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iMapValue = getMapValue(iMapX, iMapY);


	if (iMapValue >= 0 && iMapValue < m_vecTileImages.size()) {
		m_vecTileImages[iMapValue].renderImage(pSurface,
			0,
			0,
			iStartPositionScreenX,
			iStartPositionScreenY,
			getTileWidth(), getTileHeight());
	}
}
