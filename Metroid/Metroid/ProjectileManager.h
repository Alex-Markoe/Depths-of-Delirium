#pragma once
#include "Projectile.h"
#include "GameObject.h"
#include <vector>

class ProjectileManager
{
public:
	ProjectileManager(SDL_Renderer* renderer);
	~ProjectileManager();
	void Update();
	void Remove(Projectile* toRemove);
	void Add(SDL_Rect pos, SDL_Point force, PROJECTILE_TYPE type, bool playerOwned, float angle);
	void Render();

private:
	std::vector<Projectile*> projectiles;
	SDL_Renderer* gRenderer;
};

