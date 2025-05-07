#include "header.h"
#include "Save.h"
#include "BaseEngine.h"

void Save::virtDraw()
{
    // Draw to foreground surface instead of background
    save.renderImageWithMask(
        getEngine()->getForegroundSurface(),
        0, 0,
        m_iCurrentScreenX, m_iCurrentScreenY,
        save.getWidth(), save.getHeight(),
        0x000000
    );
}

void Save::virtDoUpdate(int iCurrent)
{
    if (isVisible() && activateTimer < 150)
    {
        activateTimer++;
        if (type == 0)
        {
            save = ImageManager::loadImage("resources/img/Save/greenWuss.png");
        }
        else
        {
            save = ImageManager::loadImage("resources/img/Save/greenSave.png");
        }
    }
    else
    {
        setVisible(false);
        activateTimer = 0;
        if (type == 0)
        {
            save = ImageManager::loadImage("resources/img/Save/redWuss.png");
        }
        else
        {
            save = ImageManager::loadImage("resources/img/Save/redSave.png");
        }
    }
    getEngine()->redrawDisplay();

}

bool Save::virtIsPositionWithinObject(int x, int y)
{
    if (x > m_iCurrentScreenX && x < m_iCurrentScreenX + 32 && y > m_iCurrentScreenY && y < m_iCurrentScreenY + 32)
        return true;
    return false;
}

