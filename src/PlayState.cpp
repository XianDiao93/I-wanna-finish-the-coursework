#include "header.h"
#include "PlayState.h"
#include "Bullet.h"
#include "Save.h"
#include "UtilCollisionDetection.h"
#include "object.h"

void PlayState::virtSetupBackground()
{
	engine->fillBackground(0xffffff);
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 25; j++)
			tm.setMapValue(i, j, tileMap[j][i]);

	tm.setTopLeftPositionOnScreen(0, 0);
	tm.drawAllTiles(engine, engine->getBackgroundSurface());
	initObjects();
}

void PlayState::virtUpdateBackground(int iCurrent)
{

	if (player->isDead())
	{
		if (deathTimer >= 100)
		{
			engine->getBackgroundSurface()->mySDLLockSurface();

			engine->drawBackgroundString(200, 200, "GAME OVER", 0x000000, CR12);
			std::string msg = "Press " + keyString[5] + " to retry";
			engine->drawBackgroundString(300, 350, msg.c_str(), 0x000000, CR6);

			engine->getBackgroundSurface()->mySDLUnlockSurface();
		}
		else
		{
			deathTimer += 1;
		}
	}
	if (reDraw)
	{
		engine->getBackgroundSurface()->mySDLLockSurface();
		engine->fillBackground(0xffffff);
		tm.drawAllTiles(engine, engine->getBackgroundSurface());

		reDraw = false;
		engine->getBackgroundSurface()->mySDLUnlockSurface();
	}

	engine->redrawDisplay();
}

void PlayState::virtKeyDown(int iKeyCode)
{
	if (iKeyCode == keyInt[4])
	{
		std::vector<int> fin = { rePos.x, rePos.y, stage, mapIndex, difficulty };
		FileManager::writeIntsToFile(file, fin);
		exit(0);
	}
	else if (iKeyCode == keyInt[3] && !player->isDead())
	{
		if (numOfBullet() < 4)
		{
			int d = player->getState();
			switch (d)
			{
			case 0:
				d = 1;
				break;
			case 1:
				d = -1;
				break;
			}
			Utilities::coordinate pos = player->getPos();
			if (d == 1)
			{
				pos.x += 20;
			}
			pos.y += 10;

			int a = sparePosForBullet();
			if (a != 0)
			{
				Bullet* bullet = new Bullet(engine, d, pos, &tm);
				engine->storeObjectInArray(a, bullet);				
			}
		}
	}
	else if (iKeyCode == keyInt[5])
	{
		reInitMap();
		reDraw = true;
		deathTimer = 0;
		player->setPos(rePos);
		player->reTry();
	}
}

void PlayState::virtKeyUp(int iKeyCode)
{
	if (iKeyCode == keyInt[2])
	{
		player->canJump = true;
	}
}

void PlayState::initObjects()
{
	if (numObjects > 25)
	{
		exit(0);
	}
	Utilities::addAllimages();
	engine->drawableObjectsChanged();
	engine->destroyOldObjects(true);
	engine->createObjectArray(30);
	engine->storeObjectInArray(29, player);
	reInitObjects();
	engine->setAllObjectsVisible(true);
}

void PlayState::reInitObjects()
{
	for (int i = 0; i < 29; i++)
	{
		DisplayableObject* obj = engine->getDisplayableObject(i);
		delete obj;
		engine->storeObjectInArray(i, nullptr);
	}
	for (int i = 0; i < savesType.size(); i++)
	{
		Save *save = new Save(engine, savesType[i], savesPos[i]);
		engine->storeObjectInArray(i, save);
	}

	for (int i = 0; i < objectsType.size(); i++)
	{
		object* obj = new object(engine, objectsType[i], objectsPos[i]);
		engine->storeObjectInArray(i + savesType.size(), obj);
	}
}

