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
	void TransitionCollisions();
	void SetViewport();

private:
	Player* player;
	Transitioner lvlTransition;

	ObjectTree* platforms;
	ObjectTree* movingPlatforms;
	ObjectTree* swingingPlatforms;
	std::vector<GameObject*> transitions;

	bool transitioning;
	float swingTimer;
	uint32_t levelWidth;
	uint32_t levelHeight;

	void MovingPlatformUpdate();
	void SwingingPlatformUpdate();

	const float GRAVITY = 9.81f;
	const int TILE_SIZE = 30;
	const int TRANSITION_DEPTH = 25;
};

