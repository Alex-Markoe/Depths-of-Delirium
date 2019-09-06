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

void LevelManager::Update(){

}

void LevelManager::RenderAll(){

}

void LevelManager::Init(){

}

void LevelManager::PlatformCollision(){

}

void LevelManager::MovingPlatformUpdate(){

}

void LevelManager::SwingingPlatformUpdate(){

}

void LevelManager::ClearLevel(){

}