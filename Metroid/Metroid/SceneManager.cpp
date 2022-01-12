#include "SceneManager.h"
#include "World.h"
#include "TitleScene.h";
#include "MainScene.h";
#include "PauseScene.h";

//Constructor
SceneManager::SceneManager() {
	//Initialize scenes
	scenes[0] = new TitleScene();
	scenes[1] = new MainScene();
	scenes[2] = new PauseScene();
	exit = false;
}
//Destructor
SceneManager::~SceneManager() {
	for (unsigned i = 0; i < TOTAL_SCENES; i++) {
		delete scenes[i];
	}
}

//Set the current world and initialize the active scene
void SceneManager::SetWorld(World* _world) { 
	world = _world; 
	world->active_scene = scenes[0];
}
//Change the current scene
void SceneManager::ChangeScene(int index) { 
	world->active_scene = scenes[index]; 
}
//Load in the level
void SceneManager::LoadGameData() {
	MainScene* m = static_cast<MainScene*>(scenes[GAME]);
	m->LoadLevel();
	m = nullptr;
}
//Exit the game
void SceneManager::Quit() {
	exit = true;
}