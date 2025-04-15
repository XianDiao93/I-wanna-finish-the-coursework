#include "SettingState.h"

void SettingState::virtSetupBackground()
{
	for (int iY = 0; iY < maxY; iY++)
	{

		for (int iX = 0; iX < maxX; iX++)
		{
			engine->setBackgroundPixel(iX, iY, backgroundPixels[maxY + iY][iX]);
		}
	}
}

void SettingState::virtUpdateBackground(int iCurrent)
{
	return;
}
