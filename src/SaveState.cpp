#include "SaveState.h"

void SaveState::virtSetupBackground()
{
	engine->fillBackground(0xffffff);
	//virtDrawImage(saveImage, 750, 350);
	//virtDrawImage(rightKid, 650, 350);
}

void SaveState::virtUpdateBackground(int iCurrent)
{
	return;
	//if ((iCurrent / 400) % 4 == 0)
	//{
	//	engine->getBackgroundSurface()->mySDLLockSurface();
	//	engine->fillBackground(0xffffff);
	//	rightKid = ImageManager::loadImage("resources/img/Kid/rightKid1.png", true);
	//	virtDrawImage(rightKid, 650, 350);
	//	engine->getBackgroundSurface()->mySDLUnlockSurface();
	//}	
	//else if ((iCurrent / 400) % 4 == 1)
	//{
	//	engine->getBackgroundSurface()->mySDLLockSurface();
	//	engine->fillBackground(0xffffff);
	//	rightKid = ImageManager::loadImage("resources/img/Kid/rightKid2.png", true);
	//	xOffset = imgWidth - rightKid.getWidth();
	//	yOffset = imgHeight - rightKid.getHeight();
	//	virtDrawImage(rightKid, 650+xOffset, 350+yOffset);
	//	engine->getBackgroundSurface()->mySDLUnlockSurface();
	//}
	//else if ((iCurrent / 400) % 4 == 2)
	//{
	//	engine->getBackgroundSurface()->mySDLLockSurface();
	//	engine->fillBackground(0xffffff);
	//	rightKid = ImageManager::loadImage("resources/img/Kid/rightKid3.png", true);
	//	xOffset = imgWidth - rightKid.getWidth();
	//	yOffset = imgHeight - rightKid.getHeight();
	//	virtDrawImage(rightKid, 650 + xOffset, 350 + yOffset);
	//	engine->getBackgroundSurface()->mySDLUnlockSurface();
	//}
	//else if ((iCurrent / 400) % 4 == 3)
	//{
	//	engine->getBackgroundSurface()->mySDLLockSurface();
	//	engine->fillBackground(0xffffff);
	//	rightKid = ImageManager::loadImage("resources/img/Kid/rightKid4.png", true);
	//	xOffset = imgWidth - rightKid.getWidth();
	//	yOffset = imgHeight - rightKid.getHeight();
	//	virtDrawImage(rightKid, 650 + xOffset, 350 + yOffset);
	//	engine->getBackgroundSurface()->mySDLUnlockSurface();
	//}
	//engine->redrawDisplay();
}

void SaveState::virtDrawImage(SimpleImage image, int iX, int iY)
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

void SaveState::virtKeyDown(int iKeyCode)
{
	if (iKeyCode == esc)
	{
		exit(0);
	}
	return;
}
