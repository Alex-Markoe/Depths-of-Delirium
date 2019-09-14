#pragma once
#include "Player.h"
#include "ObjectTree.h"
#include "Transitioner.h"
#include "MovingTile.h"
#include "SwingingTile.h"
#include <iostream>
#include <fstream>

class LevelManager{
public:
	LevelManager();
	~LevelManager();
	void StateUpdate(SDL_Event e);
	void Update();
	void RenderAll(SDL_Renderer* renderer);
	void Init();
	void SetViewport();

private:
	std::ofstream fileRead;
	Player* player;
	Transitioner lvlTransition;

	ObjectTree* platforms;
	ObjectTree* movingPlatforms;
	ObjectTree* swingingPlatforms;

	std::string roomName;
	bool transitioning;
	float swingTimer;
	int levelWidth;
	int levelHeight;

	void MovingPlatformUpdate();
	void SwingingPlatformUpdate();

	const float GRAVITY = 9.8f;
};

