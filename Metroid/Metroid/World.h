//GUARD
#ifndef __WORLD_H_INCLUDED__
#define __WORLD_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "Scene.h";

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

private:
	SDL_Renderer* gRenderer;
	Scene* active_scene;

	//CLOCK VARIABLES
	float deltaTime;
	Uint64 tick_time;
	Uint64 last_tick_time;
};

#endif //__WORLD_H_INCLUDED__