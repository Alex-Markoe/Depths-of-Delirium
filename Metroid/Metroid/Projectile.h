#pragma once
#include "GameObject.h"

enum PROJECTILE_TYPE {
	DAMAGE,
	PUSH,
	FIRE,
	ICE
};

class Projectile : public GameObject
{
public:
	Projectile(SDL_Rect initPosition, SDL_Rect initSource, SDL_Point hitboxOffset, 
				SDL_Point initForce, PROJECTILE_TYPE proj, bool player, float angle, int lifeTime);
	~Projectile();
	void Update() override;
	void Draw(SDL_Renderer* gRenderer) override;

	PROJECTILE_TYPE proj_Type;
	bool active;

private: 
	SDL_Point init_Force;
	Uint32 activeTimer;
	bool playerOwned;
	float initAngle;
};

