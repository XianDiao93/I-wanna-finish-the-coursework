#include "StartState.h"
#include "MyEngine.h"
#include <ctime>

void StartState::virtSetupBackground()
{
    engine->fillBackground(0x000000);

    for (int iY = 0; iY < maxY; iY++)
    {

        for (int iX = 0; iX < maxX; iX++)
        {
            engine->setBackgroundPixel(iX, iY, backgroundPixels[iY][iX]);
        }
    }
}

void StartState::virtUpdateBackground(int iCurrent)
{
    const int scrollSpeed = 10;
    int scrollOffset = iCurrent / scrollSpeed;
    engine->fontManager.loadFonts();

    if (!hasStoppedScrolling)
    {
        if (scrollOffset + maxY >= backgroundPixels.size())
        {
            hasStoppedScrolling = true;
            flashTimer = 0;
            return;
        }

        engine->getBackgroundSurface()->mySDLLockSurface();
        for (int iY = 0; iY < maxY; iY++)
        {
            for (int iX = 0; iX < maxX; iX++)
            {
                int sourceY = iY + scrollOffset;
                if (sourceY >= backgroundPixels.size())
                    continue;
                engine->setBackgroundPixel(iX, iY, backgroundPixels[sourceY][iX]);
            }
        }
        Font* msyh3 = engine->fontManager.getFont("Cornerstone Regular.ttf", 30);
        engine->drawBackgroundString(20, 20, "Click to skip animation", 0xffffff, msyh3);
        engine->getBackgroundSurface()->mySDLUnlockSurface();
        engine->redrawDisplay();

    }
    else if (!hasFlashed)
    {
        flashTimer++;

        if (flashStage == 0 && flashTimer >= 100) {
            engine->fillBackground(0xffffff);
            engine->redrawDisplay();
            flashStage = 1;
            flashTimer = 0;
        }
        else if (flashStage == 1 && flashTimer >= 5) {
            engine->getBackgroundSurface()->mySDLLockSurface();
            for (int iY = 0; iY < maxY; iY++) {
                for (int iX = 0; iX < maxX; iX++) {
                    engine->setBackgroundPixel(iX, iY, backgroundPixels[iY + maxY][iX]);
                }
            }
            engine->getBackgroundSurface()->mySDLUnlockSurface();
            virtDrawImage(kidImage, 850, 350);
            engine->redrawDisplay();

            flashStage = 2;
            flashTimer = 0;
        }
        else if (flashStage == 2 && flashTimer >= 100) {
            engine->fillBackground(0xffffff);
            engine->redrawDisplay();

            flashStage = 3;
            flashTimer = 0;
        }
        else if (flashStage == 3 && flashTimer >= 5) {
            engine->getBackgroundSurface()->mySDLLockSurface();
            for (int iY = 0; iY < maxY; iY++) {
                for (int iX = 0; iX < maxX; iX++) {
                    engine->setBackgroundPixel(iX, iY, backgroundPixels[iY + maxY][iX]);
                }
            }
            
            Font* CR12 = engine->fontManager.getFont("Cornerstone Regular.ttf", 120);
            Font* CR6 = engine->fontManager.getFont("Cornerstone Regular.ttf", 60);
            Font* CR3 = engine->fontManager.getFont("Cornerstone Regular.ttf", 30);
            engine->drawBackgroundString(80, 150, "I wanna", 0xffffff, CR12);
            engine->drawBackgroundString(80, 260, "finish the coursework", 0xaaaaaa, CR6);
            engine->drawBackgroundString(80, 560, "Press left shift to continue", 0xdddddd, CR3);
            engine->drawBackgroundString(80, 610, "Press esc to quit", 0xeeeeee, CR3);
            engine->getBackgroundSurface()->mySDLUnlockSurface();

            virtDrawImage(kidImage, 850, 350);
            engine->redrawDisplay();

            flashStage = 4;
            hasFlashed = true;
        }
    }
}

void StartState::virtDrawImage(SimpleImage image, int iX, int iY)
{
    image.setTransparencyColour(0x000000);
    engine->getBackgroundSurface()->mySDLLockSurface();
    image.renderImageWithMask(
        engine->getBackgroundSurface(),
        0, 0,
        iX, iY,
        image.getWidth(), image.getHeight(),
        0x000000
    );
    engine->getBackgroundSurface()->mySDLUnlockSurface();
}

void StartState::virtKeyDown(int iKeyCode)
{
    if (iKeyCode == keyInt[4])
    {
        exit(0);
    }
    else if (iKeyCode == keyInt[2])
    {
        engine->changeState(1);
    }
}

void StartState::virtMouseDown(int iButton, int iX, int iY)
{
    hasStoppedScrolling = true;
    flashStage = 3;
    flashTimer = 10;
}
