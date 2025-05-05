#include "GameState.h"

void GameState::virtSetupBackground()
{
	engine->fillBackground(0x000000);
}
void GameState::virtUpdateBackground(int iCurrent)
{
	return;
}
void GameState::virtDrawImage(SimpleImage image, int iX, int iY)
{
	return;
}

void GameState::virtKeyDown(int iKeyCode)
{
	if (iKeyCode == keyInt[4])
	{
		exit(0);
	}
	return;
}

void GameState::virtKeyUp(int iKeyCode)
{
}

void GameState::virtMouseDown(int iButton, int iX, int iY)
{
	return;
}

void GameState::virtUpdateObjects(int iCurrent)
{
	return;
}
