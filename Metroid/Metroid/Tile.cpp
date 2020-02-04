#include "Tile.h"

Tile::Tile(SDL_Rect initPosition, SDL_Rect initSource, SDL_Point hitboxOffset, 
			TILE_TYPE Type, TILE_ORIENTATION Orientation, SETTING Setting) :
	GameObject(initPosition, initSource, hitboxOffset){
	type = Type;
	orientation = Orientation;
	setting = Setting;

	switch (setting){
	case CAVERNS: //Cavern initalization
		switch(type){
		case PLATFORM:
			switch (orientation){
			case TOP_LEFT:
				SetSourceLoc(TILE_SPRITE_SIZE, 0);
				break;
			case TOP_RIGHT:
				SetSourceLoc(TILE_SPRITE_SIZE * 2, 0);
				break;
			case TOP_MIDDLE:
				SetSourceLoc(0, 0);
				break;
			case LEFT:
				SetSourceLoc(TILE_SPRITE_SIZE, TILE_SPRITE_SIZE);
				break;
			case RIGHT:
				SetSourceLoc(TILE_SPRITE_SIZE * 2, TILE_SPRITE_SIZE);
				break;
			case HORIZONTAL_MIDDLE:
				SetSourceLoc(0, TILE_SPRITE_SIZE * 3);
				break;
			case HORIZONTAL_LEFT:
				SetSourceLoc(TILE_SPRITE_SIZE, TILE_SPRITE_SIZE * 3);
				break;
			case HORIZONTAL_RIGHT:
				SetSourceLoc(TILE_SPRITE_SIZE * 2, TILE_SPRITE_SIZE * 3);
				break;
			case BOTTOM:
				SetSourceLoc(TILE_SPRITE_SIZE, TILE_SPRITE_SIZE * 2);
				break;
			case INTERIOR:
				SetSourceLoc(TILE_SPRITE_SIZE * 2, TILE_SPRITE_SIZE * 2);
				break;
			case VERTICAL_TOP:
				SetSourceLoc(0, TILE_SPRITE_SIZE);
				break;
			case VERTICAL_MIDDLE:
				SetSourceLoc(0, TILE_SPRITE_SIZE * 2);
				break;
			}
			break;
		case BOUNCE:
			break;
		case SPIKE:
			break;
		case SWAP:
			break;
		case PASSABLE:
			break;
		case SWING:
			break;
		case MOVE:
			break;
		case TRANSITION:
			break;
		}
		break;
	}
}


Tile::~Tile()
{
}

void Tile::SetSourceLoc(int x, int y) {
	sourceRect.x = x;
	sourceRect.y = y;
}
