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
	void SetForce(SDL_Point force);

	PROJECTILE_TYPE proj_Type;
	bool active;
	bool playerOwned;

private: 
	SDL_Point init_Force;
	Uint32 activeTimer;
	float initAngle;
};