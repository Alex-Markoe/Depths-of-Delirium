#pragma once
#include "Projectile.h"
#include "GameObject.h"
#include <vector>

class ProjectileManager
{
public:
	ProjectileManager(SDL_Renderer* renderer);
	~ProjectileManager();
	virtual void Update();
	void Remove(Projectile* toRemove);
	virtual void Add(SDL_Rect pos, SDL_Point force, PROJECTILE_TYPE type, bool playerOwned, float angle);
	void Render();
	std::vector<Projectile*> projectiles;

protected:
	SDL_Renderer* gRenderer;
};

