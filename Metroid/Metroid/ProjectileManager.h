#pragma once
#include "Projectile.h"
#include "GameObject.h"
#include <vector>

class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();
	void Update();
	void Render(SDL_Renderer* gRenderer);

	std::vector<Projectile*> projectiles;

private: 

};

