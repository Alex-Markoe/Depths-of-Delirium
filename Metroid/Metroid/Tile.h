#pragma once
#include "GameObject.h"

enum TILE_TYPE {
	BOUNCE,
	SWAP,
	PASSABLE,
	SPIKE,
	SWING,
	MOVE,
	PLATFORM,
	TRANSITION,
	BACKGROUND
};

enum TILE_ORIENTATION {
	TOP_MIDDLE,
	TOP_LEFT,
	TOP_RIGHT,
	HORIZONTAL_MIDDLE,
	HORIZONTAL_LEFT,
	HORIZONTAL_RIGHT,
	LEFT,
	RIGHT,
	INTERIOR,
	BOTTOM,
	VERTICAL_TOP,
	VERTICAL_MIDDLE,
};

enum SETTING {
	CAVERNS

};

class Tile : public GameObject
{
public:
	Tile(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOFfsetY, TILE_TYPE type, TILE_ORIENTATION orientation, SETTING setting);
	~Tile();
	void SetSourceLoc(int x, int y);
	TILE_TYPE type;

private:
	TILE_ORIENTATION orientation;
	SETTING setting;
	const int TILE_SPRITE_SIZE = 30;
};

