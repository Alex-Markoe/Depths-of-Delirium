#pragma once
#include "Tile.h"
#include <SDL.h>

class MovingTile : Tile
{
public:
	MovingTile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY, TileType type, TileOrientation orientation, Setting setting, SDL_Rect initPos, SDL_Rect destination);
	~MovingTile();

	SDL_Rect initialPosition;
	SDL_Rect destinationPosition;
};

