#pragma once
#include <SDL.h>
#include "Tile.h"

class SwingingTile : public Tile
{
public:
	SwingingTile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY, TILE_TYPE type, TILE_ORIENTATION orientation, SETTING setting, SDL_Rect pivotPoint);
	~SwingingTile();

	SDL_Rect initialPosition;
	SDL_Rect pivot;
	float lengthSquared;
};

