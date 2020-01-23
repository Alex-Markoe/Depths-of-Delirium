#include "MovingTile.h"

MovingTile::MovingTile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY, TILE_TYPE type, TILE_ORIENTATION orientation, SETTING setting, SDL_Rect destination) 
	: Tile(initPosition, initSource, hitboxOffsetX, hitboxOffsetY, type, orientation, setting){
	destinationPosition = destination;
	initialPosition = initPosition;
}


MovingTile::~MovingTile()
{
}
