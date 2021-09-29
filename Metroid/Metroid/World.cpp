#include "World.h"
//Constructor, initialize all important variables
World::World(SDL_Renderer* renderer) {
	gRenderer = renderer;

	//INITIALIZE TIMER VARIABLES
	tick_time = SDL_GetPerformanceCounter();
	last_tick_time = 0;
	deltaTime = 0;
}
//Destructor
World::~World(){
	gRenderer = nullptr;
}

//Call all update methods of any objects in the level
void World::Update(){
	//Update deltaTime
	last_tick_time = tick_time;
	tick_time = SDL_GetPerformanceCounter();
	deltaTime = (float)((tick_time - last_tick_time) * 1000 / (float)SDL_GetPerformanceCounter());
	deltaTime *= 0.001f;
}

//Render all relevant objects
void World::Render(){
	
}