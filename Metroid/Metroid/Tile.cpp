#include "Tile.h"



Tile::Tile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOFfsetY, TileType Type, TileOrientation Orientation, Setting Setting) :
	GameObject(initPosition, initSource, hitboxOffsetX, hitboxOFfsetY){
	type = Type;
	orientation = Orientation;
	setting = Setting;

	switch (setting){
	case Caverns: //Cavern initalization
		switch(type){
		case Platform:
			switch (orientation){
			case TopLeft:
				SetSourceLoc(TILE_SPRITE_SIZE, 0);
				break;
			case TopRight:
				SetSourceLoc(TILE_SPRITE_SIZE * 2, 0);
				break;
			case TopMiddle:
				SetSourceLoc(0, 0);
				break;
			case Left:
				SetSourceLoc(TILE_SPRITE_SIZE, TILE_SPRITE_SIZE);
				break;
			case Right:
				SetSourceLoc(TILE_SPRITE_SIZE * 2, TILE_SPRITE_SIZE);
				break;
			case HorizontalMiddle:
				SetSourceLoc(0, TILE_SPRITE_SIZE * 3);
				break;
			case HorizontalLeft:
				SetSourceLoc(TILE_SPRITE_SIZE, TILE_SPRITE_SIZE * 3);
				break;
			case HorizontalRight:
				SetSourceLoc(TILE_SPRITE_SIZE * 2, TILE_SPRITE_SIZE * 3);
				break;
			case Bottom:
				SetSourceLoc(TILE_SPRITE_SIZE, TILE_SPRITE_SIZE * 2);
				break;
			case Below:
				SetSourceLoc(TILE_SPRITE_SIZE * 2, TILE_SPRITE_SIZE * 2);
				break;
			case VerticalTop:
				SetSourceLoc(0, TILE_SPRITE_SIZE);
				break;
			case VerticalMiddle:
				SetSourceLoc(0, TILE_SPRITE_SIZE * 2);
				break;
			}
			break;
		case Bounce:
			break;
		case Spike:
			break;
		case Swap:
			break;
		case Passable:
			break;
		case Swing:
			break;
		case Move:
			break;
		case Transition:
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
