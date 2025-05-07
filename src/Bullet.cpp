#include "header.h"
#include "Bullet.h"
#include "BaseEngine.h"

void Bullet::virtDoUpdate(int iCurrent)
{
    m_iCurrentScreenX += 10 * direction;
    pos.x = m_iCurrentScreenX;
    if (pos.x > 1300 || pos.x < 0)
    {
        this->setVisible(false);
    }
    int mapX_L = tm->getMapXForScreenX(pos.x);
    int mapX_R = tm->getMapXForScreenX(pos.x + 4);
    int mapY_T = tm->getMapYForScreenY(pos.y);
    int mapY_B = tm->getMapYForScreenY(pos.y + 4);
    if(tm->getMapValue(mapX_L, mapY_T) < 9 || tm->getMapValue(mapX_R, mapY_T) < 9 || tm->getMapValue(mapX_L, mapY_B) < 9 || tm->getMapValue(mapX_R, mapY_B) < 9)
        this->setVisible(false);
}

void Bullet::virtDraw()
{
    if (isVisible())
    {
        // Draw to foreground surface instead of background
        bullet.renderImageWithMask(
            getEngine()->getForegroundSurface(),
            0, 0,
            m_iCurrentScreenX, m_iCurrentScreenY,
            bullet.getWidth(), bullet.getHeight(),
            0x000000
        );
    }
}
