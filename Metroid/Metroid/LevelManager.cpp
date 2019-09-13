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
		MovingPlatformUpdate();
		movingPlatforms->UpdatePosition();

		movingPlatforms->CollisionDetector(*player);
	}
	if (swingingPlatforms->count != 0) {
		SwingingPlatformUpdate();
		swingingPlatforms->UpdatePosition();

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
	std::vector<GameObject*> items = movingPlatforms->AllObjects();

	for (unsigned i = 0; i < items.size(); i++){
		MovingTile* tile = (MovingTile*)items[i];

		if (tile->position.x > tile->destinationPosition.x || tile->position.y > tile->destinationPosition.y
			|| tile->position.x < tile->initialPosition.x || tile->position.y < tile->initialPosition.y)
			tile->velocity = {tile->velocity.x * -1, tile->velocity.y * -1};
	}
}

void LevelManager::SwingingPlatformUpdate(){

}

void LevelManager::SetViewport(){

}