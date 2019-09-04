#pragma once
#include "GameObject.h"
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
	Run,
	Duck,
};

class Player : public GameObject
{
public:
	Player(SDL_Rect initPosition, SDL_Rect initSource);
	~Player();
	void UpdateFrame();
	void Update();
	void UpdatePosition();
	void UpdateState(SDL_Event& e);

private:
	PSTATE playerState;
	PSTATE previousState;
};

