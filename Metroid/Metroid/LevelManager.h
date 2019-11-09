#pragma once
#include "Player.h"
#include "ObjectTree.h"
#include "Transitioner.h"
#include "MovingTile.h"
#include "SwingingTile.h"
#include <iostream>
#include <fstream>
#include <map>

class LevelManager{
public:
	LevelManager(std::map<std::string, std::string> textures, SDL_Renderer* renderer);
	~LevelManager();
	void Update();
	void RenderAll(SDL_Renderer* renderer);
	void Init();
	void TransitionCollisions();
	void SetViewport();

private:
	Player* player;
	Transitioner* lvlTransition;

	ObjectTree* platforms;
	ObjectTree* movingPlatforms;
	ObjectTree* swingingPlatforms;
	std::vector<GameObject*> transitions;

	bool transitioning;
	float swingTimer;
	uint32_t levelWidth;
	uint32_t levelHeight;

	std::map<std::string, std::string> textureFiles;
	SDL_Renderer* gRenderer;

	void MovingPlatformUpdate();
	void SwingingPlatformUpdate();
	void AddTile(TileType type, TileOrientation orientation, SDL_Point pivotPos, int locX, int locY);

	const float GRAVITY = 9.81f;
	const int TILE_SIZE = 30;
	const int TRANSITION_DEPTH = 25;
};

