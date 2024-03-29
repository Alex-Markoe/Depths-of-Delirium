//GUARD
#ifndef __TEXTUREDATABASE_H_INCLUDED__
#define __TEXTUREDATABASE_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include <SDL_image.h>
#include <string>

//ENUM REPRESENTING WHERE IN THE 
//TEXTURE ARRAY A TEXTURE IS FOR A 
//PARTICULAR GAME OBJECT
enum TEXTURE_NAME { //REMEMBER TO UPDATE TEXTURE COUNT
	ICE_TILES_TXT,
	GRAVEYARD_TILES_TXT,
	SHADOW_TILES_TXT,
	ELDRITCH_TILES_TXT,
	PLAYER_TXT,
	PLAYER_PROJECTILE_TXT,
	BUTTON_TXT,
	FIRE_PARTICLES_TXT,
	ICE_PARTICLES_TXT,
	GRAVEYARD_PARTICLES_TXT,
	SHADOW_PARTICLES_TXT,
	ELDRITCH_PARTICLES_TXT,
	ICE_PROJECTILE_TXT
};

//TEXTURE DATABASE
//LOADS AND STORES ALL TEXTURES
//SINGLETON
class TextureDatabase{
public:
	static TextureDatabase& instance() {
		static TextureDatabase* instance = new TextureDatabase();
		return *instance;
	};
	~TextureDatabase();
	void LoadAssets(SDL_Renderer* gRenderer);
	SDL_Texture* GetTexture(int index);

private:
	TextureDatabase(){};
	void LoadTexture(SDL_Renderer* gRenderer, std::string path, int index);

	//CHANGE AT WILL
	SDL_Texture* textures[20];
	const int TEXTURE_COUNT = 20;
};

#endif //__TEXTUREDATABASE_H_INCLUDED__