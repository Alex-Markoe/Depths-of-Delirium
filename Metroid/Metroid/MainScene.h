//GUARD
#ifndef __MAINSCENE_H_INCLUDED__
#define __MAINSCENE_H_INCLUDED__

//FORWARD DEPENDENCIES
class ObjectTree;
class PlayerCollisionHandler;

//INCLUDE DEPENDENCIES
#include "Scene.h"

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
	GameObject* particles_test;
	int total_tile_count;
	int active_tile_count;

	//IMPORTANT VARIABLES
	const int TILE_SIZE = 60;
	uint32_t LEVEL_WIDTH;
	uint32_t LEVEL_HEIGHT;

	ObjectTree* collision_space;
	const Uint8* key_state;

	//COLLISION HANDLERS
	PlayerCollisionHandler* player_collision_handler;
};

#endif //__MAINSCENE_H_INCLUDED__