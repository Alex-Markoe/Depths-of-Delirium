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
	void ApplyForce(SDL_Point force);
	virtual void Draw(SDL_Renderer* gRenderer);
	virtual void UpdatePosition();
	virtual void setAnim(int sourceX, int sourceY, int maxFrame);
	virtual void Update();

	SDL_Point acceleration;
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
	int HITBOX_OFFSET_X;
	int HITBOX_OFFSET_Y;

	int MAX_VELOCITY_Y;
	int MAX_VELOCITY_X;
};

