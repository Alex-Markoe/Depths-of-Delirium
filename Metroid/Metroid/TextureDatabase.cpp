#include "TextureDatabase.h"

//Destructor
//DESTROY ALL THE TEXTURES
TextureDatabase::~TextureDatabase() {
	for (int i = 0; i < TEXTURE_COUNT; i++) {
		SDL_DestroyTexture(textures[i]);
	}
}
//PRETTY SIMPLE
SDL_Texture* TextureDatabase::GetTexture(int index) { return textures[index]; }

//Function that handles loading in textures
void TextureDatabase::LoadTexture(SDL_Renderer* gRenderer, std::string path, int index) {
	//Error handling
	if (index >= TEXTURE_COUNT) return;

	//Load the image
	if (textures[index] != nullptr) {
		SDL_DestroyTexture(textures[index]);
		textures[index] = nullptr;
	}

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//Create texture from the surface pixels
		textures[index] = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (textures[index] == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), IMG_GetError());
		}

		//Get rid of the old surface
		SDL_FreeSurface(loadedSurface);
	}
}

//Load in all of the assets
//AND ASSIGN THEM
void TextureDatabase::LoadAssets(SDL_Renderer* gRenderer) {
	for (unsigned i = 0; i < TEXTURE_COUNT; i++) {
		textures[i] = nullptr;
	}
	LoadTexture(gRenderer, "Assets/Phoenix_SpriteSheet.png", PLAYER_TXT);
	LoadTexture(gRenderer, "Assets/TileSheet.png", ICE_TILES_TXT);
	LoadTexture(gRenderer, "Assets/Buttons.png", BUTTON_TXT);
	LoadTexture(gRenderer, "Assets/Fireball.png", PLAYER_PROJECTILE_TXT);
	LoadTexture(gRenderer, "Assets/Fire_Particles.png", FIRE_PARTICLES_TXT);
	LoadTexture(gRenderer, "Assets/IceProjectiles.png", ICE_PROJECTILE_TXT);
}