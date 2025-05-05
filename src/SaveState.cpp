#include "header.h"
#include "SaveState.h"

void SaveState::virtSetupBackground()
{
	for (int iY = 0; iY < maxY; iY++)
	{

		for (int iX = 0; iX < maxX; iX++)
		{
			engine->setBackgroundPixel(iX, iY, backgroundPixels[maxY + iY][iX]);
		}
	}

	virtDrawImage(kidImage, 850, 350);

	for(int i = 1; i < 5; i++)
		for(int j = 1; j < 9; j++)
			tm.setMapValue(i, j, 4);
	for (int i = 1; i < 9; i++)
	{
		tm.setMapValue(0, i, 1);
		tm.setMapValue(5, i, 1);
	}
	tm.setMapValue(0, 0, 2);
	tm.setMapValue(0, 9, 2);
	tm.setMapValue(5, 0, 2);
	tm.setMapValue(5, 9, 2);
	tm.setTopLeftPositionOnScreen(50, 300);
	tm.drawAllTiles(engine, engine ->getBackgroundSurface());
	tm.setTopLeftPositionOnScreen(300, 300);
	tm.drawAllTiles(engine, engine->getBackgroundSurface());
	tm.setTopLeftPositionOnScreen(550, 300);
	tm.drawAllTiles(engine, engine->getBackgroundSurface());

	engine->drawBackgroundString(100, 340, "Save1", 0xeeeeee, CR3);
	engine->drawBackgroundString(350, 340, "Save2", 0xeeeeee, CR3);
	engine->drawBackgroundString(600, 340, "Save3", 0xeeeeee, CR3);

	engine->drawBackgroundString(50, 200, "click here to change options", 0xeeeeee, CR3);

	std::string msg = "Use " + keyString[0] + " and " + keyString[1] + " to move, use "+ keyString[2] + " to select, use "+ keyString[3] + " to backspace";
	char* c_msg = new char[msg.length() + 1];
	strcpy(c_msg, msg.c_str());
	engine->drawBackgroundString(50, 240, c_msg, 0xeeeeee, CR2);
	delete[] c_msg;
}

void SaveState::virtUpdateBackground(int iCurrent)
{
	engine->getBackgroundSurface()->mySDLLockSurface();
	for (int iY = 640; iY < 640+21; iY++)
	{
		for (int iX = 130; iX < 130+25; iX++)
		{
			engine->setBackgroundPixel(iX, iY, backgroundPixels[maxY + iY][iX]);
			engine->setBackgroundPixel(iX + 250, iY, backgroundPixels[maxY + iY][iX]);
			engine->setBackgroundPixel(iX + 500, iY, backgroundPixels[maxY + iY][iX]);
		}
	}
	if ((iCurrent / 100) % 4 == 0)
	{
		rightKid = ImageManager::loadImage("resources/img/Kid/rightKid1.png", true);
		virtDrawImage(rightKid, 130 + 250 * (saves-1), 640);
	}	
	else if ((iCurrent / 100) % 4 == 1)
	{
		rightKid = ImageManager::loadImage("resources/img/Kid/rightKid2.png", true);
		virtDrawImage(rightKid, 130 + 250 * (saves-1), 640);
	}
	else if ((iCurrent / 100) % 4 == 2)
	{
		rightKid = ImageManager::loadImage("resources/img/Kid/rightKid3.png", true);
		virtDrawImage(rightKid, 130 + 250 * (saves-1), 640);
	}
	else if ((iCurrent / 100) % 4 == 3)
	{
		rightKid = ImageManager::loadImage("resources/img/Kid/rightKid4.png", true);
		virtDrawImage(rightKid, 130 + 250 * (saves-1), 640);
	}

	if (flag && selectStage == 1)
	{
		flag = false;
		for (int iY = 550; iY < 575; iY++)
		{
			for (int iX = 90; iX < 210; iX++)
			{
				engine->setBackgroundPixel(iX, iY, backgroundPixels[maxY + iY][iX]);
				engine->setBackgroundPixel(iX + 250, iY, backgroundPixels[maxY + iY][iX]);
				engine->setBackgroundPixel(iX + 500, iY, backgroundPixels[maxY + iY][iX]);
			}
		}
		
	}
	else if (flag && selectStage == 2)
	{
		flag = false;
		for (int iY = 550; iY < 575; iY++)
		{
			for (int iX = 90; iX < 210; iX++)
			{
				engine->setBackgroundPixel(iX, iY, backgroundPixels[maxY + iY][iX]);
				engine->setBackgroundPixel(iX + 250, iY, backgroundPixels[maxY + iY][iX]);
				engine->setBackgroundPixel(iX + 500, iY, backgroundPixels[maxY + iY][iX]);
			}
		}
		engine->drawBackgroundString(90 + 250 * (saves-1), 550, difficulties[difficulty].c_str(), 0xeeeeee, CR2);

	}
	engine->getBackgroundSurface()->mySDLUnlockSurface();
	engine->redrawDisplay();
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
	if (iKeyCode == keyInt[3] || iKeyCode == keyInt[7])
	{
		if (selectStage > 1)
		{
			selectStage--;
		}
		flag = true;
		difficulty = 0;
	}
	else if (iKeyCode == keyInt[2])
	{
		if (selectStage == 2)
		{
			engine->difficulty = difficulty;
			engine->saves = saves;
			engine->changeState(3);
			// printf("hello\n");
		}
		else if (selectStage < 2)
		{
			selectStage++;
			
		}
		flag = true;
	}
	else if (iKeyCode == keyInt[4])
	{
		exit(0);
	}
	else if (iKeyCode == keyInt[0])
	{
		if (selectStage == 1)
		{
			if (saves < 3)
			{
				saves++;
			}
			else if (saves == 3)
			{
				saves = 1;
			}
		}
		else if (selectStage == 2)
		{
			flag = true;
			if (difficulty < 4)
			{
				difficulty++;
			}
			else if (difficulty >= 4)
			{
				difficulty = 0;
			}
		}
	}
	else if (iKeyCode == keyInt[1])
	{
		if (selectStage == 1)
		{
			if (saves > 1)
			{
				saves--;
			}
			else if (saves == 1)
			{
				saves = 3;
			}

		}
		else if (selectStage == 2)
		{
			flag = true;

			if (difficulty > 0)
			{
				difficulty--;
			}
			else if (difficulty <= 0)
			{
				difficulty = 4;
			}
		}

	}
	return;
}

void SaveState::virtMouseDown(int iButton, int iX, int iY)
{
	if(iX > 50 && iX < 600 && iY > 195 && iY < 235)
		engine->changeState(2);
}
