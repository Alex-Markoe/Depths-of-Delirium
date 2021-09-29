//GUARD
#ifndef __MAINSCENE_H_INCLUDED__
#define __MAINSCENE_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include <fstream>
#include "ObjectTree.h"
#include "Transitioner.h"
#include "PlayerOnObstacleHandler.h"
#include "Scene.h"

class MainScene : public Scene{
public:
	MainScene();
	~MainScene();
	void Update() override;
	void Render(SDL_Renderer* gRenderer) override;

private:
	//WORLD OBJECTS
	GameObject* player;
	GameObject* boss;
	GameObject* platforms;
	int total_tile_count;
	int active_tile_count;

	//IMPORTANT VARIABLES
	const int TILE_SIZE = 60;
	uint32_t LEVEL_WIDTH;
	uint32_t LEVEL_HEIGHT;

	ObjectTree* collision_space;
	Transitioner* transitioner;

	//COLLISION HANDLERS
	PlayerOnObstacleHandler* PoO_handler;

	void LoadLevel();
};

#endif //__MAINSCENE_H_INCLUDED__