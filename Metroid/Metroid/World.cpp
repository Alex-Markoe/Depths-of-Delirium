#include "World.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextureDatabase.h"

//Constructor, initialize all important variables
World::World(SDL_Renderer* renderer) {
	gRenderer = renderer;

	//INITIALIZE TIMER VARIABLES
	tick_time = SDL_GetPerformanceCounter();
	last_tick_time = 0;
	deltaTime = 0;
	exit = false;

	//Load visuals
	TextureDatabase::instance().LoadAssets(gRenderer);
	//Set the world for the scene manager
	SceneManager::instance().SetWorld(this);
}
//Destructor
World::~World(){
	gRenderer = nullptr; //renderer is deleted in source
	active_scene = nullptr; //scenes are deleted in scene manager
}

//Call all update methods of any objects in the level
void World::Update(){
	//Update deltaTime
	last_tick_time = tick_time;
	tick_time = SDL_GetPerformanceCounter();
	deltaTime = (float)((tick_time - last_tick_time) * 1000 / (float)SDL_GetPerformanceFrequency());
	deltaTime *= 0.001f;
	
	//Update active scene
	active_scene->Update(deltaTime);
	//Check if game needs to be exited
	exit = SceneManager::instance().exit;
}

//Render all relevant objects
void World::Render(){
	active_scene->Render(gRenderer);
}