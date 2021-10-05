//GUARD
#ifndef __TEXTUREDATABASE_H_INCLUDED__
#define __TEXTUREDATABASE_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include <SDL_image.h>
#include <string>

//ENUM REPRESENTING WHERE IN THE 
//TEXTURE ARRAY A TEXTURE IS FOR A 
//PARTICULAR GAME OBJECT
enum TEXTURE_NAME {
	ICE_TILES_TXT,
	GRAVEYARD_TILES_TXT,
	SHADOW_TILES_TXT,
	ELDRITCH_TILES_TXT,
	PLAYER_TXT,
	PROJECTILE_TXT,
	BUTTON_TXT
};

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

	SDL_Texture* textures[7];
	const int TEXTURE_COUNT = 7;
};

#endif //__TEXTUREDATABASE_H_INCLUDED__