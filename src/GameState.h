#pragma once
#include "header.h"
#include "MyEngine.h"
#include "FileManager.h"

class MyEngine;

class GameState
{
protected:
	MyEngine* engine;
	int maxY, maxX;
	std::vector<std::vector<int>> backgroundPixels;
	std::string keyboardInt = "resources/keyboard/keyboardInt.dat";
	std::string keyboardString = "resources/keyboard/keyboardString.dat";
	std::vector<int> keyInt = { 1073741904, 1073741903, 1073742049, 122, 27, 114, 32, 8 }; // used for change input
	std::vector<std::string> keyString = {"right", "left", "left shift", "z", "esc", "r", "space", "backspace"};
	std::vector<std::string> keyName = {"right", "left", "jump", "shoot", "escape", "retry", "pause", "back"};

public:
	GameState(MyEngine* pEngine, int maxX, int maxY) : engine(pEngine), maxX(maxX), maxY(maxY) {
		if (!FileManager::checkOrCreateFile(keyboardInt))
		{
			FileManager::writeIntsToFile(keyboardInt, keyInt);
		}
		else
		{
			keyInt = FileManager::readIntsFromFile(keyboardInt);
		}
		if (!FileManager::checkOrCreateFile(keyboardString))
		{
			FileManager::writeStringsToFile(keyboardString, keyString);
		}
		else
		{
			keyString = FileManager::readStringsFromFile(keyboardString);
		}
		backgroundPixels.resize(2 * maxY + 10, std::vector<int>(maxX, 0));
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

				if (randomNumber <= (int)10 * iY / maxY)
				{
					color = 0xffffff;
				}

				backgroundPixels[2 * maxY - iY][iX] = color;
			}
		}
	}
	virtual ~GameState() {}
	virtual void virtSetupBackground();
	virtual void virtUpdateBackground(int iCurrent);
	virtual void virtDrawImage(SimpleImage image, int iX, int iY);
	virtual void virtKeyDown(int iKeyCode);
	virtual void virtMouseDown(int iButton, int iX, int iY);
};

