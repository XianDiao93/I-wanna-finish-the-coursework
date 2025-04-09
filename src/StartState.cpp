#include "StartState.h"
#include "MyEngine.h"
#include <ctime>

void StartState::virtSetupBackground()
{
    engine->fillBackground(0x000000);

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int iY = 0; iY < maxY; iY++) {
        for (int iX = 0; iX < maxX; iX++) {
            int color = 0x000000;
            int randomNumber = std::rand() % 1000 + 1;

            if (randomNumber <= 10) {
                color = 0xffffff;
            }

            backgroundPixels[iY][iX] = color;
        }
    }

    for (int iY = 0; iY < maxY; iY++) {
        int red = 0;
        int green = 0;
        int blue = 255 - (255 * iY / maxY);
        int baseColor = (red << 16) | (green << 8) | blue;

        for (int iX = 0; iX < maxX; iX++) {
            int color = baseColor;
            int randomNumber = std::rand() % 1000 + 1;

            if (randomNumber <= (int)10*iY/maxY) {
                color = 0xffffff;
            }

            backgroundPixels[2*maxY-iY][iX] = color;
        }
    }


    for (int iY = 0; iY < maxY; iY++) {

        for (int iX = 0; iX < maxX; iX++) {
            engine->setBackgroundPixel(iX, iY, backgroundPixels[iY][iX]);
        }
    }

    //for (int i = 0; i < 20; i++)
    //    for (int j = 0; j < 20; j++)
    //        tm.setMapValue(i, j, i+j);
    //tm.setTopLeftPositionOnScreen(300, 300);
    //tm.drawAllTiles(this, getBackgroundSurface());

    //SimpleImage image = ImageManager::loadImage("resources/Kid.png", true);
    //image.setTransparencyColour(0x000000);
    //image.renderImageWithMask(
    //    engine->getBackgroundSurface(),
    //    0, 0,
    //    750, 350,
    //    image.getWidth(), image.getHeight(),
    //    0x000000
    //);

    //engine->fontManager.loadFonts();
    //Font* arial12 = engine->fontManager.getFont("Cornerstone Regular.ttf", 120);
    //Font* arial14 = engine->fontManager.getFont("Cornerstone Regular.ttf", 60);
    //engine->drawBackgroundString(80, 150, "I wanna", 0xffffff, arial12);
    //engine->drawBackgroundString(80, 260, "finish the coursework", 0xaaaaaa, arial14);
}

void StartState::virtUpdateBackground(int iCurrent)
{
    // ToDo, update the background
    //if ((int)iCurrent / 100 < maxY) {
    //    for (int iY = 0; iY < maxY; iY++) {

    //        for (int iX = 0; iX < maxX; iX++) {
    //            engine->setBackgroundPixel(iX, iY, backgroundPixels[iY + (int)iCurrent / 100][iX]);
    //        }
    //    }
    //}

}