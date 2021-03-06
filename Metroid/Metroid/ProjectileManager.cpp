#include "ProjectileManager.h"

//Constructor
ProjectileManager::ProjectileManager(SDL_Renderer* renderer){
	gRenderer = renderer;
}

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
		projectiles[i]->Update();
		if (!projectiles[i]->active) Remove(projectiles[i]);
	}
}

//Render all projectiles in the manager
void ProjectileManager::Render() {
	for (unsigned i = 0; i < projectiles.size(); i++){
		projectiles[i]->Draw(gRenderer);
	}
}

//Add a new projectile to the collection
void ProjectileManager::Add(SDL_Rect pos, SDL_Point force, PROJECTILE_TYPE type, bool playerOwned, float angle){
	SDL_Rect source;
	int frames = 0, lifeTime = 500;
	std::string texturePath;
	SDL_Point hitboxOffset = { 0, 0 };
	switch (type) {
	case FIRE:
		source = SDL_Rect{ 0,0,48,21 };
		texturePath = "Assets/Fireball.png";
		break;
	case ICE:
		source = SDL_Rect{ 0,0,30,30 };
		break;
	case PUSH:
		source = SDL_Rect{ 0,21,39,39 };
		break;
	}
	Projectile* projectile = new Projectile(SDL_Rect{pos.x, pos.y, source.w, source.h}, source, 
											hitboxOffset, force, type, playerOwned, angle, lifeTime);
	projectile->loadTexture("Assets/Fireball.png", gRenderer);
	//projectile->SetAnim(0, 0, 2);
	projectiles.push_back(projectile);
}

//Remove a projectile and all references to it
void ProjectileManager::Remove(Projectile* toRemove) {
	for (std::vector<Projectile*>::iterator i = projectiles.begin(); i != projectiles.end(); i++){
		if (*i == toRemove) {
			delete *i;
			projectiles.erase(i);
			break;
		}
	}
}