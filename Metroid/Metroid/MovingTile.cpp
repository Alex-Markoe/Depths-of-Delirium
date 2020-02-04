#include "MovingTile.h"

MovingTile::MovingTile(SDL_Rect initPosition, SDL_Rect initSource, SDL_Point hitboxOffset, 
					TILE_TYPE type, TILE_ORIENTATION orientation, SETTING setting, SDL_Rect destination) 
	: Tile(initPosition, initSource, hitboxOffset, type, orientation, setting){
	destinationPosition = destination;
	initialPosition = initPosition;
}


MovingTile::~MovingTile()
{
}
