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
	std::vector<GameObject*> plats = platforms->CollisionDetector(*player);
	std::vector<GameObject*> mPlats = movingPlatforms->CollisionDetector(*player);
	std::vector<GameObject*> sPlats = swingingPlatforms->CollisionDetector(*player);

	

	if (plats.size() != 0){
		

		for (unsigned i = 0; i < plats.size(); i++){
			

			
			}
		}
	}
}

void LevelManager::MovingPlatformUpdate(){

}

void LevelManager::SwingingPlatformUpdate(){

}

void LevelManager::ClearLevel(){

}

void LevelManager::SetViewport(){

}