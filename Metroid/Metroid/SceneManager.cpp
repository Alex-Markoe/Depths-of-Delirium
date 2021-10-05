#include "SceneManager.h"
#include "World.h"

//Constructor
SceneManager::SceneManager() {
	//Initialize scenes
	scenes[0] = new TitleScene();
	scenes[1] = new MainScene();
	scenes[2] = new PauseScene();
}
//Destructor
SceneManager::~SceneManager() {
	for (unsigned i = 0; i < TOTAL_SCENES; i++) {
		delete scenes[i];
	}
}

void SceneManager::SetWorld(World* _world) { 
	world = _world; 
	world->active_scene = scenes[0];
}
void SceneManager::ChangeScene(int index) { 
	world->active_scene = scenes[index]; 
}
void SceneManager::LoadGameData() {
	MainScene* m = static_cast<MainScene*>(scenes[GAME]);
	m->LoadLevel();
	m = nullptr;
}