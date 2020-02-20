#pragma once
#include "Player.h"
#include "ObjectTree.h"
#include "Transitioner.h"
#include "ProjectileManager.h"
#include "MovingTile.h"
#include "SwingingTile.h"
#include "ParticleSystem.h"
#include <iostream>
#include <fstream>
#include <map>

class LevelManager{
public:
	LevelManager(SDL_Renderer* renderer);
	~LevelManager();
	void Update();
	void RenderAll();
	void Init();
	void TransitionCollisions();

private:
	Player* player;
	ParticleSystem* particles;
	Transitioner* lvlTransition;
	ObjectTree* platforms;
	ProjectileManager* projectiles;
	SDL_Renderer* gRenderer;
	//std::vector<GameObject*> transitions;

	bool transitioning;
	float swingTimer;
	uint32_t levelWidth;
	uint32_t levelHeight;

	void AddTile(TILE_TYPE type, TILE_ORIENTATION orientation, SDL_Point pivotPos, int locX, int locY);
	void ReadLevelData(char * lvlData, std::string& tileData, int startIndex, int lvlWidth);
	void ProjectileCollision(Projectile* p, GameObject& character);

	const int TILE_SIZE = 60;
	const int TRANSITION_DEPTH = 25;
};

