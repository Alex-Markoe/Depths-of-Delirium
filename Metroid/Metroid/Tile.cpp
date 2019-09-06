#include "Tile.h"



Tile::Tile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOFfsetY, TileType Type, TileOrientation Orientation, TileSetting Setting) :
	GameObject(initPosition, initSource, hitboxOffsetX, hitboxOFfsetY){
	int sourceX = 0;
	int sourceY = 0;
	type = Type;
	orientation = Orientation;
	setting = Setting;

	switch (setting){
	case Caverns: //Cavern initalization
		switch(type){
		case Platform:
			switch (orientation){
			case TopLeft:
				break;
			case TopRight:
				break;
			case TopMiddle:
				break;
			case Left:
				break;
			case Right:
				break;
			case Middle:
				break;
			case CenterHorizontal:
				break;
			case CenterVertical:
				break;
			case Bottom:
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
		}
		break;


	}
}


Tile::~Tile()
{
}
