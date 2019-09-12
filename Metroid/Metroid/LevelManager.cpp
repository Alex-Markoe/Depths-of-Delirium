#include "LevelManager.h"

LevelManager::LevelManager(){
	platforms = new ObjectTree(0, 0);
	movingPlatforms = new ObjectTree(0, 0);
	swingingPlatforms = new ObjectTree(0, 0);

	transitioning = false;
	roomName = "";
}


LevelManager::~LevelManager(){

}

//Call all update methods of any objects in the level
void LevelManager::Update(){
	//Update all the objects in the level
	player->Update();

	//Check collisions
	if (platforms->count != 0){
		platforms->CollisionDetector(*player);
	}
	if (movingPlatforms->count != 0){
		movingPlatforms->CollisionDetector(*player);
	}
	if (swingingPlatforms->count != 0){
		swingingPlatforms->CollisionDetector(*player);
	}

	//Change positions
	player->UpdatePosition();
}

//Call any update methods that require user input
void LevelManager::StateUpdate(SDL_Event e){
	player->UpdateState(e);
}

void LevelManager::RenderAll(SDL_Renderer* renderer){
	player->Draw(renderer);

	if (platforms->count != 0) {
		platforms->Render(renderer);
	}
	if (movingPlatforms->count != 0) {
		movingPlatforms->Render(renderer);
	}
	if (swingingPlatforms->count != 0) {
		swingingPlatforms->Render(renderer);
	}
}

void LevelManager::Init(){
	
}

void LevelManager::MovingPlatformUpdate(){

}

void LevelManager::SwingingPlatformUpdate(){

}

void LevelManager::SetViewport(){

}