#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

class GameObject{
public:
	GameObject(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY);
	~GameObject();

	void UpdateAnimation();
	void loadTexture(std::string path, SDL_Renderer* gRenderer);
	void Draw(SDL_Renderer* gRenderer);
	void setAnim(int sourceX, int sourceY, int maxFrame);
	void UpdatePosition();

	SDL_Point velocity;
	SDL_Rect position;
	SDL_Rect sourceRect;
	SDL_Rect hitbox;

protected:
	SDL_Texture* texture;
	SDL_RendererFlip flipType;

	int frame;
	int MAX_FRAME;
	bool stateChange;

	int ANIM_SOURCE_X;
	int ANIM_SOURCE_Y;
	int HITBOX_OFFSET_X;
	int HITBOX_OFFSET_Y;
};

