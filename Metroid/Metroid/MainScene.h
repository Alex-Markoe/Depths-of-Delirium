//GUARD
#ifndef __MAINSCENE_H_INCLUDED__
#define __MAINSCENE_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include <fstream>
#include "ObjectTree.h"
#include "FileManager.h"
#include "PlayerOnObstacleHandler.h"
#include "SceneManager.h"
#include "PlayerComponent.h"

class MainScene : public Scene{
public:
	MainScene();
	~MainScene();
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* gRenderer) override;
	void LoadLevel();

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
	const Uint8* key_state;

	//COLLISION HANDLERS
	PlayerOnObstacleHandler* PoO_handler;
};

#endif //__MAINSCENE_H_INCLUDED__