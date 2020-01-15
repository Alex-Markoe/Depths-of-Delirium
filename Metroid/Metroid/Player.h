#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

enum PSTATE {
	Jump,
	Fall,
	Idle,
	Attack,
	Force,
	RunLeft,
	RunRight,
	Duck,
};

class Player : public GameObject
{
public:
	Player(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY);
	~Player();
	void UpdateFrame();
	void Update();
	void UpdateState();

private:
	PSTATE playerState;
	PSTATE previousState;
	PROJECTILE_TYPE current_Proj;

	const Uint8 *state;
	int p_vel_Y;

	bool inAir;
	bool moving;
	float gravTimer;
	const int TERMINAL_VELOCITY = 1;
};

