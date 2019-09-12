#include "MovingTile.h"



MovingTile::MovingTile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY, TileType type, TileOrientation orientation, Setting setting, SDL_Rect initPos, SDL_Rect destination) 
	: Tile(initPosition, initSource, hitboxOffsetX, hitboxOffsetY, type, orientation, setting){
	initialPosition = initPos;
	destinationPosition = destination;
}


MovingTile::~MovingTile()
{
}
