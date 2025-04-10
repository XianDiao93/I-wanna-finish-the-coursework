#include "StartState.h"
#include "MyEngine.h"
#include <ctime>

void StartState::virtSetupBackground()
{
    engine->fillBackground(0x000000);

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int iY = 0; iY < maxY; iY++)
    {
        for (int iX = 0; iX < maxX; iX++)
        {
            int color = 0x000000;
            int randomNumber = std::rand() % 1000 + 1;

            if (randomNumber <= 10)
            {
                color = 0xffffff;
            }

            backgroundPixels[iY][iX] = color;
        }
    }

    for (int iY = 0; iY < maxY; iY++)
    {
        int red = 0;
        int green = 0;
        int blue = 255 - (255 * iY / maxY);
        int baseColor = (red << 16) | (green << 8) | blue;

        for (int iX = 0; iX < maxX; iX++)
        {
            int color = baseColor;
            int randomNumber = std::rand() % 1000 + 1;

            if (randomNumber <= (int)10*iY/maxY)
            {
                color = 0xffffff;
            }

            backgroundPixels[2*maxY-iY][iX] = color;
        }
    }


    for (int iY = 0; iY < maxY; iY++)
    {

        for (int iX = 0; iX < maxX; iX++)
        {
            engine->setBackgroundPixel(iX, iY, backgroundPixels[iY][iX]);
        }
    }

    //engine->fontManager.loadFonts();
    //Font* arial12 = engine->fontManager.getFont("Cornerstone Regular.ttf", 120);
    //Font* arial14 = engine->fontManager.getFont("Cornerstone Regular.ttf", 60);
    //engine->drawBackgroundString(80, 150, "I wanna", 0xffffff, arial12);
    //engine->drawBackgroundString(80, 260, "finish the coursework", 0xaaaaaa, arial14);
}

void StartState::virtUpdateBackground(int iCurrent)
{
    const int scrollSpeed = 10;
    int scrollOffset = iCurrent / scrollSpeed;

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
        else if (flashStage == 1 && flashTimer >= 10) {
            engine->getBackgroundSurface()->mySDLLockSurface();
            for (int iY = 0; iY < maxY; iY++) {
                for (int iX = 0; iX < maxX; iX++) {
                    engine->setBackgroundPixel(iX, iY, backgroundPixels[iY + maxY][iX]);
                }
            }
            engine->getBackgroundSurface()->mySDLUnlockSurface();
            virtDrawImage(kidImage, 750, 350);
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
        else if (flashStage == 3 && flashTimer >= 10) {
            engine->getBackgroundSurface()->mySDLLockSurface();
            for (int iY = 0; iY < maxY; iY++) {
                for (int iX = 0; iX < maxX; iX++) {
                    engine->setBackgroundPixel(iX, iY, backgroundPixels[iY + maxY][iX]);
                }
            }
            engine->fontManager.loadFonts();
            Font* CR12 = engine->fontManager.getFont("Cornerstone Regular.ttf", 120);
            Font* CR6 = engine->fontManager.getFont("Cornerstone Regular.ttf", 60);
            Font* CR3 = engine->fontManager.getFont("Cornerstone Regular.ttf", 30);
            engine->drawBackgroundString(80, 150, "I wanna", 0xffffff, CR12);
            engine->drawBackgroundString(80, 260, "finish the coursework", 0xaaaaaa, CR6);
            engine->drawBackgroundString(80, 560, "Press left shift to continue", 0xdddddd, CR3);
            engine->drawBackgroundString(80, 610, "Press esc to quit", 0xeeeeee, CR3);
            engine->getBackgroundSurface()->mySDLUnlockSurface();

            virtDrawImage(kidImage, 750, 350);
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
    switch (iKeyCode)
    {
    case '\033':
        exit(0);
    }
}
