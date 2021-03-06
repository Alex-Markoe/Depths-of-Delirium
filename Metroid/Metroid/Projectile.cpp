#include "Projectile.h"

Projectile::Projectile(SDL_Rect initPosition, SDL_Rect initSource, SDL_Point hitboxOffset,
	SDL_Point initForce, PROJECTILE_TYPE proj, bool player, float angle, int lifeTime):
	GameObject(initPosition, initSource, hitboxOffset)
{
	init_Force = initForce;
	proj_Type = proj;
	playerOwned = player;
	initAngle = angle;
	active = true;

	MAX_VELOCITY.x = 40;
	MAX_VELOCITY.y = 40;
	activeTimer = SDL_GetTicks() + lifeTime;
}

Projectile::~Projectile(){}

void Projectile::Update(){
	ApplyForce(init_Force);
	UpdateAnimation();
	UpdatePosition();

	if (activeTimer < SDL_GetTicks()) active = false;
}

void Projectile::Draw(SDL_Renderer* gRenderer){
	SDL_RenderCopyEx(gRenderer, texture, &sourceRect, &position, initAngle, NULL, flipType);
}

void Projectile::SetForce(SDL_Point force) {
	init_Force = force;
}