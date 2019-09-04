#include "GameObject.h"

//Constructor
GameObject::GameObject(SDL_Rect initPosition, SDL_Rect initSource){
	position = initPosition;
	sourceRect = initSource;
	position.w = sourceRect.w;
	position.h = sourceRect.h;

	velocity.x = 0;
	velocity.y = 0;
	frame = 0;
	flipType = SDL_FLIP_NONE;
}

//Destructor
GameObject::~GameObject(){
	SDL_DestroyTexture(texture);
	texture = NULL;
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

//Funtion to set the source rectangle in the case of changing states
void GameObject::setAnim(int sourceX, int sourceY, int maxFrame) {
	ANIM_SOURCE_X = sourceX;
	ANIM_SOURCE_Y = sourceY;
	MAX_FRAME = maxFrame;

	if (stateChange){
		sourceRect.x = sourceX;
		sourceRect.y = sourceY;
	}
}