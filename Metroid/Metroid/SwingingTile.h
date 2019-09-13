#pragma once
#include <SDL.h>
#include "Tile.h"

class SwingingTile : public Tile
{
public:
	SwingingTile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY, TileType type, TileOrientation orientation, Setting setting, SDL_Rect initPos, SDL_Rect pivotPoint);
	~SwingingTile();

	SDL_Rect initialPosition;
	SDL_Rect destinationPosition;
	SDL_Rect pivot;
};

