#include "ProjectileManager.h"

//Constructor
ProjectileManager::ProjectileManager(SDL_Renderer* renderer){
	gRenderer = renderer;
}

//Destructor, remove any remaining projectiles
ProjectileManager::~ProjectileManager(){
	for (unsigned i = 0; i < projectiles.size(); i++) {
		delete projectiles.front();
		projectiles.erase(projectiles.begin());
	}
}

//Update all projectiles contained in the manager
void ProjectileManager::Update() {
	for (unsigned i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Update();
	}
}

//Render all projectiles in the manager
void ProjectileManager::Render() {
	for (unsigned i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Draw(gRenderer);
	}
}

//Add a new projectile to the collection
void ProjectileManager::Add(SDL_Rect pos, SDL_Point force, PROJECTILE_TYPE type, bool playerOwned, float angle) {
	Projectile* projectile = new Projectile(pos, SDL_Rect{0,0,0,0}, 0, 0, force, type, playerOwned, angle);
	projectile->loadTexture("Assets/TileSpriteSheet.png", gRenderer);
	projectiles.push_back(projectile);
}

//Remove a projectile and all references to it
void ProjectileManager::Remove(Projectile* toRemove) {
	for (std::vector<Projectile*>::iterator i = projectiles.begin(); i != projectiles.end(); i++) {
		if (*i == toRemove) {
			delete *i;
			projectiles.erase(i);
			break;
		}
	}
}

