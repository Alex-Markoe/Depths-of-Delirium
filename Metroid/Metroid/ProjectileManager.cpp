#include "ProjectileManager.h"



ProjectileManager::ProjectileManager(){
}


ProjectileManager::~ProjectileManager()
{
}

void ProjectileManager::Update() {
	for (unsigned i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Update();
	}
}

void ProjectileManager::Render(SDL_Renderer* gRenderer) {
	for (unsigned i = 0; i < projectiles.size(); i++) {
		projectiles[i]->Draw(gRenderer);
	}
}
