//GUARD
#ifndef __COMPONENT_H_INCLUDED__
#define __COMPONENT_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include <SDL.h>
#include <SDL_image.h>

//BASE COMPONENT CLASS
//ATTACHABLE BEHAVIOR FOR GAMEOBJECTS
class Component {
public:
	Component(){};
	~Component(){};
	virtual void Update(){};
};

#endif //__COMPONENT_H_INCLUDED__