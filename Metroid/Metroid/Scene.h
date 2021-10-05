//GUARD
#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "GameObject.h";
#include "TextureDatabase.h";

class Scene{
public:
	Scene() {};
	~Scene(){};
	virtual void Update(float deltaTime){};
	virtual void Render(SDL_Renderer* gRenderer){};
};

#endif //__SCENE_H_INCLUDED__