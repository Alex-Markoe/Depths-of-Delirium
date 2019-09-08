#pragma once
#include "Player.h"
#include "ObjectTree.h"
#include <iostream>
#include <fstream>

class LevelManager{
public:
	LevelManager();
	~LevelManager();
	void Update();
	void RenderAll();
	void ClearLevel();
	void Init();
	void SetViewport();

private:
	std::ofstream fileRead;
	Player* player;

	ObjectTree* platforms;
	ObjectTree* movingPlatforms;
	ObjectTree* swingingPlatforms;

	std::string roomName;
	bool transitioning;
	int levelWidth;
	int levelHeight;

	void PlatformCollision();
	void MovingPlatformUpdate();
	void SwingingPlatformUpdate();
};

