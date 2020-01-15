#include "Projectile.h"

Projectile::Projectile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY, SDL_Point initForce, PROJECTILE_TYPE proj) :
	GameObject(initPosition, initSource, hitboxOffsetX, hitboxOffsetY)
{
	init_Force = initForce;
	proj_Type = proj;
}

Projectile::~Projectile()
{
}

void Projectile::Update() {
	ApplyForce(init_Force);
	UpdateAnimation();
	UpdatePosition();
}