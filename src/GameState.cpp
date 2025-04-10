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
	switch (iKeyCode)
	{
	case '\033':
		exit(0);
	}
	return;
}
