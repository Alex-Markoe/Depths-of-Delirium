#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cmath>

enum PLAYER_STATE {
	IDLE,
	JUMP,
	FALL,
	RUN,
	DUCK,
};

class Player : public GameObject
{
public:
	Player(SDL_Rect initPosition, SDL_Rect initSource, SDL_Point hitboxOffset, ProjectileManager* projManager);
	~Player();
	void UpdateFrame();
	void UpdateState();
	void Update() override;

private:
	void SpawnProjectile(PROJECTILE_TYPE type);

	PLAYER_STATE playerState;
	PLAYER_STATE previousState;
	PROJECTILE_TYPE current_Proj_Type;

	const Uint8 *state;
	ProjectileManager* projectiles;
	int p_vel_Y;

	bool inAir;
	bool inAction;
	bool attacking;
	Uint32 attackTimer;
	const int TERMINAL_VELOCITY = 1;
};

