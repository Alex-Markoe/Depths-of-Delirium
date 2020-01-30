#include "Projectile.h"

Projectile::Projectile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY, SDL_Point initForce, PROJECTILE_TYPE proj, bool player, float angle):
	GameObject(initPosition, initSource, hitboxOffsetX, hitboxOffsetY)
{
	init_Force = initForce;
	init_Position = SDL_Point{ initPosition.x, initPosition.y };
	proj_Type = proj;
	playerOwned = player;
	initAngle = angle;
	active = true;

	int timerModifier = 500;
	switch (proj) {
	case FIRE:
		sourceRect = SDL_Rect{ 0,0,30,30 };
		break;
	case ICE:
		sourceRect = SDL_Rect{ 0,0,30,30 };
		break;
	case PUSH:
		sourceRect = SDL_Rect{ 0,0,30,30 };
		break;
	}

	MAX_VELOCITY_X = 50;
	MAX_VELOCITY_Y = 50;
	activeTimer = SDL_GetTicks() + timerModifier;
}

Projectile::~Projectile()
{
}

void Projectile::Update() {
	ApplyForce(init_Force);
	UpdateAnimation();
	UpdatePosition();

	if (activeTimer < SDL_GetTicks()) active = false;
}

void Projectile::Draw(SDL_Renderer* gRenderer){
	SDL_RenderCopyEx(gRenderer, texture, &sourceRect, &position, initAngle, &init_Position, flipType);
}