void PlayState::virtUpdateObjects(int iCurrent)
{
	if (lockTimer < 20)
	{
		lockTimer++;
		return;
	}
	for (int i = numObjects; i < numObjects + 4; i++)
	{
		DisplayableObject* b = engine->getDisplayableObject(i);

		if (b != nullptr)
		{
			for (int j = 0; j < savesType.size(); j++)
			{
				DisplayableObject* s = engine->getDisplayableObject(j);
				
				if (s->virtIsPositionWithinObject(b->getXCentre(), b -> getYCentre()))
				{
					s->setVisible(true);
					savePlayer();
				}

			}
			if (!b->isVisible())
			{
				delete b;
				engine->storeObjectInArray(i, nullptr);
			}
		}
	}
	for (int i = savesType.size(); i < numObjects; i++)
	{

		DisplayableObject* o = engine->getDisplayableObject(i);
		if (i < savesType.size())
		{
			i = savesType.size();
			continue;
		}
		else if (i - savesType.size() > objectsType.size())
		{
			break;
		}

		if (o != nullptr)
		{
			//printf("%d\n", i);
			//printf("%d\n", savesType.size());
			//printf("%d\n", objectsType.size());
			//printf("%d\n", i - savesType.size());
			if (objectsType[i - savesType.size()] == 0)
			{
				if (o->virtIsPositionWithinObject(player->getPos().x + 1, player->getPos().y + 1) || o->virtIsPositionWithinObject(player->getPos().x + 23, player->getPos().y + 1) || o->virtIsPositionWithinObject(player->getPos().x + 1, player->getPos().y + 19) || o->virtIsPositionWithinObject(player->getPos().x + 23, player->getPos().y + 19))
				{
					mapIndex++;
					rePos.x = player->getPos().x;
					rePos.y = player->getPos().y;
					jumpMap();
				}
			}
			else if (objectsType[i - savesType.size()] == 1)
			{
				if (o->virtIsPositionWithinObject(player->getPos().x + 1, player->getPos().y + 1) || o->virtIsPositionWithinObject(player->getPos().x + 23, player->getPos().y + 1) || o->virtIsPositionWithinObject(player->getPos().x + 1, player->getPos().y + 19) || o->virtIsPositionWithinObject(player->getPos().x + 23, player->getPos().y + 19))
				{
					mapIndex = 0;
					if (stage >= maxStage)
					{
						stage = maxStage;
					}
					else
					{
						stage++;
					}
					rePos.x = 600;
					rePos.y = 748;
					jumpMap();
				}
			}
			else 
			{
				if (o->virtIsPositionWithinObject(player->getPos().x + 1, player->getPos().y + 1) || o->virtIsPositionWithinObject(player->getPos().x + 23, player->getPos().y + 1) || o->virtIsPositionWithinObject(player->getPos().x + 1, player->getPos().y + 19) || o->virtIsPositionWithinObject(player->getPos().x + 23, player->getPos().y + 19))
				{
					player->triggerDeath();
				}
			}
		}
	}
}

int PlayState::numOfBullet()
{
	int num = 0;
	DisplayableObject *A;
	for (int i = numObjects; i < numObjects +4; i++)
	{
		A = engine->getDisplayableObject(i);
		if (A == nullptr)
		{
			continue;
		}
		else if (dynamic_cast<Bullet*>(A))
		{
			num++;
		}
	}
	return num;
}

int PlayState::sparePosForBullet()
{
	DisplayableObject* A;
	for (int i = numObjects; i < numObjects + 4; i++)
	{
		A = engine->getDisplayableObject(i);
		if (A == nullptr)
		{
			return i;
		}
	}
	return 0;
}

void PlayState::savePlayer()
{
	rePos.x = player->getPos().x;
	rePos.y = player->getPos().y;
}

void PlayState::reInitMap()
{
	lockTimer = 0;
	mapS = "resources/map/Stage" + std::to_string(stage) + "/" + std::to_string(mapIndex) + ".map";
	datS = "resources/map/Stage" + std::to_string(stage) + "/" + std::to_string(mapIndex) + ".dat";

	tileMap = FileManager::readMapFromFile(mapS, 25, 40);
	savesPos = FileManager::readSavesFromFile(datS);
	savesType = FileManager::readSavesTypeFromFile(datS);
	objectsPos = FileManager::readObjectsFromFile(datS);
	objectsType = FileManager::readObjectsTypeFromFile(datS);

	std::vector<int> a;
	std::vector<Utilities::coordinate> b;
	for (int i = 0; i < savesType.size(); i++)
	{
		if (savesType[i] > difficulty - 1)
		{
			a.push_back(savesType[i]);
			b.push_back(savesPos[i]);
		}
	}
	savesType = a;
	savesPos = b;

	numObjects = objectsType.size() + savesType.size();

	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 25; j++)
			tm.setMapValue(i, j, tileMap[j][i]);
	reInitObjects();
}

void PlayState::jumpMap()
{
	lockTimer = 0;
	reInitMap();
	reDraw = true;
	player->setPos(rePos);
	player->reTry();
}
