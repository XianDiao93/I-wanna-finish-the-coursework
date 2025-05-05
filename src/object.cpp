#include "header.h"
#include "object.h"
#include "BaseEngine.h"

void object::virtDoUpdate(int iCurrent)
{
    int currentFrame = (iCurrent / 250) % 2;
    if (currentFrame == 0)
    {
        image = Utilities::objectImages[type];
    }
    else
    {
        image = Utilities::objectImages2[type];
    }
    getEngine()->redrawDisplay();
}

void object::virtDraw()
{
    if (isVisible())
    {
        // Draw to foreground surface instead of background
        image.renderImageWithMask(
            getEngine()->getForegroundSurface(),
            0, 0,
            m_iCurrentScreenX, m_iCurrentScreenY,
            image.getWidth(), image.getHeight(),
            0x000000
        );
    }
}