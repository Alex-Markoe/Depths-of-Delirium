#include "ProjectileManager.h"
//Destructor, remove any remaining projectiles
ProjectileManager::~ProjectileManager(){
	for (; projectiles.size() > 0;){
		delete projectiles.front();
		projectiles.erase(projectiles.begin());
	}
}

//Update all projectiles contained in the manager
void ProjectileManager::Update() {
	for (unsigned i = 0; i < projectiles.size(); i++){
		
	}
}

//Render all projectiles in the manager
void ProjectileManager::Render() {
	for (unsigned i = 0; i < projectiles.size(); i++){
		//projectiles[i]->renderer->Render(gRenderer);
	}
}

//Add a new projectile to the collection
void ProjectileManager::Add(SDL_Rect pos, SDL_Point force, bool playerOwned, float angle){
	
}

//Remove a projectile and all references to it
void ProjectileManager::Remove(GameObject* toRemove) {
	
}