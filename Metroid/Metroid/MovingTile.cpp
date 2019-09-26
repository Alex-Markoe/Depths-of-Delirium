#include "MovingTile.h"



MovingTile::MovingTile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY, TileType type, TileOrientation orientation, Setting setting, SDL_Rect destination) 
	: Tile(initPosition, initSource, hitboxOffsetX, hitboxOffsetY, type, orientation, setting){
	destinationPosition = destination;
	initialPosition = initPosition;
}


MovingTile::~MovingTile()
{
}
