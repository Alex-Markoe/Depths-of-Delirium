#pragma once
#include "GameObject.h"

enum PROJECTILE_TYPE {
	Damage,
	Push,
	Fire,
	Ice
};

class Projectile : public GameObject
{
public:
	Projectile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY, SDL_Point initForce, PROJECTILE_TYPE proj);
	~Projectile();
	void Update();

	PROJECTILE_TYPE proj_Type;

private: 
	SDL_Point init_Force;
};

