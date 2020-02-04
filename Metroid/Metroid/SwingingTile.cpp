#include "SwingingTile.h"

SwingingTile::SwingingTile(SDL_Rect initPosition, SDL_Rect initSource, SDL_Point hitboxOffset, 
					TILE_TYPE type, TILE_ORIENTATION orientation, SETTING setting, SDL_Rect pivotPoint)
	: Tile(initPosition, initSource, hitboxOffset, type, orientation, setting){
	pivot = pivotPoint;
	initialPosition = initPosition;

	lengthSquared = pow(pivot.x - initPosition.x, 2) + pow(pivot.y - initPosition.y, 2);
}


SwingingTile::~SwingingTile()
{
}
