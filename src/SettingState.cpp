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

	engine->drawBackgroundString(100, 100, "Click to Change Key Binding", 0xeeeeee, CR4);
	for (int i = 0; i < keyName.size(); i++)
	{
		engine->drawBackgroundString(100, 200 + i * 50, keyName[i].c_str(), 0xeeeeee, CR2);
	}

	for (int i = 0; i < keyString.size(); i++)
	{
		engine->drawBackgroundString(200, 200 + i * 50, keyString[i].c_str(), 0xeeeeee, CR2);
	}
	engine->drawBackgroundString(100, 700, "Click here to Apply", 0xeeeeee, CR4);
	
}

void SettingState::virtUpdateBackground(int iCurrent)
{

	if (flag)
	{
		// printf("this\n");
		engine->getBackgroundSurface()->mySDLLockSurface();
		engine->drawBackgroundString(100, 170, "Press a key to confirm or right click to cancel", 0xeeeeee, CR2);
		for (int iX = 200; iX < 350; iX++)
		{
			for (int iY = 200+pos*50; iY < 200+pos*50+25; iY++)
			{
				engine->setBackgroundPixel(iX, iY, backgroundPixels[maxY + iY][iX]);
			}
		}
		engine->getBackgroundSurface()->mySDLUnlockSurface();
	}

	engine->redrawDisplay();
	flag = false;

}

void SettingState::virtKeyDown(int iKeyCode)
{
	if (iKeyCode == keyInt[4] && flag2)
	{
		exit(0);
	}
	else if (iKeyCode == keyInt[7] && flag2)
	{
		engine->changeState(1);
	}
	else if (!flag2)
	{
		// TODO, check the validation of the keycode
		if (checkOccupation(iKeyCode))
		{
			GameState::keyInt[pos] = iKeyCode;
			if (SDL_GetKeyName(iKeyCode) == "RIGHT")
			{
				GameState::keyString[pos] = "->";
			}
			else if (SDL_GetKeyName(iKeyCode) == "LEFT")
			{
				GameState::keyString[pos] = "<-";
			}
			else
			{
				GameState::keyString[pos] = SDL_GetKeyName(iKeyCode);
			}
			flag2 = true;
			engine->getBackgroundSurface()->mySDLLockSurface();
			virtSetupBackground();
			engine->getBackgroundSurface()->mySDLUnlockSurface();
		}
		else
		{
			engine->getBackgroundSurface()->mySDLLockSurface();
			for (int iX = 100; iX < 700; iX++)
			{
				for (int iY = 170; iY < 200; iY++)
				{
					engine->setBackgroundPixel(iX, iY, backgroundPixels[maxY + iY][iX]);
				}
			}
			engine->drawBackgroundString(100, 170, "This key have been occupied", 0xeeeeee, CR2);
			engine->getBackgroundSurface()->mySDLUnlockSurface();
			engine->redrawDisplay();
		}
	}
}

void SettingState::virtMouseDown(int iButton, int iX, int iY)
{
	if (iButton == SDL_BUTTON_RIGHT)
	{
		flag2 = true;
		// printf("Hello\n");
		engine->getBackgroundSurface()->mySDLLockSurface();
		virtSetupBackground();
		engine->getBackgroundSurface()->mySDLUnlockSurface();
	}
	else if (iX > 100 && iY > 700 && iX < 600 && iY < 740 && flag2)
	{
		FileManager::writeStringsToFile(keyboardString, keyString);
		FileManager::writeIntsToFile(keyboardInt, keyInt);
		// printf("hello\n");
	}
	else if (iX > 200 && iX < 300 && flag2)
	{
		if (iY > 195 && iY < 225)
		{
			pos = 0;
			flag = true;
			flag2 = false;
			// printf("%d\n", pos);
		}
		else if (iY > 245 && iY < 275)
		{
			pos = 1;
			flag = true;
			flag2 = false;
		}
		else if (iY > 295 && iY < 325)
		{
			pos = 2;
			flag = true;
			flag2 = false;
		}
		else if (iY > 345 && iY < 375)
		{
			pos = 3;
			flag = true;
			flag2 = false;
		}
		else if (iY > 395 && iY < 425)
		{
			pos = 4;
			flag = true;
			flag2 = false;
		}
		else if (iY > 445 && iY < 475)
		{
			pos = 5;
			flag = true;
			flag2 = false;
		}
		else if (iY > 495 && iY < 525)
		{
			pos = 6;
			flag = true;
			flag2 = false;
		}
		else if (iY > 545 && iY < 575)
		{
			pos = 7;
			flag = true;
			flag2 = false;
		}
	}
}

bool SettingState::checkOccupation(int iKeyCode)
{
	for (int i = 0; i < keyInt.size(); i++)
	{
		if (iKeyCode == keyInt[i])
		{
			return false;
		}
	}
	return true;
}
