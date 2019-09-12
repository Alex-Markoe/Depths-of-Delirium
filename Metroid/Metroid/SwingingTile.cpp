#include "SwingingTile.h"



SwingingTile::SwingingTile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY, TileType type, TileOrientation orientation, Setting setting, SDL_Rect initPos, SDL_Rect pivotPoint)
	: Tile(initPosition, initSource, hitboxOffsetX, hitboxOffsetY, type, orientation, setting){
	initialPosition = initPos;
	pivot = pivotPoint;

	destinationPosition = {pivot.x + (pivot.x - initialPosition.x), initialPosition.y};
}


SwingingTile::~SwingingTile()
{
}
