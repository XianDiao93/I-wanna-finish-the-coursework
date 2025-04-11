#pragma once
#include "header.h"
#include "MyEngine.h"

class MyEngine;

class GameState
{
protected:
	MyEngine* engine;
	int maxY, maxX;
	int esc;
	int shoot;
	int jump;
	int left;
	int right;
public:
	GameState(MyEngine* pEngine, int maxX, int maxY) : engine(pEngine), maxX(maxX), maxY(maxY) {
		esc = 27; // esc
		shoot = 122; // z
		jump = 1073742049; // left shift
		left = 1073741904; // left arrow
		right = 1073741903; // right arrow
	}
	virtual ~GameState() {}
	virtual void virtSetupBackground();
	virtual void virtUpdateBackground(int iCurrent);
	virtual void virtDrawImage(SimpleImage image, int iX, int iY);
	virtual void virtKeyDown(int iKeyCode);
	virtual void virtMouseDown(int iButton, int iX, int iY);
};

