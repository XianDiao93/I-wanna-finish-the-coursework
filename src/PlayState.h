#pragma once
#include "header.h"
#include "GameState.h"
#include "MapTileManager.h"
#include "Player.h"


class PlayState :
    public GameState
{
private:
	Utilities::coordinate rePos;
	bool reDraw = false;
	int deathTimer;
	std::vector<std::vector<int>> tileMap;

	std::vector<int> savesType;
	std::vector<int> objectsType;
	std::vector<Utilities::coordinate> savesPos;
	std::vector<Utilities::coordinate> objectsPos;
	// 0 and 1 is warp
	// 2-9 is delicious friut
	// 0 is wuss
	// 1 is hard
	// 2 is very hard
	// 3 is impossible
	
	Player *player;

	int mapIndex = 0;
	int stage = 0;

	int numObjects = 16;
	int maxStage = 0;

protected:
	int lockTimer = 0;
	MapTileManager tm;
	Font* CR6;
	Font* CR12;
	std::string mapS;
	std::string datS;

	std::string file = "resources/save/save" + std::to_string(engine->saves) + ".dat";

public:
	std::vector<DisplayableObject> objects;
public:
	PlayState(MyEngine* pEngine, int maxX, int maxY) : GameState(pEngine, maxX, maxY)
	{
		rePos.x = 600;
		rePos.y = 748;

		if (engine->difficulty == 0) {
			if (FileManager::checkOrCreateFile(file))
			{
				std::vector<int> fin = FileManager::readIntsFromFile(file);
				rePos.x = fin[0];
				rePos.y = fin[1];
				stage = fin[2];
				mapIndex = fin[3];
			}
			else
			{
				std::vector<int> fin = { rePos.x, rePos.y, stage, mapIndex, difficulty };
				FileManager::writeIntsToFile(file, fin);
			}
		}
		else
		{
			FileManager::checkOrCreateFile(file);
			std::vector<int> fin = { rePos.x, rePos.y, stage, mapIndex, difficulty };
			FileManager::writeIntsToFile(file, fin);
		}

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

		numObjects = objectsType.size()+savesType.size();

		player = new Player(pEngine, rePos.x, rePos.y, &tm, this);
		for (int i = 0; i < 4; i++)
		{
			player->keys[i] = keyInt[i];
		}

		CR6 = engine->fontManager.getFont("Cornerstone Regular.ttf", 60);
		CR12 = engine->fontManager.getFont("Cornerstone Regular.ttf", 120);
		deathTimer = 0;
	}
	void virtSetupBackground() override;
	void virtUpdateBackground(int iCurrent) override;
	//void virtDrawImage(SimpleImage image, int iX, int iY);
	void virtKeyDown(int iKeyCode) override;
	void virtKeyUp(int iKeyCode) override;
	/*void virtMouseDown(int iButton, int iX, int iY);*/
	void initObjects();
	void reInitObjects();
	void virtUpdateObjects(int iCurrent) override;
	int numOfBullet();
	int sparePosForBullet();
	void savePlayer();
	void reInitMap();
	void jumpMap();
};

