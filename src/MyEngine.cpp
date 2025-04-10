
#include "header.h"
#include "MyEngine.h"
#include "ImageManager.h"
#include "Scyxd6Object.h"
#include "AutomatedObject.h"
#include "UtilCollisionDetection.h"
#include "StartState.h"

void MyEngine::virtSetupBackgroundBuffer()
{
    currentState->virtSetupBackground();
}


void MyEngine::virtMouseDown(int iButton, int iX, int iY)
{
    //if (iButton == SDL_BUTTON_LEFT)
    //{
    //    stars++;
    //    lockBackgroundForDrawing();
    //    drawBackgroundRectangle(iX - 3, iY, iX + 3, iY, 0xffffff);
    //    drawBackgroundRectangle(iX, iY - 3, iX, iY + 3, 0xffffff);
    //    unlockBackgroundForDrawing();
    //    redrawDisplay(); // Force background to be redrawn to foreground
    //}
    //else if (iButton == SDL_BUTTON_RIGHT)
    //{
    //    stars++;
    //    lockBackgroundForDrawing();
    //    drawBackgroundOval(iX - 3, iY - 3, iX + 3, iY + 3, 0xffffff);
    //    unlockBackgroundForDrawing();
    //    redrawDisplay(); // Force background to be redrawn to foreground
    //}
}


/* Draw the string that moving objects should be drawn on top of */
void MyEngine::virtDrawStringsOnTop()
{
    // Build the string to print
    //char buf[128];
    //sprintf(buf, "%d stars in the sky", stars);
    //drawForegroundString(450, 150, buf, 0x00ffff, NULL);
}

void MyEngine::virtKeyDown(int iKeyCode)
{
    currentState->virtKeyDown(iKeyCode);
    //switch (iKeyCode)
    //{
    //case ' ':
    //    lockBackgroundForDrawing();
    //    virtSetupBackgroundBuffer();
    //    unlockBackgroundForDrawing();
    //    redrawDisplay();
    //    break;
    //}
}

int MyEngine::virtInitialiseObjects()
{
    //drawableObjectsChanged();
    //destroyOldObjects(true); 
    //createObjectArray(2);
    //storeObjectInArray(0, new Scyxd6Object(this));
    //storeObjectInArray(1, new AutomatedObject(this, 2));
    //setAllObjectsVisible(true);
    return 0;
}


void MyEngine::updateAllObjects(int iCurrentTime)
{
    BaseEngine::updateAllObjects(iCurrentTime);

    //DisplayableObject* obj1 = getDisplayableObject(0);  // Object in controll
    //DisplayableObject* obj2 = getDisplayableObject(1);  // Automated object

    //if (CollisionDetection::checkCircles(obj1->getXCentre(), obj1->getYCentre(), obj2->getXCentre(), obj2->getYCentre(), (obj1->getDrawHeight()+ obj2->getDrawHeight()) / 4))
    //{
    //    //obj2->setVisible(false);
    //    //obj2->redrawDisplay();
    //    obj2->setVelocity(0);
    //}
    //else
    //{
    //    //obj2->setVisible(true);
    //    //obj2->redrawDisplay();
    //    obj2->setVelocity(2);
    //}

    //if (tm.isValidTilePosition(obj1->getXCentre() - obj1->getDrawHeight()/4, obj1->getYCentre() - obj1->getDrawHeight() / 4))
    //{
    //    int mapX = tm.getMapXForScreenX(obj1->getXCentre() - obj1->getDrawHeight() / 4); // Which column?
    //    int mapY = tm.getMapYForScreenY(obj1->getYCentre() - obj1->getDrawHeight() / 4); // Which row?
    //    int value = tm.getMapValue(mapX, mapY); // Current value?
    //    tm.setAndRedrawMapValueAt(mapX, mapY, 0xffffff, this, getBackgroundSurface());
    //    redrawDisplay(); // Force background to be redrawn to foreground
    //}
}


int MyEngine::virtInitialise()
{
    currentState = new StartState(this, getWindowWidth(), getWindowHeight());
    BaseEngine::virtInitialise();
    return 0;
}

void MyEngine::virtMainLoopDoBeforeUpdate()
{
    if(currentState)
        currentState->virtUpdateBackground(getModifiedTime());
}

void MyEngine::changeState(int code)
{
    //switch (code)
    //{
    //case 1:
    //    currentState = new SaveState(this);
    //}
}
