#include "SaveState.h"

void SaveState::virtSetupBackground()
{
	engine->fillBackground(0xffffff);
}

void SaveState::virtUpdateBackground(int iCurrent)
{
	engine->getBackgroundSurface()->mySDLLockSurface();
	engine->fillBackground(0xffffff);
	engine->getBackgroundSurface()->mySDLUnlockSurface();
	engine->redrawDisplay();
}

void SaveState::virtDrawImage(SimpleImage image, int iX, int iY)
{
	return;
}

void SaveState::virtKeyDown(int iKeyCode)
{
	return;
}
