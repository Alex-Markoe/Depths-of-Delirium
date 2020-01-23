#pragma once
#include "Tile.h"
#include <SDL.h>

class MovingTile : public Tile
{
public:
	MovingTile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY, TILE_TYPE type, TILE_ORIENTATION orientation, SETTING setting, SDL_Rect destination);
	~MovingTile();

	SDL_Rect initialPosition;
	SDL_Rect destinationPosition;
};

