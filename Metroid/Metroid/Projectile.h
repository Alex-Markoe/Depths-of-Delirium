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
	Projectile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY, SDL_Point initForce, PROJECTILE_TYPE proj, bool player, float angle);
	~Projectile();
	void Update() override;
	void Draw(SDL_Renderer* gRenderer) override;

	PROJECTILE_TYPE proj_Type;

private: 
	SDL_Point init_Force;
	SDL_Point init_Position;
	bool playerOwned;
	float initAngle;
};

