#pragma once
#include "GameObject.h"

enum TileType {
	Bounce,
	Swap,
	Passable,
	Spike,
	Swing,
	Move,
	Platform,
	Transition,
	Background
};

enum TileOrientation {
	TopMiddle,
	TopLeft,
	TopRight,
	HorizontalMiddle,
	HorizontalLeft,
	HorizontalRight,
	Left,
	Right,
	Below,
	Bottom,
	VerticalTop,
	VerticalMiddle,
};

enum Setting {
	Caverns

};

class Tile : public GameObject
{
public:
	Tile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOFfsetY, TileType type, TileOrientation orientation, Setting setting);
	~Tile();
	void SetSourceLoc(int x, int y);
	TileType type;

private:
	TileOrientation orientation;
	Setting setting;
	const int TILE_SPRITE_SIZE = 30;
};

