#include "SaveState.h"

void SaveState::virtSetupBackground()
{
	engine->fillBackground(0xffffff);
}

void SaveState::virtUpdateBackground(int iCurrent)
{
	return;
}

void SaveState::virtDrawImage(SimpleImage image, int iX, int iY)
{
	return;
}

void SaveState::virtKeyDown(int iKeyCode)
{
	if (iKeyCode == esc)
	{
		exit(0);
	}
	return;
}
