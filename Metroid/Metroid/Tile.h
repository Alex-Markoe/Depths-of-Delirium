#pragma once
#include "GameObject.h"

enum TileType {
	Bounce,
	Swap,
	Passable,
	Spike,
	Swing,
	Move,
	Platform
};

enum TileOrientation {
	TopMiddle,
	TopLeft,
	TopRight,
	Left,
	Right,
	Middle,
	Bottom,
	CenterHorizontal,
	CenterVertical
};

enum Setting {
	Caverns

};

class Tile : GameObject
{
public:
	Tile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOFfsetY, TileType type, TileOrientation orientation, Setting setting);
	~Tile();
	TileType type;

private:
	TileOrientation orientation;
	Setting setting;
};

