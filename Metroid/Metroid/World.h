//GUARD
#ifndef __WORLD_H_INCLUDED__
#define __WORLD_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "SceneManager.h"

//WORLD CLASS
//UPDATES OBJECTS IN THE WORLD
//RENDERS THEM, HANDLES ROOM TRANSITIONING
//AND READING LEVEL DATA
class World{
public:
	World(SDL_Renderer* renderer);
	~World();
	void Update();
	void Render();

	Scene* active_scene;

private:
	SDL_Renderer* gRenderer;

	//CLOCK VARIABLES
	float deltaTime;
	Uint64 tick_time;
	Uint64 last_tick_time;
};

#endif //__WORLD_H_INCLUDED__