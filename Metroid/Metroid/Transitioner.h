#pragma once
#include "Tile.h"
#include <SDL.h>

class Transitioner
{
public:
	Transitioner();
	~Transitioner();
	SDL_Point Update();

	std::string roomName;
	Setting setting;
	int roomNumber;
};

