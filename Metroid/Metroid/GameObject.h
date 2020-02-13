#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

class GameObject{
public:
	GameObject(SDL_Rect initPosition, SDL_Rect initSource, SDL_Point hitboxOffset);
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
	short collisionLayer;

protected:
	SDL_Texture* texture;
	SDL_RendererFlip flipType;
	SDL_Point HITBOX_OFFSET;
	SDL_Point MAX_VELOCITY;

	int frame;
	int MAX_FRAME;

	int ANIM_SOURCE_X;
};

