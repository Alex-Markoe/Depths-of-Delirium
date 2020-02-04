#include "GameObject.h"

//Constructor
GameObject::GameObject(SDL_Rect initPosition, SDL_Rect initSource, SDL_Point hitboxOffset){
	position = initPosition;
	sourceRect = initSource;
	HITBOX_OFFSET = hitboxOffset;

	hitbox = { position.x + HITBOX_OFFSET.x, position.y + HITBOX_OFFSET.y, position.w - (HITBOX_OFFSET.x * 2), position.h - HITBOX_OFFSET.y};

	velocity.x = 0;
	velocity.y = 0;
	frame = 0;
	flipType = SDL_FLIP_NONE;
}

//Destructor
GameObject::~GameObject(){
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

//Simple method that updates the animation frame
void GameObject::UpdateAnimation(){
	frame++;
	if (frame/7 > MAX_FRAME) { frame = 0; }

	sourceRect.x = ANIM_SOURCE_X + ((frame/7) * sourceRect.w);
}

//Function that handles loading in textures
void GameObject::loadTexture(std::string path, SDL_Renderer* gRenderer) {
	//Load the image
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//Create texture from the surface pixels
		texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (texture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
		}

		//Get rid of the old surface
		SDL_FreeSurface(loadedSurface);
	}
}

//Simple function to render the object to the screen
void GameObject::Draw(SDL_Renderer* gRenderer){
	SDL_RenderCopyEx(gRenderer, texture, &sourceRect, &position, 0, NULL, flipType);
}

//Apply a force to the object
void GameObject::ApplyForce(SDL_Point force) {
	acceleration.x += force.x;
	acceleration.y += force.y;
}

//Funtion to set the source rectangle in the case of changing states
void GameObject::setAnim(int sourceX, int sourceY, int maxFrame) {
	ANIM_SOURCE_X = sourceX;
	MAX_FRAME = maxFrame;
	sourceRect.x = sourceX;
	sourceRect.y = sourceY;
}

//Update the object's position based on any recently applied forces
void GameObject::UpdatePosition(){
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;
	
	if (abs(velocity.y) > MAX_VELOCITY.y)
		velocity.y = MAX_VELOCITY.y * (velocity.y / abs(velocity.y));
	if (abs(velocity.x) > MAX_VELOCITY.x)
		velocity.x = MAX_VELOCITY.x * (velocity.x / abs(velocity.x));

	position.x += velocity.x;
	position.y += velocity.y;

	hitbox.x = position.x + HITBOX_OFFSET.x;
	hitbox.y = position.y + HITBOX_OFFSET.y;

	acceleration.x = 0;
	acceleration.y = 0;
}

//Update function meant to be overriden
void GameObject::Update(){}