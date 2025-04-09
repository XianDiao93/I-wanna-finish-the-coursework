#pragma once
#include "header.h"
#include "MyEngine.h"

class MyEngine;

class GameState
{
protected:
	MyEngine* engine;
	int maxY, maxX;
public:
	GameState(MyEngine* pEngine, int maxX, int maxY) : engine(pEngine), maxX(maxX), maxY(maxY) {

	}
	virtual ~GameState() {}
	virtual void virtSetupBackground();
	virtual void virtUpdateBackground(int iCurrent);
};

